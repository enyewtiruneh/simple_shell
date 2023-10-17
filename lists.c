#include "head.h"

/**
 * sh_insrtnode_end - insert a node to the end of the list
 * @head: address of pointer to head node
 * @str: string field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
sh_list *sh_insrtnode_end(sh_list **head, const char *str, int num)
{
	sh_list *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(sh_list));
	if (!new_node)
		return (NULL);
	sh_memoryset((void *)new_node, 0, sizeof(sh_list));
	new_node->num = num;
	if (str)
	{
		new_node->str = sh_dupstr(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * sh_printlist - displays only the string element of a sh_list linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t sh_printlist(const sh_list *head)
{
	size_t j = 0;

	while (head)
	{
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		j++;
	}
	return (j);
}

/**
 * sh_insertnod - insert a node to the beginning of the list
 * @head: address of pointer to head node
 * @str: string field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
sh_list *sh_insertnod(sh_list **head, const char *str, int num)
{
	sh_list *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(sh_list));
	if (!new_head)
		return (NULL);
	sh_memoryset((void *)new_head, 0, sizeof(sh_list));
	new_head->num = num;
	if (str)
	{
		new_head->str = sh_dupstr(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * sh_listfree - frees all nodes of a list
 * @ptr_of_head: address of pointer to head node
 *
 * Return: void
 */
void sh_listfree(sh_list **ptr_of_head)
{
	sh_list *node, *next_node, *head;

	if (!ptr_of_head || !*ptr_of_head)
		return;
	head = *ptr_of_head;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*ptr_of_head = NULL;
}

/**
 * sh_delete_at_index - remove node at given index
 * @head: pointer to first node
 * @index: index of node to remove
 *
 * Return: 1 on success, 0 on failure
 */
int sh_delete_at_index(sh_list **head, unsigned int index)
{
	unsigned int i = 0;
	sh_list *node, *prev_node;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

