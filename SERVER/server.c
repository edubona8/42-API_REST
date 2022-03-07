/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonamic <ebonamic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 21:50:36 by ebonamic          #+#    #+#             */
/*   Updated: 2022/02/24 21:50:37 by ebonamic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "server.h"

int	open_db(const char *datetime, const char *cases, const char *deaths);
int	parse_json(char *body);

/**
 * @brief		Uma função de manipulador de eventos que faz a requisição para  outra API dependendo
 *				da rota e escreve uma mensagem de log.
 *
 * @param    c			Uma conexão que o evento recebeu.
 * @param    ev			Um número de evento, definido em mongoose.h. Por exemplo,
*					quando os dados chegam em uma conexão de entrada
 * @param    ev_data	Aponta para algum dado especifico do evento
 * @param    fn_data	Um ponteiro arbitrário, que será passado como fn_data quando um manipulador de eventos 
 * 					for chamado. Este ponteiro vai ser armazenado em uma struct de conexão como a c->fn_data
 */
static void	fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data)
{
	struct mg_http_message	*hm;
	char					*msg;


	if (ev == MG_EV_HTTP_MSG) //verifica se a mensagem recebida é uma requisição HTTP
	{
		hm = (struct mg_http_message *)ev_data; //recebe a mensagem que foi feita na requisição do cliente
		if (mg_http_match_uri(hm, "/")) //compara a mensagem recebida com a rota
		{
			mg_http_reply(c, 200, "Content-Type: application/json\r\n", "{\"result\": \"Bem vindo a 42LabsNEWS selecione um tópico!\"}");
			log_message ("server.log", hm->method.ptr, 200);
		}
		else if (mg_http_match_uri(hm, "/weather")) 
		{
			msg = get_api(1); //obtem o conteudo da API externa que foi requesitada
			mg_http_reply(c, 200, "Content-Type: application/json\r\n", "%s", msg); //retorna a mensagem para o cliente em . JSON
			log_message ("server.log", hm->method.ptr, 200); //escreve a mensagem de LOG
		}
		else if (mg_http_match_uri(hm, "/covid"))
		{
			msg = get_api(2);
			parse_json(msg);
			mg_http_reply(c, 200, "Content-Type: application/json\r\n", "%s", msg);
			log_message ("server.log", hm->method.ptr, 200);
		}
		else if (mg_http_match_uri(hm, "/finance"))
		{
			msg = get_api(3);
			mg_http_reply(c, 200, "Content-Type: application/json\r\n", "%s", msg);
			log_message ("server.log", hm->method.ptr, 200);
		}
		else if (mg_http_match_uri(hm, "/tech"))
		{
			msg = get_api(4);
			mg_http_reply(c, 200, "Content-Type: application/json\r\n", "%s", msg);
			log_message ("server.log", hm->method.ptr, 200);
		}
		else
		{
			mg_http_reply(c, 404, "Content-Type: application/json\r\n", "{\"result\": \"Página não encontrada\"}");
			log_message ("server.log", hm->method.ptr, 404);
		}
	}
}

int	main(int argc, char *argv[])
{
	struct mg_mgr	mgr;

	mg_log_set("4");
	mg_mgr_init(&mgr);// Inicia o  gerenciador
	mg_http_listen(&mgr, LOCAL_ROST, fn, &mgr);// Configura o ouvinte HTTP
	for (;;) mg_mgr_poll (&mgr, 1000); /** itera sobre todas as conexões, aceita novas conexões, envia e recebe dados, fecha conexões e 
									   chama funções de manipulador de eventos para os respectivos eventos. */
	mg_mgr_free(&mgr);// Free na struct
	return (0);
}

int parse_json(char *body) {

	struct json_object *parsed_json;
	struct json_object *datetime;
	struct json_object *cases;
	struct json_object *deaths;

	parsed_json = json_tokener_parse(body);

	json_object_object_get_ex(parsed_json, "deaths", &deaths);
	json_object_object_get_ex(parsed_json, "cases", &cases);
	json_object_object_get_ex(parsed_json, "datetime", &datetime);
	open_db(
		json_object_get_string(datetime),
		json_object_get_string(cases),
		json_object_get_string(deaths)
	);	
}


int	open_db(const char *datetime, const char *cases, const char *deaths)
{
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	char *sql;

   rc = sqlite3_open("test.db", &db);

   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stderr, "Opened database successfully\n");
   }

   sql = "CREATE TABLE DATA_COVID("  \
      "ID INTEGER PRIMARY KEY 	AUTOINCREMENT," \
      "DATETIME	TEXT	NOT NULL," \
      "CASES	TEXT	NOT NULL," \
      "DEATHS	TEXT	NOT NULL );";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);

   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Table created successfully\n");
   }
  
  sql = sqlite3_mprintf(
            "INSERT INTO DATA_COVID (DATETIME, CASES, DEATHS)    \
            VALUES ('%q', '%q','%q');",
            datetime, cases, deaths);

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
   
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Records created successfully\n");
   }
   sqlite3_close(db);
   return 0; 
}