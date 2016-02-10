#ifndef FT_LS_H
# define FT_LS_H
#include <stdlib.h>
#include "libft.h"

typedef struct		s_args
{
	int				l;
	int				R;
	int				a;
	int				r;
	int				t;
}					t_args;

typedef struct		s_array
{
	char			*data;
	struct s_array	*next;
}					t_array;


t_array		*array_init(t_array *root, char *data);
void		compute_args(int ac, char **av, t_args **args, t_array **lst);
void		start_ls(t_args *args, t_array *paths);

#endif
