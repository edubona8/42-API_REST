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
	char					*uri_id;

	//game = "455827";
	if (ev == MG_EV_HTTP_MSG)
	{
		hm = (struct mg_http_message *)ev_data;
		if (mg_http_match_uri(hm, "/"))
		{
			mg_http_reply(c, 200, "Content-Type: application/json\r\n", "{\"result\": Portal de informações 42Labs Selecione sua notícia}", result_api);
			log_message ("LOG.log", hm->method.ptr, 200);
		}

		else if (mg_http_match_uri(hm, "/weather"))
		{
			uri_id = "455827";
			result_api = get_api(uri_id, 1);
			mg_http_reply(c, 200, "Content-Type: application/json\r\n", "%s\n", result_api);
			log_message ("LOG.log", hm->method.ptr, 200);
		}
		else if (mg_http_match_uri(hm, "/covid"))
		{
			result_api = get_api(NULL, 2);
			mg_http_reply(c, 200, "Content-Type: application/json\r\n", "%s", result_api);
			log_message ("../LOG.log", hm->method.ptr, 200);
		}
		else if (mg_http_match_uri(hm, "/finance"))
		{
			result_api = get_api(NULL, 3);
			mg_http_reply(c, 200, "Content-Type: application/json\r\n", "%s", result_api);
			log_message ("../LOG.log", hm->method.ptr, 200);
		}
		else
		{
			mg_http_reply(c, 404, "Content-Type: application/json\r\n", "{\"result\": \"Página não encontrada\"}");
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
