/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loram <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 17:03:17 by loram             #+#    #+#             */
/*   Updated: 2020/03/10 17:03:19 by loram            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

t_glist		*ft_glstnew(void const *content, size_t content_size,
						int fd, int eof)
{
	t_glist		*res;

	if ((res = (t_glist *)ft_memalloc(sizeof(t_glist))))
	{
		if (content == NULL)
		{
			res->fd = fd;
			res->eof = eof;
			res->content = NULL;
			res->content_size = 0;
		}
		else
		{
			if (!(res->content = ft_memalloc(content_size)))
			{
				free(res);
				return (NULL);
			}
			ft_memcpy(res->content, content, content_size);
			res->content_size = content_size;
		}
		res->next = NULL;
	}
	return (res);
}
