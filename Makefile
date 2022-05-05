NAME	=	RT

#compiler
CC	=	gcc
LFLAGS	=	-Wall -Wextra -O3 -g ##-Werror

#sources & object files
SRC_DIR =	./src/
OBJ_DIR =	./build/
SRC_LIST = draw_pixel.c \
		main.c \
		ales_rayc.c \
		keyevents.c \
		v_util_1.c \
		v_util_2.c \
		uni_util.c \
		min_max.c \
		ray_intersect.c \
		ray_cast_util.c \
		vector_rotation.c \
		parse_1.c \
		parse_2.c \
		parse_3.c \
		parse_4.c \
		init.c \
		raytracer.c \
		help_functions.c \
		help_functions_2.c \
		help_functions_3.c \
		get_next_line.c \
		grayscale.c \
		bmp_screencap.c \
		color_manip.c \
		projection.c \
		v_rotation.c \
		textures.c
SRCS = $(addprefix $(SRC_DIR),$(SRC_LIST))
OBJS = $(addprefix $(OBJ_DIR),$(SRC_LIST:.c=.o))

#SDL2
SDL_SRC_DIR = SDL2-2.0.20
SDL_DIR = libSDL2
SDL_BUILD_DIR_PATH = $(CURDIR)/$(SDL_DIR)
SDL_CFLAGS = `$(SDL_DIR)/bin/sdl2-config --cflags --libs`
SDL_BIN = $(SDL_DIR)/lib/libSDL2.a

.PHONY: all clean fclean re

all: $(SDL_BIN) $(NAME)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(LFLAGS) -Iinclude/ -Ilibft/includes -I$(SDL_DIR)/include/SDL2 -o $@ -c $<

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(SDL_CFLAGS) $(LFLAGS) -lm -o $(NAME)

$(SDL_BIN) :
	echo "Extracting SDL archives..."
	tar xzf SDL2-2.0.20.tar.gz
	mkdir -p $(SDL_DIR)
	cd $(SDL_SRC_DIR); ./configure --prefix=$(SDL_BUILD_DIR_PATH); make -j6; make install

clean:
	rm -rf $(OBJ_DIR)
	rm -rf DATA

fclean: clean
	rm -f $(NAME)
	rm -rf $(SDL_SRC_DIR)
re: fclean all
