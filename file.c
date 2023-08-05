/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:25:25 by madaguen          #+#    #+#             */
/*   Updated: 2023/08/05 23:23:33 by madaguen         ###   ########.fr       */
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
	while (i < 10)
	{
		file_name[i] = file_name[i] % 26 + 'A';
		i++;
	}
	return (file_name);
}

static int	get_fd(unsigned char *file_name, int option, int option_2)
{
	int	fd;

	fd = 0;
	if (option == HEREDOC)
		fd = open((const char *)file_name, O_RDWR | O_CREAT,
				S_IROTH | S_IWOTH);
	else if (option == INFILE)
		fd = open((const char *)file_name, O_RDONLY);
	else if (option == OUTFILE && !option_2)
		fd = open((const char *)file_name, O_TRUNC | O_WRONLY | O_CREAT,
				S_IWUSR | S_IRUSR | S_IROTH | S_IRGRP);
	else
		fd = open((const char *)file_name, O_APPEND | O_WRONLY | O_CREAT,
				S_IWUSR | S_IRUSR | S_IROTH | S_IRGRP);
	return (fd);
}

int	get_outfile(t_env *env, char *argv)
{
	env->outfile.file_name = (unsigned char *)ft_strdup(argv);
	if (!env->outfile.file_name)
		return (0);
	env->outfile.fd = get_fd(env->outfile.file_name, OUTFILE, env->heredoc);
	if (env->outfile.fd == -1)
		return (0);
	return (1);
}

int	get_infile(t_env *env, char *argv)
{
	
	env->infile.file_name = (unsigned char *)ft_strdup(argv);
	if (!env->infile.file_name)
		return (0);
	env->infile.fd = get_fd(env->infile.file_name, INFILE, env->heredoc);
	return (1);
}

int	get_infile_heredoc(t_env *env)
{
	char	*line;

	env->infile.file_name = get_file_name();
	printf("%s\n", env->infile.file_name);
	if (!env->infile.file_name)
		return (0);
	env->infile.fd = get_fd(env->infile.file_name, HEREDOC, env->heredoc);
	printf("%d\n", env->infile.fd);
	if (env->infile.fd == -1)
		return (0);
	while (1)
	{
		line = get_next_line(0);
		if (!line)
			break ;
		ft_putstr_fd(line, env->infile.fd);
		free(line);
	}
	unlink((const char *)env->infile.file_name);
	return (1);
}