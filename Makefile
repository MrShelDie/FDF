_SRC_ =															\
fdf.c					matrix.c				render.c		\
render_utils.c			render_utils_init.c		parser.c		\
parser_utils_check.c	parser_utils_fill.c		get_next_line.c	\
get_next_line_utils.c	projection.c			transform_map.c	\
transform_point.c		events.c				events_key.c	\
events_mouse.c

SRC			= $(addprefix src/, $(_SRC_))

SRC			+= $(PARS)
SRC			+= $(GNL)

OBJ			= $(SRC:.c=.o)
DEP			= $(SRC:.c=.d)

NAME		= fdf
GNLDIR		= src/get_next_line
PARSDIR		= src/parser
LIBFTDIR	= lib/libft
LIBFT		= lib/libft/libft.a
MLXDIR		= lib/minilibx-linux
MLX			= lib/minilibx-linux/libmlx_Linux.a
INCDIR		= include

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -O3
CPPFLAGS	= -MMD -I./src -I./$(LIBFTDIR) -I./$(GNLDIR) -I./$(PARSDIR) -I./$(MLXDIR) -I./$(INCDIR) 
LDFLAGS		= $(MLX) -lmlx -lXext -lX11 -lm

all:		$(LIBFT) $(MLX) $(NAME)

bonus:		all

$(LIBFT):
	@make -C $(LIBFTDIR) all

$(MLX):
	@make -C $(MLXDIR) all

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) $(LIBFT) -o $@ 

clean:
	@make -C $(LIBFTDIR) clean
	@make -C $(MLXDIR) clean
	$(RM) $(OBJ) $(DEP)

fclean:		clean
	@make -C $(LIBFTDIR) fclean
	$(RM) $(NAME)

re:			fclean all
	@make -C $(LIBFTDIR) re
	@make -C $(MLXDIR) re

.PHONY:		all clean fclean re

-include $(DEP)