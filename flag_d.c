#include "corewar.h"

char	hex_char(int a)
{
	if (a < 10)
		return (a + '0');
	if (a >= 10 && a < 16)
		return (a + 'a' - 10);
	return (0);
}

void	print_buf(unsigned char *buf)
{
	int		i;
	int		j;
	int		counters[3];

	i = 0;
	counters[0] = 0;
	counters[1] = 0;
	counters[2] = 0;
	while (i < MEM_SIZE)
	{
		j = 0;
		ft_putstr("0x");
		ft_putchar(hex_char(counters[2]));
		ft_putchar(hex_char(counters[1]));
		ft_putchar(hex_char(counters[0]));
		ft_putchar('0');
        counters[0] += 2;
//        counters[0] += 4;
		if (counters[0] == 16)
		{
			counters[0] = 0;
			counters[1] += 1;
		}
		if (counters[1] == 16)
		{
			counters[1] = 0;
			counters[2] += 1;
		}
		ft_putstr(" :");
        while (j < 32)
//        while (j < 64)
		{
			ft_putchar(' ');
			ft_putchar(hex_char(buf[i + j] / 16));
			ft_putchar(hex_char(buf[i + j] % 16));
			j++;
		}
		if (counters[2] == 16)
			break ;
        i += 32;
//        i += 64;
        ft_putchar(' ');
        ft_putchar('\n');
	}
}