#include "CLI.h"


int main()
{
    
    t_data  requests;
    

    int     fd;
    char    *tmp_line;
    
    init_values(&requests);
    fd = open("LOG.log", O_RDONLY);
    if (fd == -1)
		printf("Error.");
    while (1)
	{
		tmp_line = get_next_line(fd);
		if (tmp_line == NULL)
			break ;
	     if (strstr(tmp_line, "GET /"))
            requests.root++;
        if (strstr(tmp_line, "GET /weather"))
            requests.weather++;
        if (strstr(tmp_line, "GET /covid"))
            requests.covid++;
        if (strstr(tmp_line, "GET /finance"))
            requests.finance++;
        if (strstr(tmp_line, "GET /tech"))
            requests.tech++;
        if (strstr(tmp_line, "Status: 404"))
            requests.error++;
        free(tmp_line);
    }
    draw(&requests);
}

void    init_values(t_data *requests)
{
    requests->root = 0;
    requests->weather = 0;
    requests->covid = 0;
    requests->finance = 0;
    requests->tech = 0;
    requests->error = 0;
}

void    draw(t_data *requests)
{
     printf("╔════════════════════════════════════════════════╗\n");
    printf("║Total Requests║  HTTP Method  ║      Path       ║\n");
    printf("║══════════════║═══════════════║═════════════════║\n");
    printf("║      %03d     ║      GET      ║    /            ║\n", requests->root);
    printf("║      %03d     ║      GET      ║    /weather     ║\n", requests->weather);
    printf("║      %03d     ║      GET      ║    /covid       ║\n", requests->covid);
    printf("║      %03d     ║      GET      ║    /finance     ║\n", requests->finance);
    printf("║      %03d     ║      GET      ║    /tech        ║\n",requests->tech);
    printf("║      %03d     ║      GET      ║    ERROR        ║\n",requests->error);
    printf("╚══════════════╩═══════════════╩═════════════════╝  \n");
}