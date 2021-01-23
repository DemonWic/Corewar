/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Makefile                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahintz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 15:25:50 by ahintz            #+#    #+#             */
/*   Updated: 2021/01/23 15:25:52 by ahintz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



ASM_NAME = asm
COREWAR_NAME = corewar

CC = gcc
FLAGS = -Wall -Werror -Wextra -O3


ASM_LIBRARIES =
ASM_INCLUDES = \
	-I$(HEADERS_DIRECTORY)\
	-I$(LIBFT_HEADERS_COREWAR)\

COREWAR_LIBRARIES = -lncurses
COREWAR_INCLUDES = \
	-I$(HEADERS_DIRECTORY)\
	-I$(LIBFT_HEADERS_ASM)\



LIBFT_COREWAR = $(LIBFT_DIRECTORY_COREWAR)libft.a
LIBFT_DIRECTORY_COREWAR = ./libft/corewar/
LIBFT_HEADERS_COREWAR = $(LIBFT_DIRECTORY_COREWAR)includes/


# Headers

HEADERS_DIRECTORY = ./includes/

# asm

ASM_HEADERS_LIST = \
	op.h\
	asm.h\
	asm_error.h\
	asm_asm.h\
	asm_disasm.h
ASM_HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(ASM_HEADERS_LIST))

# corewar

COREWAR_HEADERS_LIST = \
	op.h\
	corewar.h\
	corewar_error.h\
	corewar_vs.h
COREWAR_HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(COREWAR_HEADERS_LIST))