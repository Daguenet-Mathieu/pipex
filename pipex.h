/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 21:19:46 by madaguen          #+#    #+#             */
/*   Updated: 2023/08/12 04:27:29 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 150
# endif

typedef struct s_file
{
	unsigned char	*file_name;
	int				fd;
}					t_file;

typedef struct s_env
{
	char	**env;
	int		heredoc;
	int		nb_cmd;
	int		index_start;
	int		pipe[2];
	int		prev_pipe;
	int		*pids;
	char	**lst_cmd;
	t_file	infile;
	t_file	outfile;
}			t_env;

void	ft_putstr_fd(char *str, int fd);
int		ft_strlen(char *str);
int		ft_strncmp(char *s1, char *s2, int n);
int		verif_heredoc(char *s1, char *s2, int n);
char	**ft_split(char const *s, char c);
char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2, char c);
char	*ft_strdup(char *s1);
int		handle_arg(char **arg, int size, t_env *env);
void	error(char *str);
void	bash_error(char *s1, char *s2, char *s3);
void	ft_memset(void *mem_zone, int size, char c);
void	ft_freetab(char **tab);
char	*get_path(char **env);
int		get_infile_heredoc(t_env *env);
int		get_infile(t_env *env, char *argv);
int		get_outfile(t_env *env, char *argv);
void	free_infile(t_env *env);
void	free_outfile(t_env *env);
void	exec(t_env *env);
void	super_exec(t_env *env, int index);
int		waiting(int *pids, int nb_cmd);
int		failure_critic(t_env *env);
void	fail_cmd(t_env *env, char **cmd, char **path);
void	handle_invalid_out(t_env *env);
void	handle_invalide_in(t_env *env);
int		ft_dup(int infile, int outfile, t_env *env, int i);
void	dup_all(t_env *env, int i);
void	close_all(t_env *env, int i);
void	fill_here_doc(t_env *env, int tmp_fd);
int		get_fd(unsigned char *file_name, int option, int option_2);
void	close_parent(t_env *env, int i);

#endif
