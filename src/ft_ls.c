#include "ft_ls.h"
#include <stdio.h>

void	start_ls(t_args *args, t_array *paths)
{
	t_array	*tmp;
	t_array	*files;
	t_array	*dirs;
	DIR		*dir;

	tmp = paths;
	while (tmp && args)
	{
		if ((dir = opendir(tmp->data)) == NULL)
		{
			if (errno != ENOTDIR)
				ft_error(tmp->data);
			else
				files = array_init(files, tmp->data);
		}
		else
		{
			dirs = array_init(dirs, tmp->data);
			if (closedir(dir) == -1)
				ft_error(tmp->data);
		}
		tmp = tmp->next;
	}
}
