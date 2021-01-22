#include "corewar.h"

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

//int	code_to_int2(t_init *data, int addr, size_t size)
//{
//    int	result;
//    int	sign;
//    int	i;
//
//    result = 0;
//    sign = (int)(data->arena[cor_addr(addr)] & 128);
//    size += addr;
//    i = 0;
//    while (size > addr)
//    {
//        if (sign)
//            result += ((data->arena[cor_addr(size - 1)] ^ 255) << (i * 8));
//        else
//            result += data->arena[cor_addr(size - 1)] << (i * 8);
//        size--;
//        i++;
//    }
//    if (sign)
//        result = ~(result);
//    return (result);
//}

int	code_to_int2(t_init *data, int addr, int size)
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
}

