/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 11:51:54 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/16 08:29:50 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_nbr(int nlink, int space)
{
	int		n;

	n = space - ft_count_digit(nlink, 10);
	if (nlink == 0)
		n--;
	while (n-- > 0)
		ft_putchar(' ');
	ft_putnbr(nlink);
	ft_putchar(' ');
}

void	print_str(char *str, int space)
{
	int		n;

	n = space - ft_strlen(str);
	ft_putstr(str);
	while (n-- > 0)
		ft_putchar(' ');
	ft_putstr("  ");
}

void	print_majmin(t_file *file, t_space *spaces)
{
	int		min;
	int		maj;

	min = ft_count_digit(minor(file->st_rdev), 10);
	maj = ft_count_digit(major(file->st_rdev), 10);
	ft_putnbr(major(file->st_rdev));
	while (maj < spaces->maj--)
		ft_putchar(' ');
	ft_putstr(", ");
	ft_putnbr(minor(file->st_rdev));
	while (min < spaces->min--)
		ft_putchar(' ');
	ft_putchar(' ');
}

void	print_date(time_t date)
{
	t_date	*fdate;
	time_t	actual_time;

	actual_time = time(0);
	fdate = ft_parse_date(&date);
	ft_putstr(fdate->month);
	ft_putchar(' ');
	if (ft_strlen(fdate->day_of_month) == 1)
		ft_putchar(' ');
	ft_putstr(fdate->day_of_month);
	ft_putchar(' ');
	if ((actual_time - 15724800) > date || actual_time < date)
	{
		ft_putchar(' ');
		ft_putstr(fdate->year);
	}
	else
		write(1, fdate->time, 5);
	ft_putchar(' ');
	ft_destroy_date(fdate);
}
