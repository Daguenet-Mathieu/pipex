/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:24:49 by madaguen          #+#    #+#             */
/*   Updated: 2023/08/05 18:46:59 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int failure_critic(t_env *env)
{
    (void) env;
    return (0);
}

int	ft_dup(int infile, int outfile, t_env *env)
{
	int	res;

	res = 1;
	if (dup2(infile, READ) == -1)
	{
		perror("dup2");
		res = failure_critic(env);\
	}
	if (dup2(outfile, WRITE) == -1)
	{
		perror("dup2");
		res = failure_critic(env);
	}
	return (res);
}

char	*check_access(char *cmd, char **path)
{
	int		i;
	char	*pathed;

	i = 0;
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
	{
		if (!access(cmd, F_OK))
			return (ft_strdup(cmd));
		error("bash: ");
		error(cmd);
		error(": No such file or directory\n");
		return (NULL);
	}
	while (path[i])
	{
		pathed = ft_strjoin(path[i], cmd, '/');
		if (!pathed)
			return (NULL);
		if (!access(pathed, F_OK))
			return (pathed);
		free(pathed);
		i++;
	}
	if (!access(cmd, F_OK))
		return (ft_strdup(cmd));
	error(cmd);
	error(": command not found\n");
	return (NULL);
}

char	*get_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			return (&env[i][5]);
		i++;
	}
	return (NULL);
}

void	super_exec(t_env *env, int i)
{
	char	**path;
	char	**cmd;
	char	*pathed;

	path = ft_split(get_path(env->env), ':');
	cmd = ft_split(env->lst_cmd[i], ' ');
	pathed = check_access(cmd[0], path);
	if (!pathed)
	{
		free(path);
		free(cmd);
		failure_critic(env);
		exit (127);
	}
	if (i == 0)
	{
		if (!ft_dup(env->infile.fd, env->pipe[WRITE], env))
		{
			failure_critic(env);
			exit (127);
		}
	}
	else if (i == env->nb_cmd - 1)
	{

		if (!ft_dup(env->prev_pipe, env->outfile.fd, env))
		{
			failure_critic(env);
			exit (127);
		}
	}
	else
	{
		if (!ft_dup(env->prev_pipe, env->pipe[WRITE], env))
		{
			failure_critic(env);
			exit (127);
		}
	}
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
		
	if (execve(pathed, cmd, env->env) == -1)
	{
		free(path);
		free(cmd);
		failure_critic(env);
		exit(0);
	}

}

void	exec(t_env *env)
{
	int	i;
	int	pid;

	i = 0;
	while (i < env->nb_cmd)
	{
		if (i < env->nb_cmd - 1)
		{
			if (pipe(env->pipe) == -1)
				failure_critic(env);
		}
		pid = fork();
		if (pid == -1)
			failure_critic(env);
		else if (pid == 0)
			super_exec(env, i);
		if (i == 0)
		{
			free_infile(env);
			close(env->pipe[WRITE]);
			env->prev_pipe = env->pipe[READ];
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
		env->prev_pipe = env->pipe[READ];
		env->pids[i] = pid;
		i++;
	}
}
