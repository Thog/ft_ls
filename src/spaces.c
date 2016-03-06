/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 11:51:34 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/04 16:18:22 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		quick_check(t_space *space, t_file *file)
{
	int		tmp;

	tmp = count_digit(file->st_nlink);
	space->link = tmp > space->link ?
		tmp : space->link;
	tmp = count_digit(major(file->st_rdev));
	space->maj = tmp > space->maj ?
		tmp : space->maj;
	tmp = count_digit(minor(file->st_nlink));
	space->min = tmp > space->min ?
		tmp : space->min;
	tmp = count_digit(file->st_size);
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
		len = count_digit(file->st_uid);
	space->user = len > space->user ? len : space->user;
	if (getgrgid(file->st_gid))
		len = ft_strlen(getgrgid(file->st_gid)->gr_name);
	else
		len = count_digit(file->st_gid);
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
