#include "head.h"

/**
 * sh_envunset - delete an environ variable
 * @info: Structure holds arguments used to update constant fun prototype.
 *  Return: 1 on delete, 0 otherwise
 * @envar: the string enviromental variable property
 */
int sh_envunset(info_t *info, char *envar)
{
	size_t i = 0;
	char *ptr;
	sh_list *node = info->env;

	if (!node || !envar)
		return (0);

	while (node)
	{
		ptr = starts_with(node->str, envar);
		if (ptr && *ptr == '=')
		{
			info->env_changed = sh_delete_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * sh_envget - returns array of  string copy of our environment
 * @info: Structure holds arguments used to modify constant fun prototype.
 * Return: Always 0
 */
char **sh_envget(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = sh_strslist(info->env);
		info->env_changed = 0;
	}
	return (info->environ);
}

/**
 * sh_envset - Initialize a new env var or update an existing one
 * @info: Structure holds arguments used to keep constant fun prototype.
 * @envar: the string enviromental variable property
 * @value: the string env var value
 *  Return: Always 0
 */
int sh_envset(info_t *info, char *envar, char *value)
{
	char *buffer = NULL;
	sh_list *node;
	char *ptr;

	if (!envar || !value)
		return (0);

	buffer = malloc(sh_lnstr(envar) + sh_lnstr(value) + 2);
	if (!buffer)
		return (1);
	sh_cpystr(buffer, envar);
	_strcat(buffer, "=");
	_strcat(buffer, value);
	node = info->env;
	while (node)
	{
		ptr = starts_with(node->str, envar);
		if (ptr && *ptr == '=')
		{
			free(node->str);
			node->str = buffer;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	sh_insrtnode_end(&(info->env), buffer, 0);
	free(buffer);
	info->env_changed = 1;
	return (0);
}

