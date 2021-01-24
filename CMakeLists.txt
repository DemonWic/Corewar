cmake_minimum_required(VERSION 3.15)
project(corewar C)

set(CMAKE_C_STANDARD 11)

include_directories(corewar_dir/libft, corewar_dir/includes)

add_executable(corewar corewar_dir/libft/ft_atoi.c
        corewar_dir/libft/ft_base16_decoder.c
        corewar_dir/libft/ft_base16_encoder.c
        corewar_dir/libft/ft_bzero.c
        corewar_dir/libft/ft_isalnum.c
        corewar_dir/libft/ft_isalpha.c
        corewar_dir/libft/ft_isascii.c
        corewar_dir/libft/ft_isdigit.c
        corewar_dir/libft/ft_isprint.c
        corewar_dir/libft/ft_itoa.c
        corewar_dir/libft/ft_lstadd.c
        corewar_dir/libft/ft_lstdel.c
        corewar_dir/libft/ft_lstdelone.c
        corewar_dir/libft/ft_lstiter.c
        corewar_dir/libft/ft_lstmap.c
        corewar_dir/libft/ft_lstnew.c
        corewar_dir/libft/ft_memalloc.c
        corewar_dir/libft/ft_memccpy.c
        corewar_dir/libft/ft_memchr.c
        corewar_dir/libft/ft_memcmp.c
        corewar_dir/libft/ft_memcpy.c
        corewar_dir/libft/ft_memdel.c
        corewar_dir/libft/ft_memmove.c
        corewar_dir/libft/ft_memset.c
        corewar_dir/libft/ft_pow.c
        corewar_dir/libft/ft_putchar.c
        corewar_dir/libft/ft_putchar_fd.c
        corewar_dir/libft/ft_putendl.c
        corewar_dir/libft/ft_putendl_fd.c
        corewar_dir/libft/ft_putnbr.c
        corewar_dir/libft/ft_putnbr_fd.c
        corewar_dir/libft/ft_putstr.c
        corewar_dir/libft/ft_putstr_fd.c
        corewar_dir/libft/ft_rot_n.c
        corewar_dir/libft/ft_sqrt.c
        corewar_dir/libft/ft_strcat.c
        corewar_dir/libft/ft_strchr.c
        corewar_dir/libft/ft_strclr.c
        corewar_dir/libft/ft_strcmp.c
        corewar_dir/libft/ft_strcpy.c
        corewar_dir/libft/ft_strdel.c
        corewar_dir/libft/ft_strdup.c
        corewar_dir/libft/ft_strequ.c
        corewar_dir/libft/ft_striter.c
        corewar_dir/libft/ft_striteri.c
        corewar_dir/libft/ft_strjoin.c
        corewar_dir/libft/ft_strlcat.c
        corewar_dir/libft/ft_strlen.c
        corewar_dir/libft/ft_strmap.c
        corewar_dir/libft/ft_strmapi.c
        corewar_dir/libft/ft_strncat.c
        corewar_dir/libft/ft_strncmp.c
        corewar_dir/libft/ft_strncpy.c
        corewar_dir/libft/ft_strnequ.c
        corewar_dir/libft/ft_strnew.c
        corewar_dir/libft/ft_strnstr.c
        corewar_dir/libft/ft_strrchr.c
        corewar_dir/libft/ft_strsplit.c
        corewar_dir/libft/ft_strstr.c
        corewar_dir/libft/ft_strsub.c
        corewar_dir/libft/ft_strtrim.c
        corewar_dir/libft/ft_tolower.c
        corewar_dir/libft/ft_toupper.c
        corewar_dir/libft/get_next_line.c
        corewar_dir/libft/libft.h
        corewar_dir/libft/ft_free_str.c
        corewar_dir/includes/libft.h
        corewar_dir/includes/op.h
        corewar_dir/includes/corewar.h
        corewar_dir/src/main.c
        corewar_dir/src/functions.c
        corewar_dir/src/flag_d.c
        corewar_dir/src/op.c
        corewar_dir/src/visio_put_data.c
        corewar_dir/src/visio_cells.c
        corewar_dir/src/functions2.c
        corewar_dir/src/functions3.c
        corewar_dir/src/functions4.c
        corewar_dir/src/op_addr_ld_st.c
        corewar_dir/src/op_and_or_xor.c
        corewar_dir/src/op_add_sub_zjmp_ldi_sti.c
        corewar_dir/src/op_fork_lld_lldi.c
        corewar_dir/src/op_lfork_aff_live.c
        corewar_dir/src/validation.c
        corewar_dir/src/validation2.c
        corewar_dir/src/read_champ.c
        corewar_dir/src/main_functions.c
        corewar_dir/src/main_functions2.c
        corewar_dir/src/visio.c
        corewar_dir/src/visio_update_attrs.c
        corewar_dir/src/visio_update_data.c
        corewar_dir/src/visio_put_attrs.c
        corewar_dir/src/main_functions3.c
        corewar_dir/src/main2.c
        corewar_dir/src/main3.c)

target_link_libraries(${PROJECT_NAME} ncurses)
