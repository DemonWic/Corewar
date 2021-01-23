/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteemo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:36:25 by dteemo            #+#    #+#             */
/*   Updated: 2020/11/03 17:36:27 by dteemo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H
# define MAP_SIZE 100000
# define BITS_IN_INT	 (sizeof(int) * 8)
# define THREE_QUARTERS  ((int) ((BITS_IN_INT * 3) / 4))
# define ONE_EIGHTH	  ((int) (BITS_IN_INT / 8))
# define HIGH_BITS	   (~((unsigned int)(~0) >> ONE_EIGHTH ))

# include "libft.h"
# include <fcntl.h>

typedef struct		s_road
{
	char			*edge;
	int				len;
	struct s_road	*next;
}					t_road;

typedef struct		s_node
{
	char			*name;
	int				x;
	int				y;
	char			*rel;
	int				marker;
	int				met;
	int				exclude;
	struct s_node	*next;
}					t_node;

typedef struct		s_lem
{
	t_road			*road;
	int				n;
	int				finished;
}					t_lem;

typedef struct		s_edge
{
	char			*begin;
	char			*end;
}					t_edge;

typedef struct		s_stack
{
	t_edge			*elem[MAP_SIZE];
	int				top;
}					t_stack;

typedef struct		s_queue
{
	char			*qu[MAP_SIZE + 1];
	int				rear;
	int				frnt;
}					t_queue;

typedef struct		s_data
{
	t_node			*start;
	t_node			*end;
	t_node			**nodes;
	t_road			**roads;
	char			**lines;
	int				lines_count;
	int				col;
	int				ant_count;
	int				roads_count;
	int				cur_n;
	int				check;
	int				invalid;
	t_queue			queue;
	t_stack			edges;
}					t_data;

unsigned int		ft_hash(const char *datum, int size);
t_node				*ft_search(const char *name, t_node **rooms);
char				*ft_strchrjoin(char *dest, char *src, char c);
t_data				*ft_read(int fd, int size_map);
void				ft_nodedelone(t_node **alst);
void				ft_nodedel(t_node **alst);
void				ft_datadel(t_data *data);
int					go_lem(t_data *data);
void				ft_stkinit(t_stack *stk);
int					ft_stkpush(t_stack *stk, t_edge *edge);
t_edge				*ft_stkpop(t_stack *stk);
int					ft_stkempty(t_stack *stk);
void				ft_quinit(t_queue *q);
int					ft_quinsert(t_queue *q, char *s);
int					ft_quempty(t_queue *q);
char				*ft_qupop(t_queue *q);
int					bfs(t_data *all, int count, int num);
void				ft_add_edge(t_road **road, int num, char *edge);
void				ft_error(char *mes);
int					ft_isnumber(char *str);
void				add_start_end(t_data *data, t_node *new);
void				push_node(t_data *data, t_node *new, int id);
t_node				*new_node(t_data *data, char **buf);
t_data				*init_data(int size_map);
void				ft_roaddel(t_road **alst);
int					add_lem(t_data *data, int i, t_lem *lems[data->ant_count],
		int cur_lems);
int					del_lems(t_data *data, t_lem *lems[data->ant_count]);
int					short_path(t_data *all);
void				free_edge(t_edge *e);
int					check_ret(t_data *data);
int					error_check(t_data *all);

#endif
