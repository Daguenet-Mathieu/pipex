/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 21:18:56 by madaguen          #+#    #+#             */
/*   Updated: 2023/08/09 17:42:07 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_invalide_in(t_env *env)
{
	bash_error("bash: ", (char *)env->infile.file_name, \
	": No such file or directory\n");
	free_infile(env);
	close(env->pipe[WRITE]);
	close(env->pipe[READ]);
	free_outfile(env);
	free(env->pids);
	exit(127);
}
