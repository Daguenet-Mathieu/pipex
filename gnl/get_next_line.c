#include "get_next_line.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


#ifndef BUFFER_SIZE
#define BUFFER_SIZE 150
#endif

int find_c(char *line, int *pos, char c)
{
    int i;

    i = 0;
    if (!line)
    {
        *pos = 0;
        return (0);
    }
    while(line[i] && line[i] != c)
        i++;
    *pos = i;
    return (line[i] == c);
}

char *join_line(char *line, char *buffer, char **tmp)
{
    int     i;
    int     j;
    int     len_l;
    int     len_b;
    int     c;
    char    *res;

    c = 0;
    find_c(line, &len_l, 0);
    find_c(buffer, &len_b, '\n');
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
        res[(i)++] = buffer[j++];
        find_c(&buffer[j], &len_b, 0);
        *tmp = malloc(sizeof(char) * len_b + 1);
        if (!*tmp)
            return (free(line), free(res), NULL);
        c = 0;
        while (buffer[j])
            (*tmp)[c++] = buffer[j++];
        (*tmp)[c] = 0;
    }
    res[i] = 0;
    free(line);
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
    static char buffer[BUFFER_SIZE + 1];

    line = NULL;
    tmp = NULL;
    r = BUFFER_SIZE;
    while (1)
    {
        line = join_line(line, buffer, &tmp);
        if (!line)
            return (free(tmp), NULL);
        ft_memset_2(buffer, 0, BUFFER_SIZE);
        str_copy(buffer, tmp);
        free(tmp);
        tmp = NULL;
        if (find_c(line, &nl, '\n') || r < BUFFER_SIZE)
            break ;
        r = read(fd, buffer, BUFFER_SIZE);
        if (r == -1)
            return(free(line),free(tmp), NULL);
        buffer[BUFFER_SIZE] = 0;
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