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

ASM := asm
CW := corewar
ASM_DIR := asm_dir
CW_DIR := corewar_dir
CC = gcc

all: $(ASM) $(CW)

$(ASM):
	@make -C $(ASM_DIR)
	@mv $(ASM_DIR)/$(ASM) .

$(CW):
	@make -C $(CW_DIR)
	@mv $(CW_DIR)/$(CW) .

clean:
	@make -C $(ASM_DIR) clean
	@make -C $(CW_DIR) clean

fclean:
	@make -C $(ASM_DIR) fclean
	@make -C $(CW_DIR) fclean
	@rm -f $(ASM)
	@rm -f $(CW)

re: fclean all

.PHONY: all clean fclean re
