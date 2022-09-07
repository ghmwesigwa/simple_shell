#include "shell.h"

/**
 * _strcat - concatenates src to destination
 * @src: pointer to the source string
 * @dst: pointer to the destination string
 * Return: pointer to destination
 */
char *_strcat(char *dst, char *src)
{
	int len = 0, len2 = 0;

	if (!dst || !src)
	{
		return (dst);
	}
	while (dst[len2])
	{
		len2++;
	}
	while(src[len])
	{
		dst[len2++] = src[len];
		len++;
	}
	dst[len2] = '\0';
	return (dst);
}