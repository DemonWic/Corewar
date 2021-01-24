# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bsausage <bsausage@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/22 03:38:06 by loram             #+#    #+#              #
#    Updated: 2021/01/19 12:44:40 by bsausage         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COREWAR = corewar

SRC_DIR = src/
LFT_DIR = libft/
OBJ_DIR = obj/
HEADERS = includes/

SRC =	flag_d.c\
        functions.c\
        functions2.c\
        functions3.c\
        functions4.c\
        main2.c\
        main3.c\
        main_functions.c\
        main_functions2.c\
        main_functions3.c\
        op.c\
        op_add_sub_zjmp_ldi_sti.c\
        op_addr_ld_st.c\
        op_and_or_xor.c\
        op_fork_lld_lldi.c\
        op_lfork_aff_live.c\
        read_champ.c\
        validation.c\
        validation2.c\
        visio.c\
        visio_cells.c\
        visio_put_attrs.c\
        visio_put_data.c\
        visio_update_attrs.c\
        visio_update_data.c

CSRC = main.c
SRC_DIRS = $(SRC_DIR)

OBJ = $(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(SRC)))
OBJS = $(OBJ)
OBJ_CSRC = $(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(CSRC)))

INCLUDES = -I $(HEADERS) -I $(LFT_DIR)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -O3
LIBS = -L$(LFT_DIR)
LFT = $(addprefix $(LFT_DIR), libft.a)

.PHONY: all clean fclean re

all: $(COREWAR)

$(COREWAR): $(LFT) $(OBJ_DIR) $(OBJS) $(OBJ_CSRC)
	@echo "\033[32mmaking COREWAR...\033[0m"
	@$(CC) $(CFLAGS) $(LIBS) $(OBJS) $(OBJ_CSRC) $(INCLUDES) $(LFT) -o $(COREWAR) -lncurses
	@echo "\033[32mCreate COREWAR\033[0m"

$(OBJ_DIR):
	@echo "\033[32mCreate OBJ dir\033[0m"
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)%.o: $(UTIL_DIR)%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LFT):
	@echo "\033[32mcreatiing LIB...\033[0m"
	@make -C $(LFT_DIR)

clean:
	@make -C $(LFT_DIR) clean
	@echo "\033[33mcleaning repository...\033[0m"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make -C $(LFT_DIR) fclean
	@echo "\033[33mremoving executable...\033[0m"
	@rm -f $(COREWAR)

re: fclean all
