# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afidalgo <afidalgo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/15 16:37:55 by alvicina          #+#    #+#              #
#    Updated: 2024/03/12 18:44:11 by afidalgo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#SETUP

NAME            = cub3D
CC              = gcc
RM              = rm -rf
FLAGS           = -Wall -Wextra -Werror -Ilibft -Imlx  #-g3 -fsanitize=address

#FILES AND PATH

HEADER_SRCS = cub3D.h
HEADER_DIR  = includes/
HEADER      = $(addprefix $(HEADER_DIR), $(HEADER_SRCS))

MPATH_SRCS  = main.c copy_file.c utils_copy_file_map_position.c check_map_position.c \
			  split_map_specifications.c specifications_checker.c specifications_checker_utils.c \
			  color_validation.c check_file_last_part.c map_validation.c map_validation_utils.c \
			  make_square_map.c check_player_and_left.c gui_init.c player_init.c player_movement.c \
			  player_direction.c gui_event_handler.c map_walls.c map_wall_dir.c map_render.c \
			  map_render_walls.c map_position.c mlx_utils.c utils.c gui_init_utils.c get_addr_utils.c

MPATH_DIR   = mandatory/
MPATH       = $(addprefix $(MPATH_DIR), $(MPATH_SRCS))
OBJ_M       = $(MPATH:.c=.o)

BPATH_SRCS  = 
BPATH       = $(addprefix $(BPATH_DIR), $(BPATH_SRCS))
OBJ_B       = $(BPATH:.c=.o)

#COMMANDS
all:        lib $(NAME)

$(NAME):    $(OBJ_M)
		    @$(CC) $(FLAGS) -o $(NAME) $(OBJ_M) -lm -Llibft -lft -Lmlx -lmlx -lGL -lX11 -lXext

%.o: %.c $(HEADER) Makefile
		    @$(CC) $(FLAGS) -c $< -o $@

bonus:      lib $(OBJ_B)
			@$(CC) $(FLAGS) $(OBJ_B) -o $(NAME) -lm -Llibft -lft -Lmlx -lmlx -lGL -lX11 -lXext

clean:
	        @$(RM) $(OBJ_M)
			@$(RM) $(OBJ_B)
	        $(MAKE) -C libft clean
			$(MAKE) -C mlx clean

fclean:	    clean
		    @$(RM) $(NAME)

re:         fclean all

lib:
	        $(MAKE) -C libft 
			$(MAKE) -C mlx

.PHONY: all execute clean fclean re lib