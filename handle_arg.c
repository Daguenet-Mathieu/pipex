# include "pipex.h"

int	handle_arg(char **argv, int size, t_env *env)
{
	if (size < 4)
		return (0);
	if (!ft_strncmp(argv[0], "here_doc", 8))
		env->heredoc = 1;
	if (env->heredoc && size < 5)
		return (0);
	else if (!env->heredoc)
		env->nb_cmd = size - 2;
	else
		env->nb_cmd = size - 3;
	return (1);
}