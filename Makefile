_SRC_ =															\
fdf.c				matrix.c			render.c				\
render_utils.c		parser.c			parser_utils_check.c	\
parser_utils_fill.c get_next_line.c		get_next_line_utils.c	\
projection.c		transform_map.c		transform_point.c		\
events.c			events_key.c		events_mouse.c

SRC			= $(addprefix src/, $(_SRC_))

SRC			+= $(PARS)
SRC			+= $(GNL)

OBJ			= $(SRC:.c=.o)
DEP			= $(SRC:.c=.d)

NAME		= fdf
GNLDIR		= src/get_next_line
PARSDIR		= src/parser
LIBFTDIR	= lib/libft
LIB			= lib/libft/libft.a
MLXDIR		= lib/minilibx-linux
MLX			= lib/minilibx-linux/libmlx_Linux.a
INCDIR		= include

CC			= gcc
CFLAGS		= -g #-Wall -Werror -Wextra -g
CPPFLAGS	= -MMD -I./src -I./$(LIBFTDIR) -I./$(GNLDIR) -I./$(PARSDIR) -I./$(MLXDIR) -I./$(INCDIR) 
LDFLAGS		= $(MLX) -lmlx -lXext -lX11 -lm

all:		$(NAME)

$(NAME):	$(OBJ)
	@make -C $(LIBFTDIR) all
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) $(LIB) -o $@ 

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