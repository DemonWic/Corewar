#include "corewar.h"

void data_free(t_init *data)
{
	int i;
	
	i = 0;
	while (i < data->pl_count)
	{
		if (data->champs[i] != NULL)
		{
			if(data->champs[i]->file != NULL)
				free(data->champs[i]->file);
			if (data->champs[i]->code != NULL)
				free(data->champs[i]->code);
			free(data->champs[i]);
		}
		i++;
	}
	if (data->champs != NULL)
	    free(data->champs);
	free(data);
}

int read_champ3(int a[2], int ret, unsigned char buf2[4], t_init *data)
{
	ret = read(a[1], data->champs[a[0]]->comment, COMMENT_LENGTH);
	if (ret != COMMENT_LENGTH)
		data->error.invalid_head = 1;
	ret = read(a[1], buf2, 4);
	if (ret != 4 || code_to_int(buf2, 4) != 0)
		data->error.invalid_head = 1;
	data->champs[a[0]]->code = (unsigned char *)ft_memalloc(data->champs[a[0]]->size);
	if (data->champs[a[0]]->code == NULL)
		return (1);
	ret = read(a[1], data->champs[a[0]]->code, data->champs[a[0]]->size);
	if (ret != data->champs[a[0]]->size)
		data->error.invalid_head = 1;
	ret = read(a[1], buf2, 4);
	if (ret != 0)
		data->error.invalid_head = 1;
	return (ret);
}

int read_champ2(int a[2], int ret, unsigned char buf2[4], t_init *data)
{
	ret = read(a[1], buf2, 4);
	if (ret != 4)
		data->error.not_valid_file = 1;
	else if (code_to_int(buf2, 4) != COREWAR_EXEC_MAGIC)
		data->error.invalid_head = 1;
	ret = read(a[1], data->champs[a[0]]->name, PROG_NAME_LENGTH);
	if (ret != PROG_NAME_LENGTH)
		data->error.not_valid_file = 1;
	ret = read(a[1], buf2, 4);
	if (ret != 4 || code_to_int(buf2, 4) != 0)
		data->error.invalid_head = 1;
	ret = read(a[1], buf2, 4);
	if (ret != 4 || code_to_int(buf2, 4) < 0)
		data->error.invalid_head = 1;
	data->champs[a[0]]->size = code_to_int(buf2, 4);
	if (data->champs[a[0]]->size > CHAMP_MAX_SIZE)
		data->error.large_code = 1;
	return (read_champ3(a, ret, buf2, data));
}

int error_open(void)
{
    perror("ERROR: Can\'t open file with champion");
    return (1);
}

int read_champ(t_init *data)
{
	int a[2];
	int ret;
	unsigned char buf2[4];
	
	a[0] = 0;
	ret = 0;
	while (a[0] < data->pl_count)
	{
		if ((a[1] = open(data->champs[a[0]]->file, O_RDONLY, 0)) < 0)
		    return (error_open());
		else
			ret = read_champ2(a, ret, buf2, data);
		if (check_errors(data, a[0]))
		    return (1);

		a[0]++;
	}
	return (0);
}
