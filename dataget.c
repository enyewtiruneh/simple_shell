#include "head.h"

/**
 * sh_freinfo- frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void sh_freinfo(info_t *info, int all)
{
	sh_freestr(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			sh_listfree(&(info->env));
		if (info->history)
			sh_listfree(&(info->history));
		if (info->alias)
			sh_listfree(&(info->alias));
		sh_freestr(info->environ);
		info->environ = NULL;
		sh_free_ptr_null((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}

/**
 * sh_rmvinfo - info_t structure initialization
 * @info: address of structure
 */
void sh_rmvinfo(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * sh_setinfo - info_t sturcture initialization
 * @info: address of structure
 * @av: argument vector
 */
void sh_setinfo(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = sh_dupstr(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			info->argc = i;

		replace_alias(info);
		replace_vars(info);
	}
}

