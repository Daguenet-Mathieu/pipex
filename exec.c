/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:24:49 by madaguen          #+#    #+#             */
/*   Updated: 2023/08/14 21:43:32 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		ft_strncpy(err + (ft_strlen(err)), cmd,2048 - ft_strlen(err));
		ft_strncpy(err + (ft_strlen(err)), " ",2048 - ft_strlen(err));
		ft_strncpy(err + (ft_strlen(err)), strerror(errno), 2048 - ft_strlen(err));
		ft_strncpy(err + (ft_strlen(err)), "\n",2048 - ft_strlen(err));
		write (2, err, ft_strlen(err));
	}
	if (nb == 2)
	{
		ft_strncpy(err, cmd, 2048);
		ft_strncpy(err + ft_strlen(err), ": command not found\n", 2048 - ft_strlen(err));
		write (2, err, ft_strlen(err));
	}
}

char	*check_access(char *cmd, char **path)
{
	int		i;
	char	*pathed;
	char	err[2048];

	i = 0;
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/') || \
	(cmd[0] == '.' && cmd[1] == '.' && cmd[2] == '/'))
	{
		if (!access(cmd, F_OK | X_OK))
			return (ft_strdup(cmd));
		print_error(err, cmd, 1);
		return (NULL);
	}
	while (path && path[i])
	{
		pathed = ft_strjoin(path[i], cmd, '/');
		if (!pathed)
			return (NULL);
		if (!access(pathed, F_OK | X_OK))
			return (pathed);
		free(pathed);
		i++;
	}
	print_error(err, cmd, 2);
	return (NULL);
}

void	super_exec(t_env *env, int i)
{
	char	**path;
	char	**cmd;
	char	*pathed;

	if (env->infile.fd == -1 && i == 0)
		handle_invalide_in(env);
	if (env->outfile.fd == -1 && i == env->nb_cmd -1)
		handle_invalid_out(env);
	path = ft_split(get_path(env->env), ':');
	cmd = ft_split(env->lst_cmd[i], ' ');
	if (!cmd)
		fail_cmd(env, cmd, path);
	pathed = check_access(cmd[0], path);
	if (!pathed)
		fail_cmd(env, cmd, path);
	dup_all(env, i);
	close_all(env, i);
	execve(pathed, cmd, env->env);
	ft_freetab(path);
	ft_freetab(cmd);
	free(pathed);
	failure_critic(env);
	exit(0);
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
		{
			failure_critic(env);
			env->nb_cmd = i;
			return ;
		}
		else if (pid == 0)
			super_exec(env, i);
		close_parent(env, i);
		env->prev_pipe = env->pipe[READ];
		env->pids[i] = pid;
		i++;
	}
}
