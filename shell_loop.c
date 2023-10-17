#include "head.h"

/**
 *sh_cmdfork - forks a an execute to run cmd
 * @data: the parameter & return information struct
 *
 * Return: void
 */
void sh_cmdfork(info_t *data)
{
        pid_t child_pid;

        child_pid = fork();
        if (child_pid == -1)
        {
                /* TODO: PUT ERROR FUNCTION */
                perror("Error:");
                return;
        }
        if (child_pid == 0)
        {
                if (execve(data->path, data->argv, sh_envget(data)) == -1)
                {
                        sh_freinfo(data, 1);
                        if (errno == EACCES)
                                exit(126);
                        exit(1);
                }
                /* TODO: PUT ERROR FUNCTION */
        }
        else
        {
                wait(&(data->status));
                if (WIFEXITED(data->status))
                {
                        data->status = WEXITSTATUS(data->status);
                        if (data->status == 126)
                                sh_dsply_err(data, "Permission denied\n");
                }
        }
}


/**
 * sh_hsh - main shell loop
 * @data: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int sh_hsh(info_t *data, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		sh_rmvinfo(data);
		if (interface(data))
			_puts("$ ");
		sh_err_putchar(BUF_FLUSH);
		r = sh_getinput(data);
		if (r != -1)
		{
			sh_setinfo(data, av);
			builtin_ret = sh_fbuiltin(data);
			if (builtin_ret == -1)
				sh_fcmd(data);
		}
		else if (interface(data))
			_putchar('\n');
		sh_freinfo(data, 0);
	}
	sh_historywrite(data);
	sh_freinfo(data, 1);
	if (!interface(data) && data->status)
		exit(data->status);
	if (builtin_ret == -2)
	{
		if (data->err_num == -1)
			exit(data->status);
		exit(data->err_num);
	}
	return (builtin_ret);
}

/**
 * sh_fbuiltin - search a builtin command
 * @data: the parameter & return data struct
 *
 * Return: -1 if builtin not found,
 * 	0 if builtin executed successfully,
 * 	1 if builtin found but not successful,
 * 	2 if builtin signals exit()
 */
int sh_fbuiltin(info_t *data)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", sh_exit},
		{"env", sh_env},
		{"help", sh_help},
		{"history", sh_history},
		{"setenv", sh_setenv},
		{"unsetenv", sh_unsetenv},
		{"cd", sh_cd},
		{"alias", sh_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (sh_cmpstr(data->argv[0], builtintbl[i].type) == 0)
		{
			data->line_count++;
			built_in_ret = builtintbl[i].func(data);
			break;
		}
	return (built_in_ret);
}

/**
 * sh_fcmd - finds a command in PATH
 * @data: the parameter & return info struct
 *
 * Return: void
 */
void sh_fcmd(info_t *data)
{
	int i, j;
	char *path = NULL;

	data->path = data->argv[0];
	if (data->linecount_flag == 1)
	{
		data->line_count++;
		data->linecount_flag = 0;
	}
	for (i = 0, j = 0; data->arg[i]; i++)
		if (!ck_delim(data->arg[i], " \t\n"))
			j++;
	if (!j)
		return;

	path = sh_pathfind(data, sh_getenv(data, "PATH="), data->argv[0]);
	if (path)
	{
		data->path = path;
		sh_cmdfork(data);
	}
	else
	{
		if ((interface(data) ||sh_getenv(data, "PATH=")
					|| data->argv[0][0] == '/') && sh_excmd(data, data->argv[0]))
			sh_cmdfork(data);
		else if (*(data->arg) != '\n')
		{
			data->status = 127;
			sh_dsply_err(data, "not found\n");
		}
	}
}
