# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/11 10:42:46 by eniini            #+#    #+#              #
#    Updated: 2022/05/28 14:24:07 by eniini           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a
PRINTF	=	libftprintf.a
GFX		=	libgfx.a

# compiler
CC	=	gcc
CFLAGS	=	-Wall -Wextra -Werror -O3

# header directory
INCDIR	=	includes

# source directories
SRCDIRS	=	array_utils: \
		char_utils: \
		file_io: \
		llist_utils: \
		math: \
		mem_utils: \
		process_control: \
		string_utils: \
		type_conversion: \
		wchar_utils
PFTDIR	=	ft_printf:
GFXDIR	=	gfx:
# vpath
VPATH	+=	$(addprefix srcs/,$(SRCDIRS))
VPATH	+=	$(addprefix srcs/,$(PFTDIR))
VPATH	+=	$(addprefix srcs/,$(GFXDIR))
# source files
SRCS	=	ft_free_arr.c \
		ft_get_arr_size.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_islower.c \
		ft_isprint.c \
		ft_isspace.c \
		ft_isupper.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_putchar_fd.c \
		ft_putchar.c \
		ft_putendl_fd.c \
		ft_putendl.c \
		ft_putnbr_fd.c \
		ft_putnbr.c \
		ft_putstr_fd.c \
		ft_putstr.c \
		get_next_line.c \
		ft_elemdel.c \
		ft_lstadd.c \
		ft_lstaddl.c \
		ft_lstdel.c \
		ft_lstdelone.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_lstnew.c \
		ft_abs.c \
		ft_clamp_d.c \
		ft_clamp_i.c \
		ft_pow.c \
		ft_bzero.c \
		ft_memalloc.c \
		ft_memccpy.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memdel.c \
		ft_memmove.c \
		ft_memset.c \
		ft_swap.c \
		ft_getout.c \
		ft_strcat.c \
		ft_strchr.c \
		ft_strclr.c \
		ft_strcmp.c \
		ft_strcpy.c \
		ft_strdel.c \
		ft_strdup.c \
		ft_strequ.c \
		ft_striter.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlen.c \
		ft_strmap.c \
		ft_strmapi.c \
		ft_strncat.c \
		ft_strncmp.c \
		ft_strncpy.c \
		ft_strndup.c \
		ft_strnequ.c \
		ft_strnew.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strsplit.c \
		ft_strstr.c \
		ft_strsub.c \
		ft_strtrim.c \
		ft_wordcount.c \
		ft_atof.c \
		ft_atoi.c \
		ft_atoi_sizet.c \
		ft_ftoa.c \
		ft_itoa.c \
		ft_itoa_base.c \
		ft_uitoa.c \
		ft_uitoa_base.c \
		ft_putwchar.c \
		ft_putwstr.c \
		ft_wcharlen.c \
		ft_wstrlen.c \
		ft_wstrnlen.c
PFTSRCS	=	ft_printf.c \
		ftprintf_c.c \
		ftprintf_convert.c \
		ftprintf_float.c \
		ftprintf_integer.c \
		ftprintf_read_args.c \
		ftprintf_sign.c \
		ftprintf_str.c \
		ftprintf_typecheck.c
GFXSRCS	=	ft_argb_grayscale.c \
		ft_argb_lerp.c \
		ft_color_lerp.c \
		ft_d_lerp.c \
		ft_i_lerp.c \
		ft_inverse_d_lerp.c \
		ft_inverse_i_lerp.c \
		ft_create_bmp.c \
		ft_load_bmp.c \
		ft_hueshift.c \
		ft_init_gfxinfo.c \
		ft_smoothstep.c

#object directory
OBJDIR	=	objs
PFTOBJDIR =	pftobjs
GFXOJBDIR =	gfxobjs
#object files
OBJS	=	$(patsubst %,$(OBJDIR)/%,$(SRCS:.c=.o))
PFTOBJS	=	$(patsubst %,$(PFTOBJDIR)/%,$(PFTSRCS:.c=.o))
GFXOBJS	=	$(patsubst %,$(GFXOJBDIR)/%,$(GFXSRCS:.c=.o))

#colors
CYAN	=	\033[0;36m
PURPLE	=	\033[1;35m
NC	=	\033[0m
#clear line, move backwards x columns
RESET	=	\033[1K\033[100D

.PHONY: all clean fclean re

#compiles all libraries together
all: $(NAME) $(PRINTF) $(GFX)
	@ar -rc $(NAME) $(PFTOBJS) $(GFXOBJS)
	@printf "$(CYAN)$(RESET)[libft] finished!$(NC)\n"

#link obj files
$(OBJDIR)/%.o:%.c
	@mkdir -p $(OBJDIR)
	@printf "$(CYAN)."
	@$(CC) $(CFLAGS) -o $@ -c $< -I$(INCDIR)

$(PFTOBJDIR)/%.o:%.c
	@mkdir -p $(PFTOBJDIR)
	@printf "$(PURPLE)."
	@$(CC) $(CFLAGS) -o $@ -c $< -I$(INCDIR)

$(GFXOJBDIR)/%.o:%.c
	@mkdir -p $(GFXOJBDIR)
	@printf "$(PURPLE)."
	@$(CC) -lm $(CFLAGS) -o $@ -c $< -I$(INCDIR)

#compile each library separately
$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@printf "$(CYAN)$(RESET)[libft] library built!$(NC)\n"

$(PRINTF): $(PFTOBJS)
	@ar rcs $(PRINTF) $(PFTOBJS)
	@printf "$(PURPLE)$(RESET)[ftprintf] library built!$(NC)\n"

$(GFX) : $(GFXOBJS)
	@ar rcs $(GFX) $(GFXOBJS)
	@printf "$(PURPLE)$(RESET)[gfx] library built!$(NC)\n"

clean:
	@rm -rf $(OBJDIR)
	@rm -rf $(PFTOBJDIR)
	@rm -rf $(GFXOJBDIR)
	@printf "$(CYAN)[libft] object files removed$(NC)\n"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(PRINTF)
	@rm -f $(GFX)
	@printf "$(CYAN)[libft] static libraries removed$(NC)\n"

re: fclean all
