#include "head.h"

/**
 * sh_chrdup - char duplication
 * @strpath: string PATH
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *sh_chrdup(char *strpath, int start, int stop)
{
	int i = 0, k = 0;
	static char buf[1024];

	for (k = 0, i = start; i < stop; i++)
		if (strpath[i] != ':')
			buf[k++] = strpath[i];
	buf[k] = 0;
	return (buf);
}

/**
 * sh_excmd - determines an executable command
 * @data: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int sh_excmd(info_t *data, char *path)
{
	struct stat st;

	(void)data;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * sh_pathfind - get cmd in the PATH string
 * @data: the info struct
 * @strpath: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *sh_pathfind(info_t *data, char *strpath, char *cmd)
{
	char *path;
	int i = 0, curr_p = 0;

	if (!strpath)
		return (NULL);
	if ((sh_lnstr(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (sh_excmd(data, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!strpath[i] || strpath[i] == ':')
		{
			path = sh_chrdup(strpath, curr_p, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (sh_excmd(data, path))
				return (path);
			if (!strpath[i])
				break;
			curr_p = i;
		}
		i++;
	}
	return (NULL);
}

