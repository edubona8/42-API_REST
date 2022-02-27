#ifndef SERVER_H
# define SERVER_H


#include "mongoose.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define COVID_URL	"https://covid19-brazil-api.vercel.app/api/report/v1/brazil/uf/sp"
#define	TECH_URL	"https://newsapi.org/v2/everything?q=tech&from=2022-01-25&sortBy=publishedAt&apiKey=82c35576d3cc448986574b64a3753ea7"
#define WEATHER_URL	"https://api.hgbrasil.com/weather?woeid="
#define	FINANCE_URL	"https://api.hgbrasil.com/finance/stock_price?key=af83d52f&symbol=b3sa3"
#define LOCAL_ROST	"http://localhost:8000"

typedef struct s_MemoryStruct
{
	char	*memory;
	size_t	size;
}	t_MemoryStruct;

char	*get_api(int switch_);
void	log_message(const char *filename, const char *message, int status);


#endif