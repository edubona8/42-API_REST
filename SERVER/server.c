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

static void	fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data)
{
	int	aux;
	struct mg_http_message	*hm;
	char					*result_api;
	char					*game;

	game = "noita";
	if (ev == MG_EV_HTTP_MSG)
	{
		hm = (struct mg_http_message *)ev_data;
		if (mg_http_match_uri(hm, "/"))
		{
			result_api = get_api(game);
			mg_http_reply(c, 200, "Content-Type: application/json\r\n", "%s", result_api);
			log_message ("LOG.log", hm->method.ptr, 200);
		}

		else if (mg_http_match_uri(hm, "/4"))
		{
			aux = rand() % 4;
			mg_http_reply(c, 200, "Content-Type: application/json\r\n", "{\"result\": %d}", aux);
			log_message ("../LOG.log", hm->method.ptr, 200);
		}
		else if (mg_http_match_uri(hm, "/6"))
		{
			aux = rand() % 6;
			mg_http_reply(c, 200, "Content-Type: application/json\r\n", "{\"result\": %d}", aux);
			log_message ("../LOG.log", hm->method.ptr, 200);
		}
		else if (mg_http_match_uri(hm, "/10"))
		{
			aux = rand() % 10;
			mg_http_reply(c, 200, "Content-Type: application/json\r\n", "{\"result\": %d}", aux);
			log_message ("../LOG.log", hm->method.ptr, 200);
		}
		else if (mg_http_match_uri(hm, "/20"))
		{
			aux = rand() % 20;
			mg_http_reply(c, 200, "Content-Type: application/json\r\n", "{\"result\": %d}", aux);
			log_message ("../LOG.log", hm->method.ptr, 200);
		}
		else
		{
			mg_http_reply(c, 404, "Content-Type: application/json\r\n", "{\"result\": \"Escolha um dado: Dado não encontrado\"}");
			log_message ("../LOG.log", hm->method.ptr, 404);
		}
	}
}

int	main(int argc, char *argv[])
{
	struct mg_mgr	mgr;

	mg_log_set("4");
	mg_mgr_init(&mgr);// Init manager
	mg_http_listen(&mgr, "http://localhost:8000", fn, &mgr);// Setup listener
	for (;;) mg_mgr_poll (&mgr, 1000);// Event loop
	mg_mgr_free(&mgr);// Cleanup
	return (0);
}
