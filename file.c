/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:25:25 by madaguen          #+#    #+#             */
/*   Updated: 2023/08/09 17:39:25 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static unsigned char	*get_file_name(void)
{
	int				i;
	int				fd;
	unsigned char	*file_name;

	i = 0;
	file_name = malloc(sizeof(char) * 11);
	if (!file_name)
		return (NULL);
	fd = open("/dev/random", O_RDONLY);
	if (fd == -1)
		return (free(file_name), NULL);
	file_name[10] = 0;
	if (read(fd, file_name, 10) == -1)
		return (free(file_name), close(fd), NULL);
	close(fd);
	while (i < 10)
	{
		file_name[i] = file_name[i] % 26 + 'A';
		i++;
	}
	file_name[0] = '.';
	return (file_name);
}

int	get_fd(unsigned char *file_name, int option, int option_2)
{
	int	fd;

	fd = 0;
	if (option == HEREDOC)
		fd = open((const char *)file_name, O_WRONLY | O_TRUNC | O_CREAT, \
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

void	fill_here_doc(t_env *env)
{
	char	*line;

	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line)
		{
			error("\nbash: warning: here-document at delimited by ");
			bash_error("end-of-file (wanted `", env->lst_cmd[-1], "')\n");
			break ;
		}
		if (!verif_heredoc(line, env->lst_cmd[-1], ft_strlen(env->lst_cmd[-1])))
			break ;
		ft_putstr_fd(line, env->infile.fd);
		free(line);
	}
}

int	get_infile_heredoc(t_env *env)
{
	int	tmp_fd;

	env->infile.file_name = get_file_name();
	if (!env->infile.file_name)
		return (0);
	tmp_fd = get_fd(env->infile.file_name, HEREDOC, env->heredoc);
	if (env->infile.fd == -1)
		return (0);
	env->infile.fd = get_fd(env->infile.file_name, INFILE, 0);
	unlink((const char *)env->infile.file_name);
	fill_here_doc(env);
	close(tmp_fd);
	return (1);
}