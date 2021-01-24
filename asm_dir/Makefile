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

ASM = asm

SRC_DIR = src/
UTIL_DIR = utils/
LFT_DIR = libft/
OBJ_DIR = obj/
HEADERS = includes/

UTIL =  asm_data_utils.c\
		 get_asm_data.c\
		 asm_champ_utils.c\
		 check_header_name.c\
		 check_header_comment.c\
		 swap_endian.c\
		 arg_type.c\
		 commands_list_functions.c\
		 get_command.c\
		 get_arg.c\
		 get_label_arg.c\
		 label_to_number.c\
		 labels_list_functions.c\
		 labels.c\
		 separator.c\
		 skip_data.c
SRC =	all_coding_to_vm.c\
		 code_args_and_types.c\
		 asm_parse_code.c\
		 parse_asm.c\
		 asm_parse_header.c

ASRC = asm.c
SRC_DIRS = $(UTIL_DIR) $(SRC_DIR)

OBJ = $(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(SRC)))
OBJ_UTIL = $(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(UTIL)))
OBJS = $(OBJ) $(OBJ_UTIL) $(OBJ_BNS)
OBJ_ASRC = $(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(ASRC)))

INCLUDES = -I $(HEADERS) -I $(LFT_DIR)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -O3
LIBS = -L$(LFT_DIR)
LFT = $(addprefix $(LFT_DIR), libft.a)

.PHONY: all clean fclean re

all: $(ASM)

$(ASM): $(LFT) $(OBJ_DIR) $(OBJS) $(OBJ_ASRC)
	@echo "\033[32mmaking ASM...\033[0m"
	@$(CC) $(CFLAGS) $(LIBS) $(OBJS) $(OBJ_ASRC) $(INCLUDES) $(LFT) -o $(ASM)
	@echo "\033[32mCreate ASM\033[0m"

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
	@rm -f $(ASM)

re: fclean all
