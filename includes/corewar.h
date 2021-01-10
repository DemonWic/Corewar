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
    int         pc; // позиция каретки (обязательно на коде операции)
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
    int             flag_aff; // 0 или 1
    int             dump_num;

    int             pl_count; // число игроков
    int             live_player;  // игрок о котором последнем сказали что он жив
    long int        cycle;   // количество циклов всего
    int             cycle_after_check; // количество циклов после проверки
    int             live_count; // количество выполненных операций `live` за последний период, длинной в `cycles_to_die`
    int             cycles_to_die; // длительность периода до проверки
    int             check_count; // число проверок

    int             nums[MAX_PLAYERS + 1];
    int             invalid;
    t_bit           error;

    t_champ         **champs;

    unsigned char   arena[MEM_SIZE];

    t_cursor        *cursors;
    int             cursors_count;

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
    int (*func) (t_cursor *, t_init *);
}               t_op;

int op_live(t_cursor *cursor, t_init *data);
int op_aff(t_cursor *cursor, t_init *data);
int op_lfork(t_cursor *cursor, t_init *data);
int op_lldi(t_cursor *cursor, t_init *data);
int    op_lld(t_cursor *cursor, t_init *data);
int op_fork(t_cursor *cursor, t_init *data);
int op_sti(t_cursor *cursor, t_init *data);
int op_ldi(t_cursor *cursor, t_init *data);
int op_zjmp(t_cursor *cursor, t_init *data);
int op_xor(t_cursor *cursor, t_init *data);
int op_or(t_cursor *cursor, t_init *data);
int op_and(t_cursor *cursor, t_init *data);
int op_sub(t_cursor *cursor, t_init *data);
int op_add(t_cursor *cursor, t_init *data);
int op_st(t_cursor *cursor, t_init *data);
int   op_ld(t_cursor *cursor, t_init *data);

static t_op    g_op_tab[17] =
        {
                {0, 0, {0}, 0, 0, 0, 0, 0, 4, &op_aff},
                {"live", 1, {T_DIR}, 1, 10, "alive", 0, 0, 4, &op_live},
                {"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0, 4, &op_ld},
                {"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0, 4, &op_st},
                {"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0, 4, &op_add},
                {"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0, 4, &op_sub},
                {"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
                        "et (and  r1, r2, r3   r1&r2 -> r3", 1, 0, 4, &op_and},
                {"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
                        "ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0, 4, &op_or},
                {"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
                        "ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0, 4, &op_xor},
                {"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1, 2, &op_zjmp},
                {"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
                        "load index", 1, 1, 2, &op_ldi},
                {"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
                        "store index", 1, 1, 2, &op_sti},
                {"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1, 2, &op_fork},
                {"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0, 4, &op_lld},
                {"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
                        "long load index", 1, 1, 2, &op_lldi},
                {"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1, 2, &op_lfork},
                {"aff", 1, {T_REG}, 16, 2, "aff", 1, 0, 4, &op_aff}
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
char *get_types_arg(t_cursor *cursor, unsigned char *arena);
unsigned char *int_to_code(int num);

#endif //COREWAR_COREWAR_H



//typedef struct s_cell
//{
//    unsigned char c;
//    int player;
//    int car;
//}              t_cell;