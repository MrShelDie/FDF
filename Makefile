_SRC_		= fdf.c
_PARS_		= parser.c			parser_utils.c
_GNL_		= get_next_line.c	get_next_line_utils.c

SRC			= $(addprefix src/, $(_SRC_))
PARS		= $(addprefix src/parser/, $(_PARS_))
GNL			= $(addprefix src/get_next_line/, $(_GNL_))

SRC			+= $(PARS)
SRC			+= $(GNL)

OBJ			= $(SRC:.c=.o)
DEP			= $(SRC:.c=.d)

NAME		= fdf
GNLDIR		= src/get_next_line
PARSDIR		= src/parser
LIBFTDIR	= lib/libft
LIB			= lib/libft/libft.a

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -g
CPPFLAGS	= -MMD -I./src -I./$(LIBFTDIR) -I./$(GNLDIR) -I./$(PARSDIR)

all:		$(NAME)

$(NAME):	$(OBJ)
	@make -C $(LIBFTDIR) all
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $@ 

clean:
	@make -C $(LIBFTDIR) clean
	$(RM) $(OBJ) $(DEP)

fclean:		clean
	@make -C $(LIBFTDIR) fclean
	$(RM) $(NAME)

re:			fclean all
	@make -C $(LIBFTDIR) re

.PHONY:		all clean fclean re

-include $(DEP)