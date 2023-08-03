#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

# define READ 0
# define WRITE 1
# define HEREDOC 1
# define INFILE 2
# define OUTFILE 3

typedef struct s_file
{
    unsigned char   *file_name;
    int     		fd;
}       t_file;

typedef struct s_env
{
    char    **env;
    int     heredoc;
    int     nb_cmd;
    int     index_start;
    int     pipe[2];
    int     prev_pipe;
    int     *pids;
    char    **lst_cmd;
    t_file  infile;
    t_file  outfile;
}        t_env;

void	ft_putstr_fd(char *str, int fd);
int		ft_strlen(char *str);
int		ft_strncmp(char *s1, char *s2, int n);
char    **ft_split(char const *s, char c);
char	*get_next_line(int fd);
char    *ft_strjoin(char *s1, char *s2, char c);
char    *ft_strdup(char *s1);
int     handle_arg(char **arg, int size, t_env *env);
void    error(char *str);
void	ft_memset(void *mem_zone, int size, char c);
void	ft_freetab(char **tab);
int    	get_infile_heredoc(t_env *env);
int     get_infile(t_env *env, char *argv);
int     get_outfile(t_env *env, char *argv);
void    free_infile(t_env *env);
void    free_outfile(t_env *env);
void    exec(t_env *env);
void    super_exec(t_env *env, int index);
int     waiting(int *pids, int nb_cmd);

#endif