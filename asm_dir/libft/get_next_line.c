/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loram <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 19:40:15 by loram             #+#    #+#             */
/*   Updated: 2019/10/24 23:54:40 by loram            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

static	void				remove_fdlist(int fd, t_glist **stock)
{
	t_glist				*current;

	current = *stock;
	if (current->fd == fd)
	{
		free(current->content);
		*stock = current->next;
		free(current);
	}
	else
	{
		while ((current->next->fd != fd) && !(current->next))
			current = current->next;
		if (current->next->fd == fd)
		{
			free(current->next->content);
			current->next = current->next->next;
			free(current->next);
		}
	}
}

static	t_glist				*get_fdlist(int fd, t_glist **stock)
{
	t_glist				*current;

	if (!(*stock) && !(*stock = ft_glstnew(NULL, 0, fd, 0)))
		return (NULL);
	current = *stock;
	while (current->fd != fd)
	{
		if ((!current->next) && (!(current->next = ft_glstnew(NULL, 0, fd, 0))))
			return (NULL);
		current = current->next;
	}
	return (current);
}

static char					*get_line_renew_list(char *eolptr, t_glist *lst)
{
	char				*temp;
	char				*line;

	line = ft_strsub(lst->content, 0, (eolptr - (char *)lst->content));
	lst->content_size -= (ssize_t)(eolptr - (char *)lst->content + 1);
	temp = lst->content;
	(lst->content_size) ? (lst->content = ft_strsub(lst->content,
			(eolptr - temp + 1), lst->content_size)) : (lst->content = NULL);
	free(temp);
	return (line);
}

static	char				*get_buffline(char **buff, ssize_t b_l,
											t_glist *lst)
{
	char				*eolptr;
	char				*temp;
	char				*line;

	line = NULL;
	if (b_l)
	{
		lst->content_size += b_l;
		temp = lst->content;
		lst->content = ft_strnjoin(lst->content, *buff, b_l);
		free(temp);
	}
	if (lst->content_size)
	{
		if ((eolptr = ft_strchr(lst->content, EOL)))
			line = get_line_renew_list(eolptr, lst);
		else if (lst->eof == 1)
		{
			line = ft_strdup(lst->content);
			lst->content_size = 0;
			free(lst->content);
			lst->content = NULL;
		}
	}
	return (line);
}

int							get_next_line(const int fd, char **line)
{
	ssize_t				buff_len;
	char				*tmp_buff;
	static	t_glist		*stock;
	t_glist				*current;

	if (fd < 0 || !line || !(current = get_fdlist(fd, &stock)))
		return (-1);
	tmp_buff = (!(current->content_size) ||
			(!(ft_strchr(current->content, EOL)) && !(current->eof))) ?
	(ft_strnew(BUFF_SIZE)) : (ft_strdup((char *)current->content));
	buff_len = 0;
	while (!(*line = get_buffline(&tmp_buff, buff_len, current)))
	{
		buff_len = read(fd, tmp_buff, BUFF_SIZE);
		if ((buff_len == 0) && (!(current->eof)) && (current->content_size))
			current->eof = 1;
		else if (buff_len <= 0)
		{
			free(tmp_buff);
			remove_fdlist(current->fd, &stock);
			return (buff_len);
		}
	}
	free(tmp_buff);
	return (1);
}
