NAME	=	RT

#compiler
CC	=	gcc
LFLAGS	=	-Wall -Wextra -O3 -g -Werror

#sources & object files
SRC_DIR =	./src/
OBJ_DIR =	./build/
SRC_LIST = draw_pixel.c \
		main.c \
		keyevents.c \
		v_util_1.c \
		v_util_2.c \
		ray_intersect.c \
		ray_cast_util.c \
		vector_rotation.c \
		raytracer.c \
		filters.c \
		bmp_screencap.c \
		color_manip.c \
		color_manip2.c \
		textures.c \
		textures2.c \
		parser_main.c \
		parser_utils.c \
		parser_shapes.c \
		parser_rotations.c \
		parser_matops.c \
		ray_cast_util2.c \
		parser_utils2.c
SRCS = $(addprefix $(SRC_DIR),$(SRC_LIST))
OBJS = $(addprefix $(OBJ_DIR),$(SRC_LIST:.c=.o))

INCS = -Iinclude/ -Ilibft/includes -I$(SDL_DIR)/include/SDL2
#libft
LIBFT = libft/libft.a
LFT_LINK = -L./libft -lft

#SDL2
SDL_SRC_DIR = SDL2-2.0.20
SDL_DIR = libSDL2
SDL_BUILD_DIR_PATH = $(CURDIR)/$(SDL_DIR)
SDL_CFLAGS = `$(SDL_DIR)/bin/sdl2-config --cflags --libs`
SDL = $(SDL_DIR)/lib/libSDL2.a

.PHONY: all clean fclean re

all: $(LIBFT) $(SDL) $(NAME)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(LFLAGS) $(INCS) -o $@ -c $<

$(LIBFT):
	make -C libft

$(SDL):
	echo "Extracting SDL archives..."
	tar xzf SDL2-2.0.20.tar.gz
	mkdir -p $(SDL_DIR)
	cd $(SDL_SRC_DIR); ./configure --prefix=$(SDL_BUILD_DIR_PATH); make -j6; make install

$(NAME): $(OBJS)
	$(CC) $(INCS) $(LFT_LINK) -lm  $(SDL_CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)
	rm -rf DATA
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	rm -rf $(SDL_SRC_DIR)
	make fclean -C libft

re: fclean all
