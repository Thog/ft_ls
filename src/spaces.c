
#include "ft_ls.h"

t_space		*get_space(t_args *args, t_file *files)
{
	t_file	*tmp;
	t_space	*space;

	if (!(space = (t_space*)malloc(sizeof(t_space))))
		return (NULL);
	tmp = files;
	while (tmp)
	{
		if (!(args->a == 0 && tmp->name[0] == '.'))
		{
			compute_quick(space, tmp);
		}
		tmp = tmp->next;
	}
}
