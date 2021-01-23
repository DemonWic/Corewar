/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loram <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 17:45:19 by loram             #+#    #+#             */
/*   Updated: 2020/03/10 17:45:21 by loram            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include "macro.h"
# include <stdlib.h>
# include <unistd.h>

# define EOL		'\n'

typedef struct		s_glist
{
	void			*content;
	size_t			content_size;
	int				eof;
	int				fd;
	struct s_glist	*next;
}					t_glist;

t_glist				*ft_glstnew(void const *content, size_t content_size,
								int fd, int eof);

#endif
