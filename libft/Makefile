# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/22 13:16:43 by bsprigga          #+#    #+#              #
#    Updated: 2019/03/27 12:05:10 by bsprigga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = libft.a
SRCS_MEM =			ft_memalloc.c \
					ft_memchr.c \
					ft_memcmp.c \
					ft_memdel.c \
					ft_memset.c \
					ft_bzero.c \
					ft_memcpy.c \
					ft_memccpy.c \
					ft_memmove.c

SRCS_STR =			ft_strcat.c \
					ft_strchr.c \
					ft_strchr_wo_zero.c \
					ft_strclr.c \
					ft_strcpy.c \
					ft_strdel.c \
					ft_strdup.c \
					ft_strlen.c \
					ft_striter.c \
					ft_striteri.c \
					ft_strmap.c \
					ft_strncpy.c \
					ft_strnew.c \
					ft_strrchr.c \
					ft_strncmp.c \
					ft_strcmp.c \
					ft_strstr.c \
					ft_strstr_to_find_zero.c \
					ft_strnstr.c \
					ft_strncat.c \
					ft_strlcat.c \
					ft_strmapi.c \
					ft_strequ.c \
					ft_strnequ.c \
					ft_strsub.c \
					ft_strsplit.c \
					ft_strjoin.c \
					ft_strtrim.c \
					ft_isin.c \
					ft_str_append_char.c \
					ft_str_append_str.c \
					ft_strlcpy.c

SRCS_OTHER = 		ft_abs.c \
					ft_atoi.c \
					ft_atoi_long.c \
					ft_itoa.c \
					ft_itoa_long.c \
					ft_itoa_base.c \
					ft_isalpha.c \
					ft_isdigit.c \
					ft_isalnum.c \
					ft_isnumeric.c \
					ft_isascii.c \
					ft_isprint.c \
					ft_toupper.c \
					ft_tolower.c \
					ft_putchar.c \
					ft_putstr.c \
					ft_putendl.c \
					ft_putnbr.c \
					ft_putchar_fd.c \
					ft_putstr_fd.c \
					ft_putendl_fd.c \
					ft_putnbr_fd.c \
					ft_natural_pow.c \
					ft_sqrt.c \
					ft_sqrt_rational.c \
					ft_range.c \
					get_next_line.c \
					ft_isinf.c \
					ft_isnan.c \
					ft_swap.c \
					ft_log2.c \
					ft_arrlen.c 

SRCS_LST =			ft_lstnew.c \
					ft_lstdelone.c \
					ft_lstdel.c \
					ft_lstadd.c \
					ft_lstiter.c \
					ft_lstmap.c \
					ft_lstreverse.c

SRCS_FT_PRINTF =	ft_printf.c \
					make_formatted_strings.c \
					make_aefg_string_part_1.c \
					make_aefg_string_part_2.c \
					make_boux_string_part_1.c \
					make_boux_string_part_2.c \
					make_boux_string_part_3.c \
					make_c_string_part_1.c \
					make_c_string_part_2.c \
					make_di_string_part_1.c \
					make_di_string_part_2.c \
					make_p_string_part_1.c \
					make_p_string_part_2.c \
					make_s_string_part_1.c \
					make_s_string_part_2.c \
					parse_format_part_1.c \
					parse_format_part_2.c \
					parse_format_part_3.c \
					parse_format_part_4.c \
					support_part_1.c \
					support_part_2.c \
					support_part_3.c

INCLUDES := includes
CC = clang

#CFLAGS = -Wall -Wextra -Werror -g

FLAGS = -Wall -Wextra -Werror -g

VPATH = SRCS_MEM SRCS_LST SRCS_STR SRCS_OTHER SRCS_FT_PRINTF

OBJECTS = $(SRCS_MEM:.c=.o) $(SRCS_STR:.c=.o) $(SRCS_LST:.c=.o) $(SRCS_OTHER:.c=.o) $(SRCS_FT_PRINTF:.c=.o)

all: $(NAME)

# если в зависимость попадают .о файлы и при отсутствии строки компиляции, а также при отсутствии .с файлов,
# то выполняется неявное правило вида `$(CC) -c $(CPPFLAGS) $(CFLAGS)'
# $(CC) и $(CFLAGS) необходимо переопределить вручную (опционально)

$(NAME) : $(OBJECTS)
	ar rc $(NAME) $(OBJECTS)
	ranlib $(NAME)

$(OBJECTS): %.o: %.c
	gcc -c $(FLAGS) $< -o $@ -Iincludes
# $@ Имя цели обрабатываемого правила
# $< Имя первой зависимости обрабатываемого правила
# $^ Список всех зависимостей обрабатываемого правила

test:
	@echo $(OBJECTS)

clean:
	/bin/rm -f $(OBJECTS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
