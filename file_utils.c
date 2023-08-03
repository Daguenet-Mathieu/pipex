/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:24:52 by madaguen          #+#    #+#             */
/*   Updated: 2023/08/03 17:42:02 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_infile(t_env *env)
{
	close(env->infile.fd);
	free(env->infile.file_name);
	env->infile.file_name = NULL;
}

void	free_outfile(t_env *env)
{
	close(env->outfile.fd);
	free(env->outfile.file_name);
	env->outfile.file_name = NULL;
}