#include "ft_ls.h"

void	ft_error(char *str)
{
	char	*tmp;

	tmp = ft_strjoin("ft_ls: ", str);
	perror(tmp);
	free(tmp);
}
