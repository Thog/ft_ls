/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 11:51:34 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/10 16:37:43 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		quick_check(t_space *space, t_file *file)
{
	int		tmp;

	tmp = ft_count_digit(file->st_nlink, 10);
	space->link = tmp > space->link ?
		tmp : space->link;
	tmp = ft_count_digit(major(file->st_rdev), 10);
	space->maj = tmp > space->maj ?
		tmp : space->maj;
	tmp = ft_count_digit(minor(file->st_nlink), 10);
	space->min = tmp > space->min ?
		tmp : space->min;
	tmp = ft_count_digit(file->st_size, 10);
	space->size = tmp > space->size ?
		tmp : space->size;
	space->total += file->st_blocks;
}

static void		get_spaces_sys(t_space *space, t_file *file)
{
	int		len;

	len = 0;
	if (getpwuid(file->st_uid))
		len = ft_strlen(getpwuid(file->st_uid)->pw_name);
	else
		len = ft_count_digit(file->st_uid, 10);
	space->user = len > space->user ? len : space->user;
	if (getgrgid(file->st_gid))
		len = ft_strlen(getgrgid(file->st_gid)->gr_name);
	else
		len = ft_count_digit(file->st_gid, 10);
	space->group = len > space->group ? len : space->group;
}

static t_space	*init_spaces(void)
{
	t_space	*result;

	if (!(result = (t_space*)malloc(sizeof(t_space))))
		return (NULL);
	result->total = 0;
	result->maj = 0;
	result->min = 0;
	result->user = 0;
	result->link = 0;
	result->group = 0;
	result->size = 0;
	return (result);
}

t_space			*get_spaces(t_args *args, t_file *files)
{
	t_file	*tmp;
	t_space	*space;

	if (!(space = init_spaces()))
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
