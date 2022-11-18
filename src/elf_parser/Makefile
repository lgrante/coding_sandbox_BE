SRC		=	main.c \
			src/json.c

OBJ		=	$(SRC:.c=.o)

CFLAGS		=	-Wall -I./include

NAME		=	parser

CC		=	gcc

RM		=	rm -f

all: 		$(NAME)

$(NAME):	$(OBJ)
		@printf "\e[1m\e[38;2;21;124;214mCompiling $(NAME)...\033[0m  "
		@gcc -o $(NAME) $(OBJ)
		@printf "Done.\n"

clean:
		@printf "\e[1m\e[38;2;21;124;214mCleaning all object files...\033[0m  "
		@$(RM) $(OBJ)
		@printf "Done.\n"

fclean:		clean
		@printf "\e[1m\e[38;2;21;124;214mCleaning $(NAME)...\033[0m  "
		@$(RM) $(NAME)
		@printf "Done.\n"

re:		fclean all

test:
		@printf "Running test...\n"

.PHONY: all clean fclean re test
