/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:25:30 by madaguen          #+#    #+#             */
/*   Updated: 2023/08/12 20:32:26 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(char *str)
{
	ft_putstr_fd(str, 2);
}

void	bash_error(char *s1, char *s2, char *s3)
{
	if (s1)
		error(s1);
	if (s2)
		error(s2);
	if (s3)
		error(s3);
}

void	fail_cmd(t_env *env, char **cmd, char **path)
{
	ft_freetab(path);
	ft_freetab(cmd);
	failure_critic(env);
	exit (127);
}

int	failure_critic(t_env *env)
{
	if (env->infile.file_name)
		free_infile(env);
	if (env->outfile.file_name)
		free_outfile(env);
	close(env->pipe[0]);
	close(env->pipe[1]);
	if (env->prev_pipe)
		close(env->prev_pipe);
	free(env->pids);
	env->pids = NULL;
	return (0);
}

void	handle_invalid_out(t_env *env)
{
	close(env->pipe[WRITE]);
	close(env->pipe[READ]);
	free_outfile(env);
	free(env->pids);
	exit(1);
}
