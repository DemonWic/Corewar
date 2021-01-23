/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_powint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loram <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 19:48:36 by loram             #+#    #+#             */
/*   Updated: 2019/09/21 19:53:42 by loram            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_powint(int num, int exp)
{
	int		res;
	int		temp;

	if ((exp < 0) || ((num == 0) && (exp == 0)))
		return (-1);
	if (exp == 0)
		return (1);
	temp = num;
	res = temp;
	while (exp > 0)
	{
		res = res * num;
		if (res / num != temp)
			return (-1);
		temp = res;
		exp--;
	}
	return (res);
}
