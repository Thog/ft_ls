#include "ft_ls.h"

void	print_nbr(int nlink, int space)
{
	int		n;

	n = space - ft_strlen(ft_itoa(nlink));
	while (n-- > 0)
		ft_putchar(' ');
	ft_putnbr(nlink);
	ft_putstr(" ");
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
