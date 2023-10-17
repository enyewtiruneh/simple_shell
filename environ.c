#include "head.h"

/**
 * sh_setenv - Initialize and modify enviroment variables
 * @info: Structure used to maintain constant function prototype.
 *  Return: Always 0
 */
int sh_setenv(info_t *info)
{
	if (info->argc != 3)
	{
		sh_err_puts("Incorrect number of arguements\n");
		return (1);
	}
	if (sh_envset(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * sh_unsetenv - Remove value of an environment variable
 * @info: Structure used to maintain constant function prototype.
 * Return: Always 0
 */
int sh_unsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		sh_err_puts("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		sh_envunset(info, info->argv[i]);

	return (0);
}

/**
 * sh_poplat_envrnlist - populates enviromental linked list
 * @info: Structure used to maintain constant function prototype.
 * Return: Always 0
 */
int sh_poplat_envrnlist(info_t *info)
{
	size_t j;
	sh_list *node = NULL;

	for (j = 0; environ[j]; j++)
		sh_insrtnode_end(&node, environ[j], 0);
	info->env = node;
	return (0);
}

/**
 * sh_env - prints the environment in the current process
 * @info: Structure used to maintain constant function prototype.
 * Return: Always 0
 */
int sh_env(info_t *info)
{
	sh_printlist(info->env);
	return (0);
}

/**
 * sh_getenv - gets the enviroment variable values
 * @info: Structure used to maintain constant function prototype.
 * @name: enviroment variable name
 *
 * Return: the value
 */
char *sh_getenv(info_t *info, const char *name)
{
	sh_list *node = info->env;
	char *pr;


	while (node)
	{
		pr = starts_with(node->str, name);
		if (pr && *pr)
			return (pr);
		node = node->next;
	}
	return (NULL);
}
