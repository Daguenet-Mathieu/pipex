/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:24:57 by madaguen          #+#    #+#             */
/*   Updated: 2023/08/01 19:24:58 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int check_nl(char *line, int *nl)
{
    int i;

    i = 0;
    while(line && line[i] && line[i] != '\n')
    {
        i++;
    }
    *nl = i;
    return (line[i] == '\n');
}

char *join_line(char *line, char *buffer, char **tmp)
{
    int     i;
    int     j;
    int     len_l;
    int     len_b;
    char    *res;
    int     c;

    len_l = ft_strlen(line);
    check_nl(buffer, &len_b);
    res = malloc(sizeof(char) * (len_l + len_b + 1 + 1));
    if (!res)
        return (free(line), NULL);
    i = 0;
    while (line && line[i])
    {
        res[i] = line[i];
        i++;
    }
    j = 0;
    while (buffer[j] && buffer[j] != '\n')
        res[i++] = buffer[j++];
    if (buffer[j] == '\n')
    {
        res[i++] = buffer[j++];
        len_b = ft_strlen(&buffer[j]);
        *tmp = malloc(sizeof(char) * len_b + 1);
        if (!*tmp)
            return (free(line), free(res), NULL);
        c = 0;
        while (buffer[j])
            (*tmp)[c++] = buffer[j++];
        (*tmp)[c] = 0;
    }
    free(line);
    res[i] = 0;
    return (res);
}

void    str_copy(char *buffer, char *tmp)
{
    int i;

    i = 0;
    while (tmp && tmp[i])
    {
        buffer[i] = tmp[i];
        i++;
    }
    buffer[i] = 0;
}

void    ft_memset_2(char *buffer, char c, int size)
{
    int i;

    i = 0;
    while (i < size)
    {
        buffer[i] = c;
        i++;
    }
}

char    *get_next_line(int fd)
{
    int         nl;
    int         r;
    char        *line;
    char        *tmp;
    static char buffer[151];

    line = NULL;
    tmp = NULL;
    r = 150;
    while (1)
    {
        line = join_line(line, buffer, &tmp);
        if (!line)
            return (free(tmp), NULL);
        ft_memset_2(buffer, 0, 150);
        str_copy(buffer, tmp);
        free(tmp);
        tmp = NULL;
        if (check_nl(line, &nl) || r < 150)
            break ;
        r = read(fd, buffer, 150);
        if (r == -1)
            return(free(line),free(tmp), NULL);
        buffer[150] = 0;
    }
    if (line && !*line)
    {
        free(line);
        line = NULL;
    }
    return (line);
}

/*int main(void)
{
    int fd;
    char    *line;

    fd = open("test.txt", O_RDONLY);
    line = get_next_line(fd);
    printf("line = %s", line);
    free(line);
    line = get_next_line(fd);
    printf("line = %s", line);
    free(line);
    line = get_next_line(fd);
    printf("line = %s", line);
    free(line);
    line = get_next_line(fd);
    printf("line = %s", line);
    free(line);
    line = get_next_line(fd);
    printf("line = %s", line);
    free(line);
    line = get_next_line(fd);
    printf("line = %s", line);
    free(line);
    line = get_next_line(fd);
    printf("line = %s", line);
    free(line);
    line = get_next_line(fd);
    printf("line = %s", line);
    free(line);
  //  line = get_next_line(fd);
 //   printf("line = %s", line);
   // while ((line = get_next_line(fd)))
  //  {
      //  printf("%s\n", line);
     //   if (line[0] == 0)
     //       return (0);
     //   free(line);
   // }
}*/