#include "toggle_asciz.h"

char
toggle_asciz(char s)
{
	return (((s >= 'a') && (s <= 'z')) ? toupper(s) : ((s >= 'A') && (s <= 'Z')) ? tolower(s) : s);
}