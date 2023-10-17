#include "head.h"

/**
 * sh_buffer_input - buffers commands
 * @info: parameter
 * @buffer: address of buffer
 * @len: address of length of variable
 *
 * Return: bytes read
 */
ssize_t sh_buffer_input(info_t *info, char **buffer, size_t *len)
{
	ssize_t reslt = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		reslt = getline(buffer, &len_p, stdin);
#else
		reslt = _getline(info, buffer, &len_p);
#endif
		if (reslt > 0)
		{
			if ((*buffer)[reslt - 1] == '\n')
			{
				(*buffer)[reslt - 1] = '\0'; /* remove trailing newline */
				reslt--;
			}
			info->linecount_flag = 1;
			sh_rmv_comments(*buffer);
			sh_historybld_list(info, *buffer, info->histcount++);
			/* if (_strchr(*buffer, ';')) is this a command chain? */
			{
				*len = reslt;
				info->cmd_buf = buffer;
			}
		}
	}
	return (reslt);
}

/**
 * sh_getinput - gets a newline
 * @data: parameter struct
 *
 * Return: bytes read
 */
ssize_t sh_getinput(info_t *data)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(data->arg), *p;

	_putchar(BUF_FLUSH);
	r = sh_buffer_input(data, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		check_chain(data, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (sh_chain(data, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			data->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (sh_lnstr(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return length of buffer from _getline() */
}

/**
 * sh_buffread - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t sh_buffread(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	char *p = NULL, *new_p = NULL, *c;
	static char buf[READ_BUF_SIZE];
	static size_t j, len;
	ssize_t k;
	ssize_t r = 0, s = 0;

	p = *ptr;
	if (p && length)
		s = *length;
	if (j == len)
		j = len = 0;

	r = sh_buffread(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = sh_loctchr(buf + j, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = sh_realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		sh_strn_concat(new_p, buf + j, k - j);
	else
		sh_strn_copy(new_p, buf + j, k - j + 1);

	s += k - j;
	j = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

