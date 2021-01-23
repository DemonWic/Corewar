/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <bsausage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 02:53:14 by loram             #+#    #+#             */
/*   Updated: 2021/01/19 17:38:13 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_ASM_H
# define ASM_ASM_H

# include "libft.h"
# include "op.h"

typedef struct			s_op
{
	char				*name;
	int					arg_num;
	int					arg_types[3];
	int					code;
	int					cycles_to_do;
	char				*des;
	int					code_arg;
	int					dir_size;
	int					dir;
}						t_op;

typedef struct			s_commands
{
	char				*line;
	int					num_line;
	int					size;
	int					args[3];
	int					arg_types[3];
	int					label_arg[3];
	t_op				op;
	struct s_commands	*next;
}						t_commands;

typedef struct			s_labels
{
	char				*label_name;
	int					num_line;
	struct s_labels		*next;
}						t_labels;

typedef struct			s_champ
{
	int					num;
	char				name[PROG_NAME_LENGTH + 1];
	char				comment[COMMENT_LENGTH + 1];
	int					size;
	int					num_line;
	t_commands			*commands;
	t_commands			*current_command;
	t_labels			*labels;
	unsigned char		*code;
}						t_champ;

typedef struct			s_data
{
	char				*input;
	char				*name_file;
	int					data_size;
	int					lines;
	int					is_name;
	int					is_comment;
	int					eol_flag;
	int					eof_flag;
}						t_data;

static t_op	g_op_tab[17] =
{
	{0, 0, {0}, 0, 0, 0, 0, 0, 4},
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0, 4},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0, 4},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0, 4},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0, 4},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0, 4},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,\
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0, 4},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,\
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0, 4},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,\
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0, 4},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1, 2},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,\
		"load index", 1, 1, 2},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,\
		"store index", 1, 1, 2},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1, 2},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0, 4},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,\
		"long load index", 1, 1, 2},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1, 2},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0, 4}
};

t_data					*init_asm_data(void);
void					*print_error_init(char *err_str, t_data *data);
void					clean_data(t_data *data);
void					clean_champ(t_champ *champ);
t_data					*get_asm_data(char *file);
int						parse_asm(char *file);
char					*parse_header(t_champ *champ, t_data *data);
t_champ					*init_champ(void);
char					*check_add_name(char *start, t_champ *champ,\
										t_data *data, int i);
char					*check_add_comment(char *start, t_champ *champ,\
											t_data *data, int i);
uint16_t				swapendian_2_bytes(uint16_t num);
uint32_t				swapendian_4_bytes(uint32_t num);
uint64_t				swapendian_8_bytes(uint64_t num);
char					*all_coding_to_vm(t_champ *champ, t_data *data);
void					code_num_size_fd(u_int64_t num, int fd,\
										size_t size);
void					code_args(t_commands *command, int fd);
void					code_arg_types(t_commands *command, int fd);
int						parse_code_part(char *ptr, t_champ *champ);
long					ft_strtol(const char *str, char **end);
t_commands				*push_command_back(t_commands **head, t_op op);
void					free_commands_list(t_commands **head);
t_labels				*push_label_back(t_labels **head, char *label_name, \
										int num_line);
void					free_labels_list(t_labels **head);
int						get_op(char **ptr, t_champ *champ);
int						get_type(char **ptr, t_commands *command, int i);
int						get_args(t_commands *command, t_champ *champ);
int						get_label_arg(char **ptr, t_commands *command, \
										t_labels *label, int i);
void					convert_label_to_number(t_commands *command, \
										t_champ *champ);
int						label_check(char **ptr, t_champ *champ);
int						print_error(char *ptr, int line);
int						skip_new_line(char **ptr, t_champ *champ);
void					skip_args(char **ptr, t_champ *champ);
void					skip_spaces(char **ptr);
int						check_separator(char **ptr, t_commands *command, int i);

#endif
