#include "server.h"

static size_t	write_memory_call_back(void *contents, size_t size,
size_t nmemb, void *userp)
{
	size_t	realsize;
	t_MemoryStruct	*mem;
	char	*ptr;

	realsize = size * nmemb;
	mem = (t_MemoryStruct *)userp;
	ptr = realloc(mem->memory, mem->size + realsize + 1);
	if (!ptr)
	{
		printf("not enough memory (realloc returned NULL)\n");
		return (0);
	}
	mem->memory = ptr;
	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;
	return (realsize);
}

char	*get_api(int switch_)
{
	CURL	*curl;
	CURLcode	res;
	t_MemoryStruct	chunk;
	char	url[256];
	
	chunk.memory = malloc(1);
	chunk.size = 0;
	curl = curl_easy_init();
	if (!curl)
	{
		fprintf(stderr, "[-] Failed Initializing Curl\n");
		exit(-1);
	}
	
	if(switch_ == 1)
		strcpy(url, WEATHER_URL);
	else if(switch_ == 2)
		strcpy(url, COVID_URL);
	else if(switch_ == 3)
		strcpy(url, FINANCE_URL);
	else if(switch_ == 4)
		strcpy(url, TECH_URL);
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_memory_call_back);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
	res = curl_easy_perform(curl);
	if (res != CURLE_OK)
	{
		fprintf(stderr,
			"[-] Could Not Fetch Webpage\n[+] Error : %s\n",
			curl_easy_strerror(res));
		exit(-2);
	}
	curl_easy_cleanup(curl);
	// printf("%s\n", chunk.memory);
	return (chunk.memory);
}