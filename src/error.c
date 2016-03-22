/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 11:52:20 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/22 16:07:37 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_error(t_file *file)
{
	ft_putstr_fd("ls: ", 2);
	if (errno == ENOENT)
		ft_putstr_fd(file->path, 2);
	else
		ft_putstr_fd(file->name, 2);
	ft_putstr_fd(": ", 2);
	perror("");
}

void	ft_error_str(char *str)
{
	ft_putstr_fd("ls: ", 2);
	if (errno == ENOENT)
		ft_putstr_fd(str, 2);
	else
		ft_putstr_fd(ft_get_filename(str), 2);
	ft_putstr_fd(": ", 2);
	perror("");
}

void	ls_usage(char c, t_args **args)
{
	ft_putstr_fd("ls: illegal option -- ", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("\nusage: ls [-Ralrt] [file ...]\n", 2);
	free(*args);
	exit(1);
}
