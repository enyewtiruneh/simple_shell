#include "head.h"

/**
 * sh_putsfd - displays an input string
 * @str: the string to be displayed
 * @fd: the fd to write to
 *
 * Return: the number of chars put
 */
int sh_putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += sh_putfd(*str++, fd);
	}
	return (i);
}

/**
 * sh_err_putchar - writes the char cr to stderr
 * @cr: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is displayed appropriately.
 */
int sh_err_putchar(char cr)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (cr == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (cr != BUF_FLUSH)
		buf[i++] = cr;
	return (1);
}

/**
 * sh_err_puts - Displays an input string
 * @str: the string to be displays
 *
 * Return: Nothing
 */
void sh_err_puts(char *str)
{
	int j = 0;

	if (!str)
		return;
	while (str[j] != '\0')
	{
		sh_err_putchar(str[j]);
		j++;
	}
}

/**
 * sh_putfd - writes the char c to given file descripter
 * @c: print character
 * @fd: The fd to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int sh_putfd(char c, int fd)
{
	static char buf[WRITE_BUF_SIZE];
	static int j;

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(fd, buf, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		buf[j++] = c;
	return (1);
}
