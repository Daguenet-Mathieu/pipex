/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 21:18:56 by madaguen          #+#    #+#             */
/*   Updated: 2023/08/15 15:11:25 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_invalide_in(t_env *env)
{
	free_infile(env);
	close(env->pipe[WRITE]);
	close(env->pipe[READ]);
	free_outfile(env);
	free(env->pids);
	exit(1);
}

void	ft_strncpy(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (s2[i] && i < n)
	{
		s1[i] = s2[i];
		i++;
	}
	s1 [i] = 0;
}

void	print_error(char *err, char *cmd, int nb)
{
	if (nb == 1)
	{
		ft_strncpy(err, "bash: ", 2048);
		ft_strncpy(err + (ft_strlen(err)), cmd, 2048 - ft_strlen(err));
		ft_strncpy(err + (ft_strlen(err)), " ", 2048 - ft_strlen(err));
		ft_strncpy(err + (ft_strlen(err)), strerror(errno),
			2048 - ft_strlen(err));
		ft_strncpy(err + (ft_strlen(err)), "\n",
			2048 - ft_strlen(err));
		write (2, err, ft_strlen(err));
	}
	if (nb == 2)
	{
		ft_strncpy(err, cmd, 2048);
		ft_strncpy(err + ft_strlen(err), ": command not found\n",
			2048 - ft_strlen(err));
		write (2, err, ft_strlen(err));
	}
}
