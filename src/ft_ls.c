#include "ft_ls.h"
#include <stdio.h>

void	start_ls(t_args *args, t_array *paths)
{
	t_array	*tmp;

	tmp = paths;
	while (tmp && args)
	{
		printf("%s\n", tmp->data);
		tmp = tmp->next;
	}
}
