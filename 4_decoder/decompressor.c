#include "decompressor.h"   

void decode(char * input)
{
	char * buffer = (char *) calloc(BUFF_LEN, sizeof(char));
	
	for(;;)
	{
		char c = *(input++);
		if( c == '\0' )
		{
			return;
		}
		if( c != '@' )
		{
			putchar(c);
			for( int i = BUFF_LEN; i > 0; --i )
			{
				buffer[ i ] = buffer[ i - 1 ];
			}
			buffer[ 0 ] = c;
		} 
		else 
		{
			int offset = *(input++) - '0';
			int length = *(input++) - '0';
			while( length-- )
			{
				char c = buffer[ offset ];
				putchar(c);
				for( int i = BUFF_LEN; i > 0; --i )
				{
					buffer[ i ] = buffer[ i - 1 ];
				}
				buffer[ 0 ] = c;
			}
		}
	}
	free(buffer);
}