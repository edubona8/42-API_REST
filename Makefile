GREEN        =    \033[0;32m
RED            =    \033[0;31m
RESET        =    \033[0m
LIB = -lcurl
CC            =    gcc
NAME = API
DIR				:=	./SERVER/

SRC := $(addprefix $(DIR),\
get_body.c \
log_server.c \
server.c \
)
MONGOOSE    =    LIBS/mongoose.a
##GNL         =    get_next_line/get_next_line.a

OBJS			:=	${SRC:%.c=%.o}

.c.o:
				$(CC) -c $< -o $(<:.c=.o)

all:            $(MONGOOSE) $(NAME) ##$(GNL)
				@echo "$(GREEN)"
				@echo "██╗ ██╗ ██████╗ ██╗         ██╗     ███████╗ "
				@echo "██║ ██║     ██║ ██║        ████╗    ██    ██╗"
				@echo "██████║ ██████║ ██║      ██    ██╗  ██████╔═╝"
				@echo "    ██║ ██╔═══╝ ██║      ████████║  ██    ██╗"
				@echo "    ██║ ██████╗ ███████╗ ██║   ██║  ███████╔╝"
				@echo "    ╚═╝ ╚═════╝ ╚══════╝ ╚═╝   ╚═╝  ╚══════╝ "
				@echo "           Everything is Done!$(RESET)"


##$(GNL):
               ## make -C ./get_next_line/
               ## @echo "\n $(GREEN)$(MONGOOSE) was created $(RESET)\n"
$(MONGOOSE):
				make -C ./LIBS/
				@echo "\n $(GREEN) $(MONGOOSE) was created $(RESET)\n"

$(NAME):    $(MONGOOSE) $(OBJS)
				$(CC) $(MONGOOSE)  $(OBJS) $(LIB) -o $(NAME) 					
				

clean:
			@echo "\n $(RED) Removing *.o files $(RESET)\n"
			rm -f $(OBJS) $(OBJS_BONUS)
			make clean -C ./LIBS

fclean:            clean
			@echo "\n $(RED) Removing files *.o and *.a files $(RESET)\n"
			rm -f $(NAME) $(NAME_BONUS)
			make fclean -C ./LIBS


runserver: $(SERVER) $(mongoose)

re:			fclean all

.PHONY:         all, clean, fclean, re