#include "ft_ls.h"

int		cmp_alpha(t_file *file1, t_file *file2)
{
	return (ft_strcmp(file1->name, file2->name));
}

int		cmp_time(t_file *file1, t_file *file2)
{
	return (file1->date < file2->date);
}
