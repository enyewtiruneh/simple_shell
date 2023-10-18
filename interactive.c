#include "head.h"

/**
 * ck_alphabt - checking alphabetic character
 * @cr: The input character
 * Return: if cr is alphabetic 1, otherwise 0.
 */

int ck_alphabt(int cr)
{
	if ((cr >= 'A' && cr <= 'Z') || (cr >= 'a' && cr <= 'z'))
		return (1);
	else
		return (0);
}

/**
 * converter - converting a string to integer
 * @str: the string is to be converted
 * Return: 0 if there is no numbers in string, otherwise converted the number
 */

int converter(char *str)
{
	unsigned int output = 0;
	int j, display, signal = 1, flag = 0;

	for (j = 0; str[j] != '\0' && flag != 2; j++)
	{
		if (str[j] == '-')
			signal *= -1;

		if (str[j] >= '0' && str[j] <= '9')
		{
			flag = 1;
			output *= 10;
			output += (str[j] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (signal == -1)
		display = -output;
	else
		display = output;
	return (display);
}


/**
 * interface - if the interface is interactive, return true
 * @info: address is type of struct
 *
 * Return: 1 if interactive interface, otherwise 0.
 */
int interface(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 3);
}

/**
 * ck_delim - checking the character of delimeter
 * @cr: the character to be checked
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int ck_delim(char cr, char *delim)
{
	while (*delim)
		if (*delim++ == cr)
			return (1);
	return (0);
}

