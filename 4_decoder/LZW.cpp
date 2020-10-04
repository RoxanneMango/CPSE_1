#include "compressor.hpp"
#include "decompressor.hpp"

#include <cstring>

int
main(int argc, char ** argv)
{
	bool compress = 1;
	bool assembly = 0;
	FILE * INPUT = NULL;
	FILE * OUTPUT = NULL;

	if(argc == 2)
	{
		if(!strncmp(argv[1], "-h", 2))
		{
			printf("Three arguments must be provided:\n");
			printf("\t(1) Compress \'-c\' or decompress \'-d\'\n");
			printf("\t(2) The input file\n\t(3) The output file.");
		}
		return 0;
	}
	
	if(argc < 4)
	{
		printf("Not enough arguments provided; use -h for help\n");
		return 1;
	}

	if(!strncmp(argv[1], "-c",2))
	{
		compress = 1;
	}
	else if(!strncmp(argv[1], "-d",2))
	{
		compress = 0;
	}
	else if(!strncmp(argv[1], "-a",2))
	{
		assembly = 1;
	}
	else
	{
		printf("Invalid argument: %s\n", argv[1]);
		return 1;
	}
	
	INPUT = fopen(argv[2], "r");
	if(!strncmp(argv[3], "stdout", 6))
	{
		OUTPUT = stdout;
	}
	else
	{
		OUTPUT = fopen(argv[3], "w");
	}
	
	if(INPUT == NULL)
	{
		printf("Could not open input file %s\n", argv[1]);
		return 1;
	}
	if(OUTPUT == NULL)
	{
		printf("Could not open output file %s\n", argv[2]);
		return 1;
	}
	
	if(assembly)
	{
		lz_compressor< 4096 > compressor;
		
		fprintf(OUTPUT, ".section .rodata\narray:\n\t.align 2\n\t.ascii \"\\\n");
		
		compressor.compress( 
			[ &INPUT ]()-> int 
			{ 
				char c = getc(INPUT);
				return c == EOF ? '\0' : c; 
			}
			,[ &OUTPUT ]( char c )
			{ 				
				if(c == '\n')
				{
//					putc('\\', OUTPUT);
					fprintf(OUTPUT, "\\r\\n\\");
				}
				putc(c, OUTPUT);
			}
		);
		
		fprintf(OUTPUT, "\"");
	}
	else if(compress)
	{
		lz_compressor< 4096 > compressor;
		compressor.compress( 
			[ &INPUT ]()-> int { char c = getc(INPUT); return c == EOF ? '\0' : c; },
			[ &OUTPUT ]( char c ){ putc( c, OUTPUT ); }
		);
	}
	else
	{
		lz_decompressor decompressor;
		decompressor.decompress( 
			[ &INPUT ]()-> int { char c = getc(INPUT); return c == EOF ? '\0' : c; },
			[ &OUTPUT ]( char c ){ putc(c, OUTPUT); }
		);
	}

	fclose(INPUT);
	fclose(OUTPUT);
	
	return 0;
}
