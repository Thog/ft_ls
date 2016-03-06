/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 11:50:43 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/04 13:25:38 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

t_file		*file_stat(char *name, char *path)
{
	t_file			*file;
	struct stat		file_stat;

	if (!(file = (t_file*)malloc(sizeof(t_file))))
		return (NULL);
	file->name = ft_strdup(name);
	file->path = ft_strjoin(path, file->name);
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

int			add_file(t_file **files, char *name, char *path)
{
	t_file	*lst;

	if (!name)
		return (0);
	lst = *files;
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
		lst->next = file_stat(name, path);
	}
	else
		*files = file_stat(name, path);
	return (1);
}

int			add_file_dir(t_file **files, struct dirent *file, char *path)
{
	if (!file)
		return (0);
	return (add_file(files, file->d_name, path));
}

void		display_files(t_file *files, t_args *args, int is_dir)
{
	t_file	*tmp;

	tmp = files;
	tmp = sort_file(tmp, args);
	if (args->l)
		long_files_display(tmp, args, is_dir);
	else
		simple_files_display(tmp, args);
	if (args->upper_r)
		recursive_display(files, args);
}

void		simple_files_display(t_file *files, t_args *args)
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
