/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 09:03:57 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/22 14:55:04 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	display_dir_recursively(char *str, char *name, t_args *args)
{
	t_file	*content;
	char	*path;
	DIR		*dir;

	path = ft_strjoin(str, "/");
	ft_putchar('\n');
	ft_putstr(str);
	ft_putstr(":\n");
	if ((dir = opendir(str)))
	{
		content = NULL;
		while (add_file_dir(&content, readdir(dir), path))
			;
		closedir(dir);
		if (content)
			display_files(content, args, 1);
	}
	else
		ft_error(name);
	ft_strdel(&path);
}

void	recursive_display(t_file *files, t_args *args)
{
	t_file	*tmp;

	tmp = files;
	while (tmp)
	{
		if (tmp->name && tmp->path && S_ISDIR(tmp->st_mode) &&
				ft_strcmp("..", tmp->name) && ft_strcmp(".", tmp->name) &&
				!(!args->a && tmp->name[0] == '.'))
			display_dir_recursively(tmp->path, tmp->name, args);
		tmp = tmp->next;
	}
}
