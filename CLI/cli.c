#include "get_next_line.h"

int main()
{
    int     request_4;
    int     request_8;
    int     request_10;
    int     request_20;
    int     fd;
    char    *tmp_line;

    request_4 = 0;
    request_8 = 0;
    request_10 = 0;
    request_20 = 0;

    fd = open("../LOG.log", O_RDONLY);
    if (fd == -1)
		printf("Error.");
    while (1)
	{
		tmp_line = get_next_line(fd);
		if (tmp_line == NULL)
			break ;
		if (ft_strnstr(tmp_line, "GET /4", ft_strlen("GET /4")))
            request_4++;
        if (ft_strnstr(tmp_line, "GET /8", ft_strlen("GET /8")))
            request_8++;
        if (ft_strnstr(tmp_line, "GET /10", ft_strlen("GET /10")))
            request_10++;
        if (ft_strnstr(tmp_line, "GET /20", ft_strlen("GET /20")))
            request_20++;
	}

    printf("|----------------------------------------------|\n");
    printf("|Total Requests|  HTTP Method  |      Path     |\n");
    printf("|--------------|---------------|---------------|\n");
    printf("|      %03d     |      GET      |      /4       |\n", request_4);
    printf("|      %03d     |      GET      |      /8       |\n", request_8);
    printf("|      %03d     |      GET      |      /10      |\n", request_10);
    printf("|      %03d     |      GET      |      /20      |\n", request_20);
    printf("|--------------|---------------|---------------|\n");
}