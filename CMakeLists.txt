cmake_minimum_required(VERSION 3.15)
project(corewar C)

set(CMAKE_C_STANDARD 11)

include_directories(libft, includes)

add_executable(corewar corewar/libft/ft_atoi.c
        corewar/libft/ft_base16_decoder.c
        corewar/libft/ft_base16_encoder.c
        corewar/libft/ft_bzero.c
        corewar/libft/ft_isalnum.c
        corewar/libft/ft_isalpha.c
        corewar/libft/ft_isascii.c
        corewar/libft/ft_isdigit.c
        corewar/libft/ft_isprint.c
        corewar/libft/ft_itoa.c
        corewar/libft/ft_lstadd.c
        corewar/libft/ft_lstdel.c
        corewar/libft/ft_lstdelone.c
        corewar/libft/ft_lstiter.c
        corewar/libft/ft_lstmap.c
        corewar/libft/ft_lstnew.c
        corewar/libft/ft_memalloc.c
        corewar/libft/ft_memccpy.c
        corewar/libft/ft_memchr.c
        corewar/libft/ft_memcmp.c
        corewar/libft/ft_memcpy.c
        corewar/libft/ft_memdel.c
        corewar/libft/ft_memmove.c
        corewar/libft/ft_memset.c
        corewar/libft/ft_pow.c
        corewar/libft/ft_putchar.c
        corewar/libft/ft_putchar_fd.c
        corewar/libft/ft_putendl.c
        corewar/libft/ft_putendl_fd.c
        corewar/libft/ft_putnbr.c
        corewar/libft/ft_putnbr_fd.c
        corewar/libft/ft_putstr.c
        corewar/libft/ft_putstr_fd.c
        corewar/libft/ft_rot_n.c
        corewar/libft/ft_sqrt.c
        corewar/libft/ft_strcat.c
        corewar/libft/ft_strchr.c
        corewar/libft/ft_strclr.c
        corewar/libft/ft_strcmp.c
        corewar/libft/ft_strcpy.c
        corewar/libft/ft_strdel.c
        corewar/libft/ft_strdup.c
        corewar/libft/ft_strequ.c
        corewar/libft/ft_striter.c
        corewar/libft/ft_striteri.c
        corewar/libft/ft_strjoin.c
        corewar/libft/ft_strlcat.c
        corewar/libft/ft_strlen.c
        corewar/libft/ft_strmap.c
        corewar/libft/ft_strmapi.c
        corewar/libft/ft_strncat.c
        corewar/libft/ft_strncmp.c
        corewar/libft/ft_strncpy.c
        corewar/libft/ft_strnequ.c
        corewar/libft/ft_strnew.c
        corewar/libft/ft_strnstr.c
        corewar/libft/ft_strrchr.c
        corewar/libft/ft_strsplit.c
        corewar/libft/ft_strstr.c
        corewar/libft/ft_strsub.c
        corewar/libft/ft_strtrim.c
        corewar/libft/ft_tolower.c
        corewar/libft/ft_toupper.c
        corewar/libft/get_next_line.c
        corewar/libft/libft.h
        corewar/libft/ft_free_str.c
        corewar/includes/libft.h
        corewar/includes/op.h
        corewar/includes/corewar.h
        corewar/src/main.c
        corewar/src/functions.c
        corewar/src/flag_d.c
        corewar/src/op.c
        corewar/src/visio_put_data.c
        corewar/src/visio_cells.c
        corewar/src/functions2.c
        corewar/src/functions3.c
        corewar/src/functions4.c
        corewar/src/op_addr_ld_st.c
        corewar/src/op_and_or_xor.c
        corewar/src/op_add_sub_zjmp_ldi_sti.c
        corewar/src/op_fork_lld_lldi.c
        corewar/src/op_lfork_aff_live.c
        corewar/src/validation.c
        corewar/src/validation2.c
        corewar/src/read_champ.c
        corewar/src/main_functions.c
        corewar/src/main_functions2.c
        corewar/src/visio.c
        corewar/src/visio_update_attrs.c
        corewar/src/visio_update_data.c
        corewar/src/visio_put_attrs.c
        corewar/src/main_functions3.c
        corewar/src/main2.c
        corewar/src/main3.c)

target_link_libraries(${PROJECT_NAME} ncurses)
