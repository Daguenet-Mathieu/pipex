/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 21:18:36 by madaguen          #+#    #+#             */
/*   Updated: 2023/08/06 23:35:43 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	find_c(char *line, int *pos, char c)
{
	int	i;

	i = 0;
	if (!line)
	{
		*pos = 0;
		return (0);
	}
	while (line[i] && line[i] != c)
		i++;
	*pos = i;
	return (line[i] == c);
}

int	join_line_util(char *line, char *res, char **tmp, char *buffer)
{
	int	j;
	int	c;
	int	i;
	int	len_b;

	j = 0;
	i = 0;
	c = 0;
	while (buffer[j] && buffer[j] != '\n')
		res[i++] = buffer[j++];
	if (buffer[j] == '\n')
	{
		res[(i)++] = buffer[j++];
		find_c(&buffer[j], &len_b, 0);
		*tmp = malloc(sizeof(char) * len_b + 1);
		if (!*tmp)
			return (free(line), free(res), 0);
		while (buffer[j])
			(*tmp)[c++] = buffer[j++];
		(*tmp)[c] = 0;
	}
	res[i] = 0;
	return (1);
}

char	*join_line(char *line, char *buffer, char **tmp)
{
	int		i;
	int		len_l;
	int		len_b;
	char	*res;

	*tmp = NULL;
	find_c(line, &len_l, 0);
	find_c(buffer, &len_b, '\n');
	res = malloc(sizeof(char) * (len_l + len_b + 1 + 1));
	if (!res)
		return (free(line), NULL);
	i = 0;
	while (line && line[i])
	{
		res[i] = line[i];
		i++;
	}
	res[i] = 0;
	if (!join_line_util(line, res + i, tmp, buffer))
		return (NULL);
	free(line);
	return (res);
}

void	str_copy(char *buffer, char *tmp)
{
	int	i;

	i = 0;
	while (tmp && tmp[i])
	{
		buffer[i] = tmp[i];
		i++;
	}
	buffer[i] = 0;
}

char	*get_next_line(int fd)
{
	int			nl;
	int			r;
	char		*line;
	char		*tmp;
	static char	buffer[BUFFER_SIZE + 1];

	line = NULL;
	r = BUFFER_SIZE;
	while (1)
	{
		line = join_line(line, buffer, &tmp);
		if (!line)
			return (free(tmp), NULL);
		ft_memset(buffer, BUFFER_SIZE, 0);
		str_copy(buffer, tmp);
		free(tmp);
		if (find_c(line, &nl, '\n') || r < BUFFER_SIZE)
			break ;
		r = read(fd, buffer, BUFFER_SIZE);
		if (r == -1)
			return (free(line), free(tmp), NULL);
	}
	if (line && !*line)
		return (free(line), NULL);
	return (line);
}
