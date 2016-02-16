#include "ft_ls.h"

t_file		*file_stat(char *name, char *path, t_args *arg)
{
	(void)arg;
	t_file		*file;
	struct stat	file_stat;

	if (!(file = (t_file*)malloc(sizeof(t_file))))
		return (NULL);

	file->name = ft_strdup(name);
	file->path = ft_strjoin(path, name);
	if (lstat(file->path, &file_stat) == -1)
	{
		ft_error(file->path);
		return (NULL);
	}

	file->st_mode = file_stat.st_mode;
	file->st_nlink = file_stat.st_nlink;
	file->st_uid = file_stat.st_uid;
	file->st_gid = file_stat.st_gid;
	file->st_size = file_stat.st_size;
	file->st_blocks = file_stat.st_blocks;
	file->st_rdev = file_stat.st_rdev;
	file->date = file_stat.st_mtime;
	file->next = NULL;
	return (file);
}

int		add_file(t_file **files, char *name, char *path, t_args *args)
{
	t_file	*lst;

	if (!name)
		return (0);
	lst = *files;
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
		lst->next = file_stat(name, path, args);
	}
	else
		*files = file_stat(name, path, args);
	return (1);
}

void	display_files(t_file *files, t_args *args, int is_dir)
{
	t_file	*tmp;

	tmp = files;
	//tmp = sort_stats(tmp, args);
	if (args->l)
		long_files_display(files, args, is_dir);
	else
		simple_files_display(tmp, args);
	/*if (args->R)
	  recursive_display(arg, tmp);*/
}

void	simple_files_display(t_file *files, t_args *args)
{
	t_file	*tmp;

	tmp = files;
	while (tmp)
	{
		if (!(args->a == 0 && tmp->name[0] == '.'))
		{
			ft_putendl(tmp->name);
		}
		tmp = tmp->next;
	}
}
