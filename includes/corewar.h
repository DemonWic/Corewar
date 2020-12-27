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

#endif //COREWAR_COREWAR_H



//typedef struct s_cell
//{
//    unsigned char c;
//    int player;
//    int car;
//}              t_cell;