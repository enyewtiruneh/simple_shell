#include "head.h"

/**
 * sh_historynum - change number the history linked list after changes
 * @data: Structure holds arguments used to keep
 *
 * Return: the new histcount
 */
int sh_historynum(info_t *data)
{
	sh_list *node = data->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (data->histcount = i);
}

/**
 * sh_gethistory_file - hold the history file
 * @data: parameter struct
 *
 * Return: allocated string containg history file
 */

char *sh_gethistory_file(info_t *data)
{
	char *buffer, *direct;

	direct = sh_getenv(data, "HOME=");
	if (!direct)
		return (NULL);
	buffer = malloc(sizeof(char) * (sh_lnstr(direct) + sh_lnstr(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	sh_cpystr(buffer, direct);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);
	return (buffer);
}

/**
 * sh_historywrite - write a file, or appends to an existing file
 * @data: the parameter structure
 *
 * Return: 1 on success, else -1
 */
int sh_historywrite(info_t *data)
{
	ssize_t fd;
	char *filename = sh_gethistory_file(data);
	sh_list *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = data->history; node; node = node->next)
	{
		sh_putsfd(node->str, fd);
		sh_putfd('\n', fd);
	}
	sh_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * sh_historyread - reads history from file
 * @data: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int sh_historyread(info_t *data)
{
	char *buf = NULL, *filename = sh_gethistory_file(data);
	int j, last = 0, countln = 0;
	ssize_t fd, readln, filsize = 0;
	struct stat st;

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		filsize = st.st_size;
	if (filsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (filsize + 1));
	if (!buf)
		return (0);
	readln = read(fd, buf, filsize);
	buf[filsize] = 0;
	if (readln <= 0)
		return (free(buf), 0);
	close(fd);
	for (j = 0; j < filsize; j++)
		if (buf[j] == '\n')
		{
			buf[j] = 0;
			sh_historybld_list(data, buf + last, countln++);
			last = j + 1;
		}
	if (last != j)
		sh_historybld_list(data, buf + last, countln++);
	free(buf);
	data->histcount = countln;
	while (data->histcount-- >= HIST_MAX)
		sh_delete_at_index(&(data->history), 0);
	sh_historynum(data);
	return (data->histcount);
}

/**
 * sh_historybld_list - insert entry to a history linked list
 * @data: Structure holds arguments used to keep
 * @buf: buffer
 * @countln: the history linecount, history count
 *
 * Return: Always 0
 */
int sh_historybld_list(info_t *data, char *buf, int countln)
{
	sh_list *node = NULL;

	if (data->history)
		node = data->history;
	sh_insrtnode_end(&node, buf, countln);

	if (!data->history)
		data->history = node;
	return (0);
}

