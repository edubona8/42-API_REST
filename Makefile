GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

.DEFAULT_GOAL    :=    all

NAME = API

SRC = mongoose.c server.c

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	gcc $(OBJS) -o $(NAME)
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

%.o: %.c
	gcc $(CFLAG) -c $< -o $@
	@echo "\n$(NAME): $(GREEN)object files were created$(RESET)"

clean:
	rm -f $(OBJS)
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"

fclean: clean
	rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"

re: fclean all

.PHONY: clean fclean re all