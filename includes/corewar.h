//
// Created by Виктор Рыжков on 08.12.2020.
//

#ifndef COREWAR_COREWAR_H
#define COREWAR_COREWAR_H

#include "libft.h"
#include "op.h"


typedef struct s_cursor
{
    int         num; // уникальный номер каретки
    int         carry; // carry или true или false 1/0 изначально 0
    int         op_code; // код операции на которой стоит каретка
    int         cycle_num_live; // номер цикла в котором была выполнена последняя операция live данной кареткой
    int         cycle_to_op; // кол-во циклов до исполнения операции
    int         position; // позиция на арене от 0 до 4095
    int         byte_to_next_op; // кол-во байт до следующей операции
    int         regs[REG_NUMBER + 1]; // регистры
    struct s_cursor  *next;
}              t_cursor;


typedef struct		s_champ
{
    int             num;
    char            *file;
    char			name[PROG_NAME_LENGTH];
    char			comment[COMMENT_LENGTH];
    int				size;
    unsigned char   *code;
}					t_champ;

typedef struct s_bit
{
    unsigned int    help : 1;
    unsigned int    too_many_files : 1;
    unsigned int    not_valid_file : 1;
    unsigned int    invalid_head : 1;
    unsigned int    no_such_file : 1;
    unsigned int    large_code: 1;
}              t_bit;

typedef struct      s_init
{
    int             num;
    int             flag_n; // 0 или число
    int             flag_dump; // 0 или число
    int             dump_num;
    int             pl_count;
//    int             error;  // флаги нужно запилить
    int             nums[MAX_PLAYERS + 1];
    int             invalid;
    t_bit           error;
    t_champ         **champs;
    unsigned char   arena[MEM_SIZE];
    t_cursor        *cursors;

}                   t_init;


typedef struct s_op
{
    char *name;
    int  arg_num;
    int  arg_types[3];
    int  code;
    int  cycles_to_do;
    char *des;
    int code_arg;  // true / false есть ли тип аргументов или нет
    int dir_size; // if 0 - 4 byte if 1 - 2 byte
    int dir;
}               t_op;

t_op    op_tab[17] =
        {
                {0, 0, {0}, 0, 0, 0, 0, 0, 4},
                {"live", 1, {T_DIR}, 1, 10, "alive", 0, 0, 4},
                {"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0, 4},
                {"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0, 4},
                {"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0, 4},
                {"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0, 4},
                {"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
                        "et (and  r1, r2, r3   r1&r2 -> r3", 1, 0, 4},
                {"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
                        "ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0, 4},
                {"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
                        "ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0, 4},
                {"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1, 2},
                {"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
                        "load index", 1, 1, 2},
                {"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
                        "store index", 1, 1, 2},
                {"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1, 2},
                {"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0, 4},
                {"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
                        "long load index", 1, 1, 2},
                {"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1, 2},
                {"aff", 1, {T_REG}, 16, 2, "aff", 1, 0, 4}
        };



int				ft_isnumber(char *str);
int ft_valname(char *file);
t_init  *init_data(void);
void    pre_valid(int argc, char **argv, t_init *data);
int min_in_arr(t_init *data);
int	code_to_int(unsigned char *code, size_t size);
void error_large_file(t_init *data, int num);
void error_read_file(void);
void print_help(void);
void error_many_champ(void);
void error_invalid_head(t_init *data, int num);
int check_errors(t_init *data, int num);
void	*ft_unmemcpy(void *dst, const void *src, size_t n);
void	print_buf(unsigned char *buf);
int    get_byte_to_do(t_cursor *cursor, unsigned char *arena);
int *get_types_arg(t_cursor *cursor, unsigned char *arena);

#endif //COREWAR_COREWAR_H



//typedef struct s_cell
//{
//    unsigned char c;
//    int player;
//    int car;
//}              t_cell;