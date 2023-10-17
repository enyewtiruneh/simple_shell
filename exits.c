#include "head.h"

/**
 *sh_strn_copy - copies a string
 *@dest: destination of string to be copied to
 *@src: source of string
 *@amt: the amount of char to be copied
 *Return: the concatenated string
 */
char *sh_strn_copy(char *dest, char *src, int amt)
{
	char *str = dest;
	int i, j;

	i = 0;
	while (src[i] != '\0' && i < amt - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < amt)
	{
		j = i;
		while (j < amt)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (str);
}

/**
 *sh_loctchr - locates a char in a string
 *@str: the str to be parsed
 *@chr: the char to look for
 *Return: (str) a pointer to the memory area str
 */
char *sh_loctchr(char *str, char chr)
{
	do {
		if (*str == chr)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}

/**
 *sh_strn_concat - concat two strings
 *@dest: the first string
 *@src: the second string
 *@amt: the amount of bytes to be used
 *Return: the concatenated string
 */
char *sh_strn_concat(char *dest, char *src, int amt)
{
	char *str = dest;
	int i, j;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < amt)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < amt)
		dest[i] = '\0';
	return (str);
}

