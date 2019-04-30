# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/01 17:36:37 by bsprigga          #+#    #+#              #
#    Updated: 2019/04/29 16:20:53 by tsimonis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re rebuild_lib re1 fclean1

NAME_ASM = asm
NAME_VM = corewar

INCLUDES := ./includes \
			./libft/includes

DIR_ASM := assembler
DIR_VM := virtual_machine

CC = clang
FLAGS := -Wall -Werror -Wextra -g
VPATH := . srcs

SRCS_ASM =	main.c \
			read_champion_part_1.c \
			read_champion_part_2.c \
			read_champion_part_3.c \
			read_champion_part_4.c \
			read_champion_part_5.c \
			read_champion_part_6.c \
			read_champion_part_7.c \
			read_champion_part_8.c \
			read_champion_part_9.c \
			read_champion_part_10.c \
			read_champion_part_11.c \
			read_champion_part_12.c \
			read_champion_part_13.c \
			read_champion_part_14.c \
			read_champion_part_15.c \
			op.c \
			support_part_1.c \
			support_part_2.c \
			support_part_3.c \
			support_part_4.c

SRCS_VM =	virtual_machine_part_1.c \
			virtual_machine_part_2.c \
			virtual_machine_part_3.c \
			virtual_machine_part_4.c \
			virtual_machine_part_5.c \
			virtual_machine_part_6.c \
			virtual_machine_part_7.c \
			read_champion_part_14.c \
			read_champion_part_15.c \
			op.c \
			support_part_1.c \
			support_part_2.c \
			support_part_4.c

OBJECTS_ASM = $(SRCS_ASM:%.c=$(DIR_ASM)/%.o)
OBJECTS_VM = $(SRCS_VM:%.c=$(DIR_VM)/%.o)

all: $(NAME_ASM) $(NAME_VM)

$(NAME_ASM): libft/libft.a $(OBJECTS_ASM)
	$(CC) $(FLAGS) $(OBJECTS_ASM) $(addprefix -I,$(INCLUDES)) -L./libft -lft -o $@

$(NAME_VM): libft/libft.a $(OBJECTS_VM)
	$(CC) $(FLAGS) -lcurses $(OBJECTS_VM) $(addprefix -I,$(INCLUDES)) -L./libft -lft -o $@

libft/libft.a:
	$(MAKE) -C libft

# $(OBJECTS_ASM): %.o: %.c
$(DIR_ASM)/%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@ $(addprefix -I,$(INCLUDES))

# $(OBJECTS_VM): %.o: %.c
$(DIR_VM)/%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@ $(addprefix -I,$(INCLUDES))

clean:
	rm -f $(OBJECTS_ASM) $(OBJECTS_VM)

fclean: clean
	rm -f $(NAME_ASM) $(NAME_VM)

re: fclean all

rebuild_lib:
	$(MAKE) re -C libft

re1: rebuild_lib fclean all

clean1: clean
	$(MAKE) clean -C libft

fclean1: fclean
	$(MAKE) fclean -C libft
