#include "ft_ls.h"
#include <stdio.h>

static void			scan(char *str, t_array *files, t_array *dirs)
{
	DIR		*dir;

	if ((dir = opendir(str)) == NULL)
	{
		if (errno != ENOTDIR)
			ft_error(str);
		else
			files = array_init(files, str);
	}
	else
	{
		dirs = array_init(dirs, str);
		if (closedir(dir) == -1)
			ft_error(str);
	}
}

void				start_ls(t_args *args, t_array *paths)
{
	t_array	*tmp;
	t_array	*files;
	t_array	*dirs;

	files = NULL;
	dirs = NULL;
	tmp = paths;
	while (tmp && args)
	{
		scan(tmp->data, files, dirs);
		tmp = tmp->next;
	}
}
