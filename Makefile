# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: jdesbord <jdesbord@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/11/21 17:29:53 by jdesbord     #+#   ##    ##    #+#        #
#    Updated: 2019/12/11 23:51:44 by jdesbord    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

# **************************************************************************** #
#								VARIABLES									   #
# **************************************************************************** #
HEADER		=					./includes/cube.h
MINILIBX	=					libmlx.a
MINILIBXS	=					minilibx/libmlx.a
LIB			=					libftprintf.a
LIBS		=					Libftprintf/libftprintf.a
SRC_PATH	=					sources
SRCS_NAME	= 					cube.c colors.c mapcheck.c raycast.c readmap.c\
								xpmparser.c movemanager.c windowmanager.c\
								utilities.c freefile.c collisions_bonus.c\
								hud_init.c hud_bonus.c gun_bonus.c\
								enemies_list.c enemy_renderer.c enemy_path.c\
								bmpconverter.c enemy_shoot.c player_shoot.c
OBJS		= 					${SRCS:.c=.o}
FW_PATH 	= 					./frameworks
LIBSDL2 	= 					-framework SDL2 -F $(FW_PATH) -framework SDL2_mixer -rpath $(FW_PATH)
LIBRARIES 	= 					$(LIBSDL2) $(LIBS) $(MINILIBXS)
NAME		= 					Cub3D
RM			= 					rm -f
FLAGS 		= 					-Wall -Wextra -Werror -g3
GFLAGS 		=					-Wall -Wextra -Werror -g3 -fsanitize=address -lmlx -framework OpenGL -framework AppKit\
								-I$(INCLUDE_PATH)\
								-I./$(LIBSDLMIXER)/\
								-I$(FW_PATH)/SDL2.framework/Headers/\
								-I$(FW_PATH)/SDL2_mixer.framework/Headers/
GFLAGS2 	=					-Wall -Wextra -Werror -g3\
								-I./$(LIBSDLMIXER)/\
								-I$(INCLUDE_PATH)\
								-I$(FW_PATH)/SDL2.framework/Headers/\
								-I$(FW_PATH)/SDL2_mixer.framework/Headers/
SRCS 		= 					$(addprefix $(SRC_PATH)/,$(SRCS_NAME))
INCLUDE_PATH = 					./includes

# **************************************************************************** #
#								REGLES									       #
# **************************************************************************** #
all:							$(NAME)
%.o: %.c 						$(HEADER) $(LIBS) $(MINILIBXS)
								@echo "\033[0;32m[OK] \033[0m \033[0;33m Compiling:\033[0m" $<
								@gcc  $(GFLAGS2) -I $(HEADER) -c $< -o $@
$(NAME):						$(MINILIBX) $(LIB) CUBE $(OBJS) $(HEADER)
								@gcc  $(OBJS) -L minilibx $(GFLAGS) $(LIBRARIES) -o $(NAME) -lm
								@echo "\x1b[36m\n[OK] \033[0m \x1b[35m Compiling Cube3D\033[0m"
$(MINILIBX) :
								@$(MAKE) -C minilibx all
$(LIB):
								@$(MAKE) -C Libftprintf all
clean:
								@$(MAKE) -C Libftprintf clean
								@$(MAKE) -C minilibx clean
								@echo "\x1b[36m[OK] \033[0m \x1b[34m Removing ALL File object\033[0m"
								@$(RM) $(OBJS)
fclean:							clean
								@$(MAKE) -C Libftprintf fclean
								@echo "\x1b[36m[OK] \033[0m \x1b[32m All is Removing\033[0m"
								@$(RM) $(NAME)
re:								fclean all
bonus:							all
CUBE:
								@echo ---------------------------------------------
								@echo "	 __,,  , __, __,  ,  ,  __, "
								@echo "	|   |  | |_)|__   |__| |  \ "
								@echo "	|__ |__| |_)|__      | |_ / "
								@echo "	 ~~  ~~   ~  ~~    ~~~  ~~   "
								@echo ""
.PHONY: 						clean fclean