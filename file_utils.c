/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:24:52 by madaguen          #+#    #+#             */
/*   Updated: 2023/08/06 22:50:05 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_infile(t_env *env)
{
	if (env->infile.fd && env->infile.file_name)
		close(env->infile.fd);
	free(env->infile.file_name);
	env->infile.file_name = NULL;
}

void	free_outfile(t_env *env)
{
	if (env->outfile.fd && env->outfile.file_name)
		close(env->outfile.fd);
	free(env->outfile.file_name);
	env->outfile.file_name = NULL;
}

int	get_outfile(t_env *env, char *argv)
{
	env->outfile.file_name = (unsigned char *)ft_strdup(argv);
	if (!env->outfile.file_name)
		return (0);
	env->outfile.fd = get_fd(env->outfile.file_name, OUTFILE, env->heredoc);
	if (env->outfile.fd == -1)
	{
		bash_error("bash: ", (char *)env->outfile.file_name, \
		" Permission denied\n");
		return (0);
	}
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
