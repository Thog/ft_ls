/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 15:44:22 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/04 16:29:37 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char		*get_rwx(int mask)
{
	if (mask == 1)
		return ("--x");
	else if (mask == 2)
		return ("--x");
	else if (mask == 3)
		return ("-wx");
	else if (mask == 4)
		return ("r--");
	else if (mask == 5)
		return ("r-x");
	else if (mask == 6)
		return ("rw-");
	else if (mask == 7)
		return ("rwx");
	return ("---");
}

static char		get_type(int mode)
{
	char	c;

	c = '?';
	if (S_ISREG(mode))
		c = '-';
	else if (S_ISDIR(mode))
		c = 'd';
	else if (S_ISBLK(mode))
		c = 'b';
	else if (S_ISCHR(mode))
		c = 'c';
	else if (S_ISLNK(mode))
		c = 'l';
	else if (S_ISSOCK(mode))
		c = 's';
	else if (S_ISFIFO(mode))
		c = 'd';
	return (c);
}

static char		*create_perms(int mode)
{
	char	*result;

	result = ft_strnew(10);
	if (result == NULL)
		return (NULL);
	*result = get_type(mode);
	ft_strcpy(result + 1, get_rwx((mode >> 6) & 7));
	ft_strcpy(result + 4, get_rwx((mode >> 3) & 7));
	ft_strcpy(result + 7, get_rwx((mode & 7)));
	if (mode & S_ISUID)
		*(result + 3) = (mode & S_IXUSR) ? 's' : 'S';
	if (mode & S_ISGID)
		*(result + 6) = (mode & S_IXGRP) ? 's' : 'S';
	if (mode & S_ISVTX)
		*(result + 9) = (mode & S_IXUSR) ? 't' : 'T';
	return (result);
}

void			print_permissions(t_file *file)
{
	char	*perms;

	perms = create_perms(file->st_mode);
	ft_putstr(perms);
	ft_putstr("  ");
	free(perms);
}
