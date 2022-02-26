GREEN = \033[0;32m
BLUE = \033[0;34m
RED = \033[0;31m
RESET = \033[0m

NAME_CLI = CLI_
NAME_SERVER = API

CLI_DIR = ./CLI/
SERVER_DIR = ./SERVER/

CLI =        $(addprefix $(CLI_DIR), \
            cli.c\
            get_next_line.c\
            get_next_line_utils.c\
			)

SERVER =    $(addprefix $(SERVER_DIR), \
			server.c\
			mongoose.c\
			get_api.c\
			log_server.c\
			)

OBJS_CLI = $(CLI:.c=.o)
OBJS_SERVER = $(SERVER:.c=.o)

cli: $(NAME_CLI)

$(NAME_CLI): $(OBJS_CLI)
	gcc $(OBJS_CLI) -o $(NAME_CLI)
	@echo "$(BLUE)"
	@echo "██╗ ██╗ ██████╗ ██╗       ███╗   ██████╗  ██████╗ "
	@echo "██║ ██║     ██║ ██║      █████╗  ██   ██╗ ██╔═══╝ "
	@echo "██████║ ██████║ ██║     ██   ██╗ █████╔═╝ ██████╗ "
	@echo "    ██║ ██╔═══╝ ██║     ███████║ ██   ██╗     ██║ "
	@echo "    ██║ ██████╗ ██████╗ ██║  ██║ ██████╔╝ ██████║ "
	@echo "    ╚═╝ ╚═════╝ ╚═════╝ ╚═╝  ╚═╝ ╚═════╝  ╚═════╝ "
	@echo "                    CLI is Done!        $(RESET)  "
	@echo "                                                  "

server: $(NAME_SERVER)

$(NAME_SERVER): $(OBJS_SERVER)
	gcc $(OBJS_SERVER) -lcurl -o $(NAME_SERVER)
	@echo "$(GREEN)"
	@echo "██╗ ██╗ ██████╗ ██╗       ███╗   ██████╗  ██████╗ "
	@echo "██║ ██║     ██║ ██║      █████╗  ██   ██╗ ██╔═══╝ "
	@echo "██████║ ██████║ ██║     ██   ██╗ █████╔═╝ ██████╗ "
	@echo "    ██║ ██╔═══╝ ██║     ███████║ ██   ██╗     ██║ "
	@echo "    ██║ ██████╗ ██████╗ ██║  ██║ ██████╔╝ ██████║ "
	@echo "    ╚═╝ ╚═════╝ ╚═════╝ ╚═╝  ╚═╝ ╚═════╝  ╚═════╝ "
	@echo "                   Server is Done!        $(RESET)"
	@echo "                                                  "

%.o: %.c
	gcc $(CFLAG) -c $< -o $@

clean:
	rm -f $(OBJS_CLI) $(OBJS_SERVER)

fclean: clean
	rm -f $(NAME_CLI) $(NAME_SERVER)

re_server: fclean server

re_cli: fclean cli