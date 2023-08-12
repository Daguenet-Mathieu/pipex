/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 21:19:27 by madaguen          #+#    #+#             */
/*   Updated: 2023/08/10 21:09:29 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	handle_arg(char **argv, int size, t_env *env)
{
	if (size < 4)
		return (0);
	if (!ft_strncmp(argv[0], "here_doc", 9))
		env->heredoc = 1;
	if (env->heredoc && size < 5)
		return (0);
	else if (!env->heredoc)
		env->nb_cmd = size - 2;
	else
		env->nb_cmd = size - 3;
	return (1);
}
