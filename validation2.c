#include "corewar.h"

int validation3(int a[5], char **argv, t_init *data)
{
	data->champs[a[1]] = (t_champ *)ft_memalloc(sizeof(t_champ));
	if (data->champs[a[1]] == NULL)
		return (1);
	data->champs[a[1]]->file = ft_strdup(argv[a[0]]);
	data->champs[a[1]]->num = 0;
	a[1]++;
	return (2);
}

void validation4(int a[5], char **argv, t_init *data)
{
	if (ft_isnumber(argv[a[0] + 1]) && ft_atoi(argv[a[0] + 1]) >= 0)
	{
		data->dump_num = ft_atoi(argv[a[0] + 1]);
		a[0]++;
	}
	else
		data->error.help = 1;
}

void validation5(int a[5], char **argv, t_init *data)
{
	if (ft_isnumber(argv[a[0] + 1]) && ft_atoi(argv[a[0] + 1]) >= 0)
	{
		data->d_num = ft_atoi(argv[a[0] + 1]);
		a[0]++;
	}
	else
		data->error.help = 1;
}

