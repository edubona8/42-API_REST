#include "server.h"

void	log_message(const char *filename, const char *message, int status)
{
	time_t	curtime;
	FILE	*fp = fopen(filename, "a");

	time(&curtime);
	if (fp != NULL)
	{
		fprintf(fp, "Status: %d\n", status);
		fprintf(fp, "Ultima requisição: %s", ctime(&curtime));
		fprintf(fp, "%s", message);
		fclose(fp);
	}
}