#include "head.h"

/**
 * sh_realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *sh_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
			free(ptr);
	return (p);
}

/**
 * sh_memoryset - fills memory with a constant byte
 * @str: the pointer to the memory area
 * @byt: the byte to fill *s with
 * @amt: the amount of bytes to be filled
 * Return: (s) a pointer to the memory area s
 */
char *sh_memoryset(char *str, char byt, unsigned int amt)
{
	unsigned int i;

	for (i = 0; i < amt; i++)
		str[i] = byt;
	return (str);
}

/**
 * sh_freestr - frees strs of string
 * @ptrptr: string of strings
 */
void sh_freestr(char **ptrptr)
{
	char **a = ptrptr;

	if (!ptrptr)
		return;
	while (*ptrptr)
		free(*ptrptr++);
	free(a);
}
