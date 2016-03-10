/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 11:51:22 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/10 09:03:49 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_lnk(t_file *file)
{
	char	*link;
	int		ret;

	link = NULL;
	if (S_ISLNK(file->st_mode))
	{
		if ((link = ft_strnew(1024)))
		{
			ret = readlink(file->path, link, 1024);
			ft_putstr(" -> ");
			ft_putstr(link);
		}
	}
	if (link)
		free(link);
}

static void	long_file_display(t_file *file, t_space *spaces)
{
	print_permissions(file);
	print_nbr(file->st_nlink, spaces->link);
	if (getpwuid(file->st_uid))
		print_str(getpwuid(file->st_uid)->pw_name, spaces->user);
	else
		print_str(ft_itoa(file->st_uid), spaces->user);
	if (getgrgid(file->st_gid))
		print_str(getgrgid(file->st_gid)->gr_name, spaces->group);
	else
		print_str(ft_itoa(file->st_gid), spaces->group);
	if (S_ISCHR(file->st_mode) || S_ISBLK(file->st_mode))
		print_majmin(file, spaces);
	else
		print_nbr(file->st_size, spaces->size);
	print_date(file->date);
	ft_putstr(file->name);
	print_lnk(file);
	ft_putchar('\n');
}

void		long_files_display(t_file *files, t_args *args, int is_dir)
{
	t_file		*tmp;
	t_space		*spaces;

	tmp = files;
	spaces = get_spaces(args, files);
	if (need_total_print(files, args, is_dir))
	{
		ft_putstr("total ");
		ft_putnbr(spaces->total);
		ft_putchar('\n');
	}
	while (tmp)
	{
		if (!(args->a == 0 && tmp->name[0] == '.'))
		{
			long_file_display(tmp, spaces);
		}
		tmp = tmp->next;
	}
	if (spaces)
		free(spaces);
}

void		display_multidir(char *str)
{
	ft_putstr(str);
	ft_putstr(":\n");
}

void		put_permission(char c)
{
	if (c == '\0')
		return ;
	ft_putchar(c);
}
