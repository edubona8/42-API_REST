#include "mongoose.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#include <curl/curl.h>
 
typedef struct s_MemoryStruct
{
    char    *memory;
    size_t    size;
}    t_MemoryStruct;

static size_t    write_memory_call_back(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t            realsize;
    t_MemoryStruct    *mem;
    char            *ptr;

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

char    *ft_curl(void)
{
    CURL            *curl;
    CURLcode        res;
    t_MemoryStruct    chunk;

    chunk.memory = malloc(1);
    chunk.size = 0;
    curl = curl_easy_init();
    if (!curl)
    {
        fprintf(stderr, "[-] Failed Initializing Curl\n");
        exit(-1);
    }
    curl_easy_setopt(curl, CURLOPT_URL, "https://www.mercadobitcoin.net/api/BTC/ticker/");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_memory_call_back);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        fprintf(
            stderr,
            "[-] Could Not Fetch Webpage\n[+] Error : %s\n",
            curl_easy_strerror(res));
        exit(-2);
    }
    curl_easy_cleanup(curl);
    // printf("%s\n", chunk.memory);
    return (chunk.memory);
}
void log_message(const char *filename, const char *message, int status)
{
    time_t curtime;
    FILE *fp = fopen(filename, "a");

    time(&curtime);
    if (fp != NULL)
    {
        fprintf(fp, "Status: %d\n", status);
        fprintf(fp, "Ultima requisição: %s", ctime(&curtime));
        fprintf(fp, "%s", message);
        fclose(fp);
    }
}

static void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) 
{  
    int aux;
    struct mg_http_message *hm;

  
    if (ev == MG_EV_HTTP_MSG) 
    {
        
        hm = (struct mg_http_message *)ev_data;
        if (mg_http_match_uri(hm, "/"))
        {
            get_api();
            mg_http_reply(c, 200, "Content-Type: application/json\r\n", "{\"result\": %s}", aux);
            log_message("LOG.log", hm->method.ptr,200);
        }
        
        else if (mg_http_match_uri(hm, "/4"))
        {
            aux = rand() % 4;
            mg_http_reply(c, 200, "Content-Type: application/json\r\n", "{\"result\": %d}", aux);
            log_message("LOG.log", hm->method.ptr,200);
        }
        else if(mg_http_match_uri(hm, "/6"))
        {
            aux = rand() % 6;
            mg_http_reply(c, 200, "Content-Type: application/json\r\n", "{\"result\": %d}", aux);
            log_message("LOG.log", hm->method.ptr,200);
        }
         else if(mg_http_match_uri(hm, "/10"))
        {
            aux = rand() % 10;
            mg_http_reply(c, 200, "Content-Type: application/json\r\n", "{\"result\": %d}", aux);
            log_message("LOG.log", hm->method.ptr,200);
        }
         else if(mg_http_match_uri(hm, "/20"))
        {
            aux = rand() % 20;
            mg_http_reply(c, 200, "Content-Type: application/json\r\n", "{\"result\": %d}", aux);
            log_message("LOG.log", hm->method.ptr,200);
        }
        else 
        {   
            mg_http_reply(c, 404, "Content-Type: application/json\r\n", "{\"result\": \"Escolha um dado: Dado não encontrado\"}");
            log_message("LOG.log", hm->method.ptr ,404);
        }    
    }   
}

int main(int argc, char *argv[]) {
  struct mg_mgr mgr;
  mg_log_set("4");
  mg_mgr_init(&mgr);                                        // Init manager
  mg_http_listen(&mgr, "http://localhost:8000", fn, &mgr);  // Setup listener
  for (;;) mg_mgr_poll(&mgr, 1000);                         // Event loop
  mg_mgr_free(&mgr);                                        // Cleanup
  return 0;
}