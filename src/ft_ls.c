/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 11:51:48 by tguillem          #+#    #+#             */
/*   Updated: 2016/04/14 09:21:00 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

static void			scan(char *str, t_array **files, t_array **dirs,
		t_args *args)
{
	DIR				*dir;
	struct stat		tmp;
	int				stat_ret;

	stat_ret = lstat(str, &tmp);
	if ((dir = opendir(str)) == NULL)
	{
		if (errno != ENOTDIR && (stat_ret || !S_ISLNK(tmp.st_mode)))
			ft_error_str(str);
		else
			*files = array_init(*files, str);
	}
	else
	{
		if (S_ISLNK(tmp.st_mode) && args->l)
			*files = array_init(*files, str);
		else
			*dirs = array_init(*dirs, str);
		if (closedir(dir) == -1)
			ft_error_str(str);
	}
}

static void			compute_files(t_args *args, t_array *files)
{
	t_array	*tmp;
	t_file	*stats;

	stats = NULL;
	tmp = files;
	while (tmp)
	{
		add_file(&stats, tmp->data, "");
		tmp = tmp->next;
	}
	if (stats)
		display_files(stats, args, 0);
}

static void			compute_dir(t_args *args, t_file *dirs, int multi_dir)
{
	DIR		*dir;
	t_file	*files;
	int		first_file;
	char	*path;

	first_file = 1;
	while (dirs)
	{
		path = !ft_strcmp(dirs->path, "/") ? ft_strdup(dirs->path) :
			ft_strjoin(dirs->path, "/");
		files = NULL;
		dir = opendir(dirs->name);
		while (add_file_dir(&files, readdir(dir), path))
			;
		closedir(dir);
		if (files)
		{
			first_file = put_permission(first_file ? '\0' : '\n');
			if (multi_dir)
				display_multidir(dirs->name);
			display_files(files, args, 1);
		}
		dirs = dirs->next;
		ft_strdel(&path);
	}
}

void				prepare_dir(t_args *args, t_array *paths, int multi_dir)
{
	t_array	*tmp;
	t_file	*dirs;

	tmp = paths;
	dirs = NULL;
	while (tmp)
	{
		add_file(&dirs, tmp->data, "");
		tmp = tmp->next;
	}
	dirs = sort_file(dirs, args);
	compute_dir(args, dirs, multi_dir);
	destroy_files(dirs);
}

void				start_ls(t_args *args, t_array *paths)
{
	t_array	*tmp;
	t_array	*files;
	t_array	*dirs;

	files = NULL;
	dirs = NULL;
	tmp = paths;
	while (tmp)
	{
		scan(tmp->data, &files, &dirs, args);
		tmp = tmp->next;
	}
	if (files)
		compute_files(args, files);
	if (files && dirs)
		write(1, "\n", 1);
	if (dirs)
		prepare_dir(args, dirs, paths->next != NULL);
	destroy_elem(files);
	destroy_elem(dirs);
}
