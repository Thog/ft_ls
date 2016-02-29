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

void	print_permissions(t_file *file)
{
	ft_putchar((S_ISFIFO(file->st_mode)) ? 'p' : '\0');
	ft_putchar((S_ISCHR(file->st_mode)) ? 'c' : '\0');
	ft_putchar((S_ISDIR(file->st_mode)) ? 'd' : '\0');
	ft_putchar((S_ISBLK(file->st_mode)) ? 'b' : '\0');
	ft_putchar((S_ISREG(file->st_mode)) ? '-' : '\0');
	ft_putchar((S_ISLNK(file->st_mode)) ? 'l' : '\0');
	ft_putchar((S_ISSOCK(file->st_mode)) ? 's' : '\0');
	ft_putchar((file->st_mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((file->st_mode & S_IWUSR) ? 'w' : '-');
	ft_putchar((file->st_mode & S_IXUSR) ? 'x' : '-');
	ft_putchar((file->st_mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((file->st_mode & S_IWGRP) ? 'w' : '-');
	ft_putchar((file->st_mode & S_IXGRP) ? 'x' : '-');
	ft_putchar((file->st_mode & S_IROTH) ? 'r' : '-');
	ft_putchar((file->st_mode & S_IWOTH) ? 'w' : '-');
	ft_putchar((file->st_mode & S_IXOTH) ? 'x' : '-');
	ft_putstr("  ");
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
