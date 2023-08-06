/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:25:30 by madaguen          #+#    #+#             */
/*   Updated: 2023/08/06 21:47:01 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	waiting(int *pids, int nb_cmd)
{
	int		i;
	pid_t	pid;
	int		status;

	i = 0;
	(void) nb_cmd;
	while (i < nb_cmd)
	{
		pid = waitpid(pids[i], &status, 0);
		if (pid == -1)
			perror("waitpid");
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			return (WTERMSIG(status));
		i++;
	}
	return (status);
}

int	main(int argc, char **argv, char **env_p)
{
	t_env	env;
	int		ret;

	ft_memset(&env, sizeof(t_env), 0);
	env.env = env_p;
	if (!handle_arg(&argv[1], argc - 1, &env))
		return (error("Incorrect arguments\n"), 0);
	if (env.heredoc)
		env.lst_cmd = &argv[3];
	else
		env.lst_cmd = &argv[2];
	env.pids = malloc(sizeof(int) * env.nb_cmd);
	if (!env.pids)
		return (0);
	if (env.heredoc && !get_infile_heredoc(&env))
		return (0);
	if (!env.heredoc && !get_infile(&env, argv[1]))
		return (0);
	if (!get_outfile(&env, argv[argc - 1]))
		return (free_infile(&env), 0);
	exec(&env);
	ret = waiting(env.pids, env.nb_cmd);
	free(env.pids);
	return (ret);
}
