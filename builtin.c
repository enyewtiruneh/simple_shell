#include "head.h"

/**
 * sh_cd - changes the directory of the current proces
 * @info: Structure Used to maintain constant function prototype.
 * Return: Always 0
 */
int sh_cd(info_t *info)
{
	int ch_dir_ret;
	char *dir, *st, buff[1024];

	st = getcwd(buff, 1024);
	if (!st)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = sh_getenv(info, "HOME=");
		if (!dir)
			ch_dir_ret = /* TODO: what should this be? */
				chdir((dir = sh_getenv(info, "PWD=")) ? dir : "/");
		else
			ch_dir_ret = chdir(dir);
	}
	else if (sh_cmpstr(info->argv[1], "-") == 0)
	{
		if (!sh_getenv(info, "OLDPWD="))
		{
			_puts(st);
			_putchar('\n');
			return (1);
		}
		_puts(sh_getenv(info, "OLDPWD=")), _putchar('\n');
		ch_dir_ret = /* TODO: what should this be? */
			chdir((dir = sh_getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		ch_dir_ret = chdir(info->argv[1]);
	if (ch_dir_ret == -1)
	{
		sh_dsply_err(info, "can't cd to ");
		sh_err_puts(info->argv[1]), sh_err_putchar('\n');
	}
	else
	{
		sh_envset(info, "OLDPWD", sh_getenv(info, "PWD="));
		sh_envset(info, "PWD", getcwd(buff, 1024));
	}
	return (0);
}

/**
 * sh_help - Changes the directory of the current proces
 * @info: Structure used to maintain constant function prototype.
 * Return: Always 0
 */
int sh_help(info_t *info)
{
	char **array_of_arg;

	array_of_arg = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*array_of_arg); /* temp att_unused workaround */
	return (0);
}

/**
 * sh_exit - exiting the shell
 * @info: Structure Used to maintain constant function prototype
 *
 * Return: exits (0) if info.argv[0] != "exit"
 */
int sh_exit(info_t *info)
{
	int checkexit;


	if (info->argv[1]) /* If there is an exit arguement */
	{
		checkexit = sh_atoi_err(info->argv[1]);
		if (checkexit == -1)
		{
			info->status = 2;
			sh_dsply_err(info, "Illegal number: ");
			sh_err_puts(info->argv[1]);
			sh_err_putchar('\n');
			return (1);
		}
		info->err_num = sh_atoi_err(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

