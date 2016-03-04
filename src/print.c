/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 11:51:54 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/04 16:24:59 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_nbr(int nlink, int space)
{
	int		n;

	n = space - count_digit(nlink);
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

	min = (int)ft_strlen(ft_itoa(minor(file->st_rdev)));
	maj = (int)ft_strlen(ft_itoa(major(file->st_rdev)));
	ft_putnbr(major(file->st_rdev));
	while (maj < spaces->maj--)
		ft_putchar(' ');
	ft_putstr(", ");
	ft_putnbr(minor(file->st_rdev));
	while (min < spaces->min--)
		ft_putchar(' ');
	ft_putchar(' ');
}

void	print_date(time_t *date)
{
	char	*str1;
	char	*str2;
	time_t	actual_time;

	actual_time = time(0);
	str1 = ctime(date);
	if ((actual_time - 15778463) > *date || actual_time < *date)
	{
		str2 = ft_strnew(6);
		str2 = ft_strsub(str1, 20, 4);
		str1 = ft_strsub(str1, 4, 6);
		str1 = ft_strjoin(str1, "  ");
		str1 = ft_strjoin(str1, str2);
		free(str2);
	}
	else
		str1 = ft_strsub(str1, 4, 12);
	str1[12] = '\0';
	ft_putstr(str1);
	ft_putchar(' ');
	free(str1);
}
