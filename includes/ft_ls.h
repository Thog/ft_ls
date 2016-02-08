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

void		compute_args(int ac, char **av, t_args **args, t_list **lst);

#endif
