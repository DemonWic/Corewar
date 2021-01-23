/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_champ_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <bsausage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 02:36:52 by loram             #+#    #+#             */
/*   Updated: 2021/01/19 12:28:20 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_errors.h"

t_champ				*init_champ(void)
{
	t_champ		*champ;

	if (!(champ = (t_champ *)ft_memalloc(sizeof(t_champ))))
		return (print_error_init(ERR_CREATE_CHAMPION, NULL));
	return (champ);
}
