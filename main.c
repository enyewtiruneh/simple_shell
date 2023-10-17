#include "head.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	int fd = 2;
	info_t data[] = { INIT_DATA };

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				sh_err_puts(av[0]);
				sh_err_puts(": 0: Can't open ");
				sh_err_puts(av[1]);
				sh_err_putchar('\n');
				sh_err_putchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		data->readfd = fd;
	}
	sh_poplat_envrnlist(data);
	sh_historyread(data);
	sh_hsh(data, av);
	return (EXIT_SUCCESS);
}

