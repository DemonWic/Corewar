cmake_minimum_required(VERSION 3.15)
project(corewar C)

set(CMAKE_C_STANDARD 11)

include_directories(libft, includes)

add_executable(corewar libft/libft_corewar/ft_atoi.c
        libft/libft_corewar/ft_base16_decoder.c
        libft/libft_corewar/ft_base16_encoder.c
        libft/libft_corewar/ft_bzero.c
        libft/libft_corewar/ft_isalnum.c
        libft/libft_corewar/ft_isalpha.c
        libft/libft_corewar/ft_isascii.c
        libft/libft_corewar/ft_isdigit.c
        libft/libft_corewar/ft_isprint.c
        libft/libft_corewar/ft_itoa.c
        libft/libft_corewar/ft_lstadd.c
        libft/libft_corewar/ft_lstdel.c
        libft/libft_corewar/ft_lstdelone.c
        libft/libft_corewar/ft_lstiter.c
        libft/libft_corewar/ft_lstmap.c
        libft/libft_corewar/ft_lstnew.c
        libft/libft_corewar/ft_memalloc.c
        libft/libft_corewar/ft_memccpy.c
        libft/libft_corewar/ft_memchr.c
        libft/libft_corewar/ft_memcmp.c
        libft/libft_corewar/ft_memcpy.c
        libft/libft_corewar/ft_memdel.c
        libft/libft_corewar/ft_memmove.c
        libft/libft_corewar/ft_memset.c
        libft/libft_corewar/ft_pow.c
        libft/libft_corewar/ft_putchar.c
        libft/libft_corewar/ft_putchar_fd.c
        libft/libft_corewar/ft_putendl.c
        libft/libft_corewar/ft_putendl_fd.c
        libft/libft_corewar/ft_putnbr.c
        libft/libft_corewar/ft_putnbr_fd.c
        libft/libft_corewar/ft_putstr.c
        libft/libft_corewar/ft_putstr_fd.c
        libft/libft_corewar/ft_rot_n.c
        libft/libft_corewar/ft_sqrt.c
        libft/libft_corewar/ft_strcat.c
        libft/libft_corewar/ft_strchr.c
        libft/libft_corewar/ft_strclr.c
        libft/libft_corewar/ft_strcmp.c
        libft/libft_corewar/ft_strcpy.c
        libft/libft_corewar/ft_strdel.c
        libft/libft_corewar/ft_strdup.c
        libft/libft_corewar/ft_strequ.c
        libft/libft_corewar/ft_striter.c
        libft/libft_corewar/ft_striteri.c
        libft/libft_corewar/ft_strjoin.c
        libft/libft_corewar/ft_strlcat.c
        libft/libft_corewar/ft_strlen.c
        libft/libft_corewar/ft_strmap.c
        libft/libft_corewar/ft_strmapi.c
        libft/libft_corewar/ft_strncat.c
        libft/libft_corewar/ft_strncmp.c
        libft/libft_corewar/ft_strncpy.c
        libft/libft_corewar/ft_strnequ.c
        libft/libft_corewar/ft_strnew.c
        libft/libft_corewar/ft_strnstr.c
        libft/libft_corewar/ft_strrchr.c
        libft/libft_corewar/ft_strsplit.c
        libft/libft_corewar/ft_strstr.c
        libft/libft_corewar/ft_strsub.c
        libft/libft_corewar/ft_strtrim.c
        libft/libft_corewar/ft_tolower.c
        libft/libft_corewar/ft_toupper.c
        libft/libft_corewar/get_next_line.c
        libft/libft_corewar/libft.h
        libft/libft_corewar/ft_free_str.c
        includes/inc_corewar/lemin.h
        includes/inc_corewar/libft.h
        includes/inc_corewar/op.h
        includes/inc_corewar/corewar.h
        src/corewar/main.c
        src/corewar/functions.c
        src/corewar/flag_d.c
        src/corewar/op.c
        src/corewar/visio_put_data.c
        src/corewar/visio_cells.c
        src/corewar/functions2.c
        src/corewar/functions3.c
        src/corewar/functions4.c
        src/corewar/op_addr_ld_st.c
        src/corewar/op_and_or_xor.c
        src/corewar/op_add_sub_zjmp_ldi_sti.c
        src/corewar/op_fork_lld_lldi.c
        src/corewar/op_lfork_aff_live.c
        src/corewar/validation.c
        src/corewar/validation2.c
        src/corewar/read_champ.c
        src/corewar/main_functions.c
        src/corewar/main_functions2.c
        src/corewar/visio.c
        src/corewar/visio_update_attrs.c
        src/corewar/visio_update_data.c
        src/corewar/visio_put_attrs.c
        src/corewar/main_functions3.c
        src/corewar/main2.c
        src/corewar/main3.c)

target_link_libraries(${PROJECT_NAME} ncurses)
