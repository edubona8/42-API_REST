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
			log_message ("LOG.log", hm->method.ptr, 200);
		}
		else if (mg_http_match_uri(hm, "/weather")) 
		{
			msg = get_api(1); //obtem o conteudo da API externa que foi requesitada
			mg_http_reply(c, 200, "Content-Type: application/json\r\n", "%s", msg); //retorna a mensagem para o cliente em . JSON
			log_message ("LOG.log", hm->method.ptr, 200); //escreve a mensagem de LOG
		}
		else if (mg_http_match_uri(hm, "/covid"))
		{
			msg = get_api(2);
			mg_http_reply(c, 200, "Content-Type: application/json\r\n", "%s", msg);
			log_message ("LOG.log", hm->method.ptr, 200);
		}
		else if (mg_http_match_uri(hm, "/finance"))
		{
			msg = get_api(3);
			mg_http_reply(c, 200, "Content-Type: application/json\r\n", "%s", msg);
			log_message ("LOG.log", hm->method.ptr, 200);
		}
		else if (mg_http_match_uri(hm, "/tech"))
		{
			msg = get_api(4);
			mg_http_reply(c, 200, "Content-Type: application/json\r\n", "%s", msg);
			log_message ("LOG.log", hm->method.ptr, 200);
		}
		else
		{
			mg_http_reply(c, 404, "Content-Type: application/json\r\n", "{\"result\": \"Página não encontrada\"}");
			log_message ("LOG.log", hm->method.ptr, 404);
		}
	}
}

int	main(int argc, char *argv[])
{
	struct mg_mgr	mgr;

	mg_log_set("4");
	mg_mgr_init(&mgr);// Iniciar gerenciador
	mg_http_listen(&mgr, LOCAL_ROST, fn, &mgr);// Configura o ouvinte HTTP
	for (;;) mg_mgr_poll (&mgr, 1000); /** itera sobre todas as conexões, aceita novas conexões, envia e recebe dados, fecha conexões e 
									   chama funções de manipulador de eventos para os respectivos eventos. */
	mg_mgr_free(&mgr);// Free nas struct
	return (0);
}
