#ifndef CLI_H
# define CLI_H

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>

#define BUFFER_SIZE 42

typedef struct s_data
{
    int root;
    int weather;
    int covid;
    int finance;
    int tech;
    int error;
}              t_data;


char    *get_next_line(int fd);
char    *ft_strdup(char *string);
int        ft_strlen(const char *string);
char    *ft_strjoin(char const *s1, char const *s2);
char    *ft_strchr(const char *string, int character);
size_t    ft_strlcpy(char *destiny, const char *source, size_t destiny_size);
char    *ft_strnstr(const char *big, const char *little, size_t len);
void    init_values(t_data *requests);
void    draw(t_data *requests);


#endif