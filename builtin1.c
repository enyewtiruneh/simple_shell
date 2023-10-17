#include "head.h"

/**
 * sh_history - the history list, one command by line, preceded
 * @info: Structure arguments used to keep const fun prototype.
 *  Return: Always 0
 */

int sh_history(info_t *info)
{
	sh_listprint(info->history);
	return (0);
}

/**
 * sh_unset - sets alias to string
 * @info: Structure used to mainain constan function prototype.
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int sh_unset(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = sh_loctchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = sh_delete_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = sh_loctchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (sh_unset(info, str));

	sh_unset(info, str);
	return (sh_insrtnode_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(sh_list *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = sh_loctchr(node->str, '=');
		for (a = node->str; a <= p; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * sh_alias - the alias builtin
 * @data: Structure holds arguments used to keep function prototype.
 *  Return: Always 0
 */
int sh_alias(info_t *data)
{
	char *p = NULL;
	int i = 0;
	sh_list *node = NULL;


	if (data->argc == 1)
	{
		node = data->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; data->argv[i]; i++)
	{
		p = sh_loctchr(data->argv[i], '=');
		if (p)
			set_alias(data, data->argv[i]);
		else
			print_alias(node_starts_with(data->alias, data->argv[i], '='));
	}

	return (0);
}

