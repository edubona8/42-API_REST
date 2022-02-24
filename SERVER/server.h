#ifndef SERVER_H
# define SERVER_H


#include "../LIBS/mongoose.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

typedef struct s_MemoryStruct
{
	char	*memory;
	size_t	size;
}	t_MemoryStruct;

char	*get_api(char *game);
void	log_message(const char *filename, const char *message, int status);


#endif