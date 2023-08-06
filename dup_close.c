/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_close.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 21:18:48 by madaguen          #+#    #+#             */
/*   Updated: 2023/08/06 23:36:09 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_dup(int infile, int outfile, t_env *env, int i)
{
	int	res;

	res = 1;
	if (dup2(infile, READ) == -1)
	{
		perror("dup2 in");
		res = failure_critic(env);
	}
	if (dup2(outfile, WRITE) == -1)
	{
		perror("dup2 out");
		res = failure_critic(env);
	}
	i++;
	return (res);
}

void	dup_all(t_env *env, int i)
{
	if (i == 0)
	{
		if (!ft_dup(env->infile.fd, env->pipe[WRITE], env, i))
		{
			failure_critic(env);
			exit (127);
		}
	}
	else if (i == env->nb_cmd - 1)
	{
		if (!ft_dup(env->prev_pipe, env->outfile.fd, env, i))
		{
			failure_critic(env);
			exit (127);
		}
	}
	else
	{
		if (!ft_dup(env->prev_pipe, env->pipe[WRITE], env, i))
		{
			failure_critic(env);
			exit (127);
		}
	}
}

void	close_all(t_env *env, int i)
{
	if (i == 0)
	{
		free_infile(env);
		close(env->pipe[WRITE]);
		close(env->pipe[READ]);
		free_outfile(env);
	}
	else if (i == env->nb_cmd - 1)
	{
		close(env->prev_pipe);
		free_outfile(env);
	}
	else
	{
		close(env->prev_pipe);
		close(env->pipe[WRITE]);
		close(env->pipe[READ]);
		free_outfile(env);
	}
}

void	close_parent(t_env *env, int i)
{
	if (i == 0)
	{
		free_infile(env);
		close(env->pipe[WRITE]);
	}
	else if (i == env->nb_cmd - 1)
	{
		close(env->prev_pipe);
		free_outfile(env);
	}
	else
	{
		close(env->prev_pipe);
		close(env->pipe[WRITE]);
	}
}
