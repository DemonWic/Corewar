//
// Created by Виктор Рыжков on 08.12.2020.
//
#include "corewar.h"


int				ft_isnumber(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}


int ft_valname(char *file)
{
    int i;
    int len;

    if (file == NULL)
        return (0);
    len = ft_strlen(file);
    if (len < 5)
        return (0);
    i = len - 4;
    len = ft_strcmp(&file[i], ".cor");
    if (len == 0)
        return (1);
    return (0);
}

t_init  *init_data(void)
{
    t_init *data;

    data = (t_init *)ft_memalloc(sizeof(t_init));
    if (data == NULL)
        return (NULL);
    data->num = 0;
    data->cursor_num = 0;
    data->flag_n = 0;
    data->flag_dump = 0;
    data->flag_aff = 0;
    data->flag_vis = 0;
    data->pl_count = 0;
    data->invalid = 0;
    data->error.help = 0;
    data->error.invalid_head = 0;
    data->error.not_valid_file = 0;
    data->error.too_many_files = 0;
    data->error.large_code = 0;
    data->champs = (t_champ **)ft_memalloc((sizeof(t_champ) * MAX_PLAYERS));
    if (data->champs == NULL)
        return (NULL);
    return (data);
}

void    pre_valid(int argc, char **argv, t_init *data)
{
    int i;

    i = 1;
    while (i < argc)
    {
        if (ft_valname(argv[i]))
            data->pl_count++;
        else if (!ft_strcmp(argv[i], "-n"))
            data->flag_n++;
        else if (!ft_strcmp(argv[i], "-dump"))
            data->flag_dump++;
        else if (ft_isnumber(argv[i]))
            data->num++;
        else if (!ft_strcmp(argv[i], "-v"))
            data->flag_vis = 1;
        else if (!ft_strcmp(argv[i], "-a"))
            data->flag_aff = 1;
        else
            data->error.help = 1;
        i++;
    }
    if (data->num != (data->flag_n + data->flag_dump))
        data->error.help = 1;
}

int min_in_arr(t_init *data)
{
    int i;

    i = 1;
    while (i < (data->pl_count + 1))
    {
        if (data->nums[i] == 0)
            return (i);
        i++;
    }
    return (0);
}

int	code_to_int(unsigned char *code, size_t size)
{
    int	result;
    int	sign;
    int	i;

    result = 0;
    sign = (int)(code[0] & 128);
    i = 0;
    while (size)
    {
        if (sign)
            result += ((code[size - 1] ^ 255) << (i * 8));
        else
            result += code[size - 1] << (i * 8);
        size--;
        i++;
    }
    if (sign)
        result = ~(result);
    return (result);
}

int	code_to_int2(t_init *data, int addr, size_t size)
{
    int	result;
    int	sign;
    int	i;

    result = 0;
    sign = (int)(data->arena[cor_addr(addr)] & 128);
    size += addr;
    i = 0;
    while (size > addr)
    {
        if (sign)
            result += ((data->arena[cor_addr(size - 1)] ^ 255) << (i * 8));
        else
            result += data->arena[cor_addr(size - 1)] << (i * 8);
        size--;
        i++;
    }
    if (sign)
        result = ~(result);
    return (result);
}

unsigned char *int_to_code(int num)
{
    int		i;
    int     k;
    unsigned char *res;

    i = 0;
    k = 24;
    res = (unsigned char *)ft_memalloc(sizeof(unsigned char) * 4);
    while (i < 4)
    {
        res[i] = (num >> k) & 255;
        i++;
        k -= 8;
    }
    return (res);
}

void error_large_file(t_init *data, int num)
{
    ft_putstr("Error: File ");
    ft_putstr(data->champs[num]->file);
    ft_putstr(" has too large a code (");
    ft_putnbr(data->champs[num]->size);
    ft_putstr(" bytes > ");
    ft_putnbr(CHAMP_MAX_SIZE);
    ft_putstr(" bytes)\n");
//    Error: File champs/42.cor has too large a code (993 bytes > 682 bytes)
}

void error_read_file(void)
{
    ft_putstr("ERROR: Can't open file with champion: No such file or directory\n");
}

void error_many_champ(void)
{
    ft_putstr("Too many champions\n");
}

void error_invalid_head(t_init *data, int num)
{
    ft_putstr("Error: File ");
    ft_putstr(data->champs[num]->file);
    ft_putstr(" has an invalid header\n");
}

void print_help(void)
{
    ft_putstr("Usage: ./corewar [-a -dump <num> -n <num>] <champion.cor> <...>\n");
    ft_putstr("-a          : Print output from \"aff\" (Default is off)\n");
    ft_putstr("-dump <num> : Dump memory (32 octets per line) after <num> cycles and exit\n");
    ft_putstr("-n    <num> : Set <num> of the next player\n");
}


int check_errors(t_init *data, int num)
{
    if (data->error.help)
    {
        print_help();
        return (1);
    }
    if (data->error.invalid_head || data->error.not_valid_file) // возможно стоит вынести в отдельный ->    проверить corewar еще раз
    {
        error_invalid_head(data, num);
        return (1);
    }
    if (data->error.large_code)
    {
        error_large_file(data, num);
        return (1);
    }
    if (data->error.no_such_file)
    {
        error_read_file();
        return (1);
    }
    if (data->error.too_many_files)
    {
        error_many_champ();
        return (1);
    }
    return (0);
}

void	ft_unmemcpy2(t_init *data, int addr, unsigned char *src, size_t n)
{
    size_t	i;

    i = 0;
    while (i < n)
    {
        data->arena[cor_addr(addr)] = src[i];
        i++;
        addr++;
    }
}

void	*ft_unmemcpy(void *dst, const void *src, size_t n)
{
    unsigned char	*s;
    unsigned char	*d;
    size_t	i;

    s = (unsigned char *)src;
    d = (unsigned char *)dst;
    i = 0;
    while (i < n)
    {
        d[i] = s[i];
        i++;
    }
    return (d);
}