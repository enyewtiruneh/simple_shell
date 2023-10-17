#include "head.h"

/**
 * sh_dsply_err - displays an error message
 * @info: the parameter & return info struct
 * @erstr: string holds error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void sh_dsply_err(info_t *info, char *erstr)
{
	sh_err_puts(info->fname);
	sh_err_puts(": ");
	sh_printdc(info->line_count, STDERR_FILENO);
	sh_err_puts(": ");
	sh_err_puts(info->argv[0]);
	sh_err_puts(": ");
	sh_err_puts(erstr);
}

/**
 * sh_cvrt_numbr - function convers number, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *sh_cvrt_numbr(long int num, int base, int flags)
{
	unsigned long n = num;
	char sign = 0;
	char *ptr;
	static char buff[50];
	static char *array;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buff[49];
	*ptr = '\0';
	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);
	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * sh_rmv_comments - replaces first instance of '#' with '\0'
 * @buffer: address of the string to update
 *
 * Return: Always 0;
 */
void sh_rmv_comments(char *buffer)
{
	int i;

	for (i = 0; buffer[i] != '\0'; i++)
		if (buffer[i] == '#' && (!i || buffer[i - 1] == ' '))
		{
			buffer[i] = '\0';
			break;
		}
}

/**
 * sh_atoi_err - changing string to intiger
 * @str: the string to be converted
 * Return: 0 if no numbers in string, otherwise
 *       -1 on error
 */
int sh_atoi_err(char *str)
{
	unsigned long int output = 0;
	int i = 0;

	if (*str == '+')
		str++;  /* TODO: why does this make main return 255? */
	for (i = 0;  str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			output *= 10;
			output += (str[i] - '0');
			if (output > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (output);
}

/**
 * sh_printdc - prints a decimal number
 * @input: the input
 * @fd: the file descriptor to write to
 *
 * Return: number of characters printed
 */
int sh_printdc(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = sh_err_putchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}
