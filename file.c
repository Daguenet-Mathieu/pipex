/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:25:25 by madaguen          #+#    #+#             */
/*   Updated: 2023/08/12 04:42:49 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_strcpy(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = 0;
}

static unsigned char	*get_file_name(void)
{
	int				i;
	int				fd;
	unsigned char	*file_name;

	i = 5;
	file_name = malloc(sizeof(char) * 16);
	if (!file_name)
		return (NULL);
	ft_strcpy((char *)file_name, "/tmp/");
	fd = open("/dev/random", O_RDONLY);
	if (fd == -1)
		return (free(file_name), NULL);
	if (read(fd, file_name + 5, 10) == -1)
		return (free(file_name), close(fd), NULL);
	close(fd);
	while (i < 16)
	{
		file_name[i] = file_name[i] % 26 + 'A';
		i++;
	}
	file_name[15] = 0;
	file_name[5] = '.';
	printf("filename == %s\n", file_name);
	return (file_name);
}

int	get_fd(unsigned char *file_name, int option, int option_2)
{
	int	fd;

	fd = 0;
	if (option == HEREDOC)
		fd = open((const char *)file_name, O_WRONLY | O_CREAT, \
		S_IRUSR | S_IWUSR | S_IRGRP);
	else if (option == INFILE)
		fd = open((const char *)file_name, O_RDONLY);
	else if (option == OUTFILE && !option_2)
		fd = open((const char *)file_name, O_TRUNC | O_WRONLY | O_CREAT,
				S_IWUSR | S_IRUSR | S_IROTH | S_IRGRP);
	else
		fd = open((const char *)file_name, O_APPEND | O_WRONLY | O_CREAT, \
		S_IWUSR | S_IRUSR | S_IROTH | S_IRGRP);
	return (fd);
}

void	fill_here_doc(t_env *env, int tmp_fd)
{
	char	*line;

	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line)
		{
			error("\nbash: warning: here-document at at line 0\
 delimited by ");
			bash_error("end-of-file (wanted `", env->lst_cmd[-1], "')\n");
			break ;
		}
		if (!verif_heredoc(line, env->lst_cmd[-1], ft_strlen(env->lst_cmd[-1])))
			break ;
		ft_putstr_fd(line, tmp_fd);
		perror("write");
		free(line);
	}
	free(line);
}

int	get_infile_heredoc(t_env *env)
{
	int	tmp_fd;

	env->infile.file_name = get_file_name();
	if (!env->infile.file_name)
		return (0);
	tmp_fd = get_fd(env->infile.file_name, HEREDOC, env->heredoc);
	printf("fd == %d\n", tmp_fd);
	if (tmp_fd == -1)
		return (0);
	env->infile.fd = get_fd(env->infile.file_name, INFILE, 0);
	unlink((const char *)env->infile.file_name);
	fill_here_doc(env, tmp_fd);
	close(tmp_fd);
	return (1);
}
