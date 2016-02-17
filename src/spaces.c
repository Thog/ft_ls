
#include "ft_ls.h"

static void	quick_check(t_space *space, t_file *file)
{
	char	*tmp;

	tmp = ft_itoa(file->st_nlink);
	space->link = (int)ft_strlen(tmp) > space->link ?
		(int)ft_strlen(tmp) : space->link;
	free(tmp);
	tmp = ft_itoa(major(file->st_rdev));
	space->maj = (int)ft_strlen(tmp) > space->maj ?
		(int)ft_strlen(tmp) : space->maj;
	free(tmp);
	tmp = ft_itoa(minor(file->st_nlink));
	space->min = (int)ft_strlen(tmp) > space->min ?
		(int)ft_strlen(tmp) : space->min;
	free(tmp);
	tmp = ft_itoa(file->st_size);
	space->size = (int)ft_strlen(tmp) > space->size ?
		(int)ft_strlen(tmp) : space->size;
	free(tmp);
	space->total += file->st_blocks;
}

static void	get_spaces_sys(t_space *space, t_file *file)
{
	int		len;
	char	*tmp;

	len = 0;
	if (getpwuid(file->st_uid))
	{
		tmp = getpwuid(file->st_uid)->pw_name;
		len = (int)ft_strlen(tmp);
	}
	else
	{
		tmp = ft_itoa(file->st_uid);
		len = (int)ft_strlen(tmp);
		free(tmp);
	}
	space->user = len > space->user ? len : space->user;
	if (getgrgid(file->st_gid))
	{
		tmp = getgrgid(file->st_gid)->gr_name;
		len = (int)ft_strlen(tmp);
	}
	else
	{
		tmp = ft_itoa(file->st_gid);
		len = (int)ft_strlen(tmp);
		free(tmp);
	}
	space->group = len > space->group ? len : space->group;
}

t_space		*get_spaces(t_args *args, t_file *files)
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
			quick_check(space, tmp);
			get_spaces_sys(space, tmp);
		}
		tmp = tmp->next;
	}
	return (space);
}
