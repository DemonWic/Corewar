/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_asm_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loram <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 02:44:15 by loram             #+#    #+#             */
/*   Updated: 2021/01/14 02:44:16 by loram            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_errors.h"

static t_data		*error_reading_file(int fd, char *err_str, t_data *data)
{
	close(fd);
	return (print_error_init(err_str, data));
}

static t_data		*get_input_data(char *file, t_data *data, char *temp)
{
	char		buf[1025];
	int			input_count;
	int			fd;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (print_error_init(ERR_READ_FILE, NULL));
	if (!(data->input = ft_strnew(1)))
		return (error_reading_file(fd, ERR_PARSER_INIT, data));
	input_count = read(fd, buf, 1024);
	while (input_count > 0)
	{
		buf[input_count] = '\0';
		temp = data->input;
		data->input = ft_strnjoin(data->input, buf, input_count);
		if (!(data->input))
			return (error_reading_file(fd, ERR_READ_FILE, data));
		ft_memdel((void **)&temp);
		data->data_size += input_count;
		input_count = read(fd, buf, 1024);
	}
	if (input_count == -1)
		return (error_reading_file(fd, ERR_READ_FILE, data));
	close(fd);
	return (data);
}

static t_data		*error_getting_data(char *err_str, t_data *data)
{
	clean_data(data);
	if (err_str)
		return (print_error_init(err_str, NULL));
	else
		return (NULL);
}

t_data				*get_asm_data(char *file)
{
	int			len_file;
	t_data		*data;

	data = init_asm_data();
	if (data)
	{
		len_file = ft_strlen(file);
		data->name_file = ft_strnew(len_file - 2);
		if (!(data->name_file))
			return (error_getting_data(ERR_NO_NAME, data));
		else
		{
			data->name_file = ft_strncpy(data->name_file, file, len_file - 2);
			data->data_size = 0;
			if (!(get_input_data(file, data, NULL)))
				return (error_getting_data(NULL, data));
			return (data);
		}
	}
	else
		return (NULL);
}
