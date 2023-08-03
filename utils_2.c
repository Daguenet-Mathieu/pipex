/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:25:28 by madaguen          #+#    #+#             */
/*   Updated: 2023/08/01 19:25:29 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char    *ft_strjoin(char *s1, char *s2, char c)
{
    int		i;
    int		size;
    char	*s3;
    int		j;

    i = 0;
	j = 0;
    size = ft_strlen(s1) + ft_strlen(s2);
    if (c)
        size = size + 1;
    s3 = malloc(sizeof(char) * size + 1);
    if (!s3)
        return (NULL);
    while (s1[i])
    {
        s3[i] = s1[i];
        i++;
    }
    if (c)
        s3[i++] = c;
    while (s2[j])
    {
        s3[i] = s2[j];
        i++;
		j++;
    }
    s3[i] = 0;
    return (s3);
}

char    *ft_strdup(char *s1)
{
    int     i;
    char    *s2;

    i = 0;
    s2 = malloc (sizeof(char) * ft_strlen(s1) + 1);
    if (!s2)
        return (NULL);
    while (s1[i])
    {
        s2[i] = s1[i];
        i++;
    }
    s2[i] = 0;
    return (s2);
}