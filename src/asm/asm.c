/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loram <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 02:46:25 by loram             #+#    #+#             */
/*   Updated: 2021/01/14 02:46:27 by loram            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_errors.h"

static int			check_extension(char *file_name, char *file_ext)
{
	size_t		len_name;
	size_t		len_ext;

	if (file_name == NULL || file_ext == NULL)
		return (0);
	else
	{
		len_name = 0;
		len_ext = 0;
		len_name = ft_strlen(file_name);
		len_ext = ft_strlen(file_ext);
		if (len_name == 0 || len_ext == 0 ||
									file_name[len_name - len_ext - 1] != '.')
			return (0);
		return (ft_strequ(&file_name[len_name - len_ext], file_ext));
	}
}

static void			error_message(char *argv, int fd)
{
	ft_putstr_fd("\033[31m", fd);
	ft_putstr_fd(ERR_INVALID_FILE, fd);
	ft_putstr_fd("\033[0m", fd);
	ft_putstr_fd(" \033[33m-\033[0m ", fd);
	ft_putstr_fd(argv, fd);
	ft_putstr_fd("\033[0m\n", fd);
}

static void			cor_error_message(char *argv, int fd)
{
	ft_putstr_fd("\033[31m", fd);
	ft_putstr_fd("Disassembler is not implemented", fd);
	ft_putstr_fd("\033[0m", fd);
	ft_putstr_fd(" \033[33mfor file\033[0m ", fd);
	ft_putstr_fd(argv, fd);
	ft_putstr_fd("\033[0m\n", fd);
}

int					main(int argc, char **argv)
{
	int			i;

	i = 1;
	if (argc < 2)
	{
		ft_putendl_fd("\033[33mUsage:\t\033[0m ./asm [champion's_name].s\n", 2);
		ft_putendl_fd("\t\t(Compile .s to .cor files)\n", 2);
		return (0);
	}
	while (i < argc)
	{
		if (check_extension(argv[i], "s"))
			parse_asm(argv[i]);
		else if (check_extension(argv[i], "cor"))
			cor_error_message(argv[i], 2);
		else
			error_message(argv[i], 2);
		i++;
	}
	return (0);
}
