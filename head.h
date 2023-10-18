#ifndef _HEAD_H_
#define _HEAD_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM        0
#define CMD_OR          1
#define CMD_AND         2
#define CMD_CHAIN       3

/* for convert_number() */
#define CONVERT_LOWERCASE       1
#define CONVERT_UNSIGNED        2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE       ".simple_shell_history"
#define HIST_MAX        4096

extern char **environ;


/**
 * struct str_detail - list the string linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct str_detail
{
	int num;
	char *str;
	struct str_detail *next;
} sh_list;

/**
 * struct argpass - passes arguements into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct argpass
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	sh_list *env;
	sh_list *history;
	sh_list *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INIT_DATA \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct blt_function - implements a builtin string
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct blt_function
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* shloop.c */
int sh_hsh(info_t *, char **);
int sh_fbuiltin(info_t *);
void sh_fcmd(info_t *);
void sh_cmdfork(info_t *);

/* parser.c */
int sh_excmd(info_t *, char *);
char *sh_chrdup(char *, int, int);
char *sh_pathfind(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* errors.c */
void sh_err_puts(char *);
int sh_err_putchar(char);
int sh_putfd(char str, int fd);
int sh_putsfd(char *str, int fd);

/* toem_string.c */
int sh_lnstr(char *);
int sh_cmpstr(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);


/* string1.c */
char *sh_cpystr(char *, char *);
char *sh_dupstr(const char *);
void _puts(char *);
int _putchar(char);

/* exits.c */
char *sh_strn_copy(char *, char *, int);
char *sh_strn_concat(char *, char *, int);
char *sh_loctchr(char *, char);

/* tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* realloc.c */
char *sh_memoryset(char *, char, unsigned int);
void sh_freestr(char **);
void *sh_realloc(void *, unsigned int, unsigned int);

/* memory.c */
int sh_free_ptr_null(void **);

/* atoi.c */
int interface(info_t *);
int ck_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* errors1.c */
int sh_atoi_err(char *);
void sh_dsply_err(info_t *, char *);
int sh_printdc(int, int);
char *sh_cvrt_numbr(long int, int, int);
void sh_rmv_comments(char *);

/* builtin.c */
int sh_exit(info_t *);
int sh_cd(info_t *);
int sh_help(info_t *);

/* builtin1.c */
int sh_history(info_t *);
int sh_alias(info_t *);

/* getline.c */
ssize_t sh_getinput(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* getinfo.c */
void sh_rmvinfo(info_t *);
void sh_setinfo(info_t *, char **);
void sh_freinfo(info_t *, int);

/* environ.c */
char *sh_getenv(info_t *, const char *);
int sh_env(info_t *);
int sh_setenv(info_t *);
int sh_unsetenv(info_t *);
int sh_poplat_envrnlist(info_t *);

/* getenv.c */
char **sh_envget(info_t *);
int sh_envunset(info_t *, char *);
int sh_envset(info_t *, char *, char *);

/* history.c */
char *sh_gethistory_file(info_t *data);
int sh_historywrite(info_t *data);
int sh_historyread(info_t *data);
int sh_historybld_list(info_t *data, char *buf, int countln);
int sh_historynum(info_t *data);

/* lists.c */
sh_list *sh_insrtnod(sh_list **, const char *, int);
sh_list *sh_insrtnode_end(sh_list **, const char *, int);
size_t sh_printlist(const sh_list *);
int sh_delete_at_index(sh_list **, unsigned int);
void sh_listfree(sh_list **);

/* lists1.c */
ssize_t get_node_index(sh_list *, sh_list *);
char **sh_strslist(sh_list *);
size_t sh_listprint(const sh_list *);
size_t sh_lenglist(const sh_list *);
sh_list *node_starts_with(sh_list *, char *, char);

/* vars.c */
int sh_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
