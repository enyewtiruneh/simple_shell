#include "head.h"

/**
 * sh_lenglist - determ len of linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t sh_lenglist(const sh_list *head)
{
	size_t j = 0;

	while (head)
	{
		head = head->next;
		j++;
	}
	return (j);
}

/**
 * sh_strslist - returns an array of strings of the liststr
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **sh_strslist(sh_list *head)
{
	char *str;
	sh_list *node = head;
	char **strs;
	size_t i = sh_lenglist(head), j;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(sh_lnstr(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = sh_cpystr(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * sh_listprint- prints elements of a linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t sh_listprint(const sh_list *head)
{
	size_t j = 0;

	while (head)
	{
		_puts(sh_cvrt_numbr(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		j++;
	}
	return (j);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
sh_list *node_starts_with(sh_list *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(sh_list *head, sh_list *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}

