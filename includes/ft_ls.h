/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 12:25:12 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/10 15:19:23 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <unistd.h>
# include <errno.h>
# include <uuid/uuid.h>
# include "libft.h"

# define MAJOR(x)((int32_t)(((u_int32_t)(x) >> 24) & 0xff))
# define MINOR(x)((int32_t)((x) & 0xffffff))

typedef struct		s_args
{
	int				l;
	int				upper_r;
	int				a;
	int				r;
	int				t;
}					t_args;

typedef struct		s_array
{
	char			*data;
	struct s_array	*next;
}					t_array;

typedef struct		s_file
{
	char			*name;
	char			*path;
	time_t			date;
	long			datensec;
	mode_t			st_mode;
	nlink_t			st_nlink;
	uid_t			st_uid;
	gid_t			st_gid;
	off_t			st_size;
	quad_t			st_blocks;
	dev_t			st_rdev;
	struct s_file	*next;
}					t_file;

typedef struct		s_space
{
	int				total;
	int				size;
	int				user;
	int				link;
	int				group;
	int				min;
	int				maj;
}					t_space;

t_array				*array_init(t_array *root, char *data);
t_file				*file_stat(char *name, char *path);
t_space				*get_spaces(t_args *args, t_file *file);
int					add_file(t_file **files, char *name, char *path);
int					add_file_dir(t_file **files, struct dirent *file,
		char *path);
int					prepare_args(char *str, t_args *args, t_array **lst,
		int force_file);
void				display_files(t_file *files, t_args *args, int is_dir);
void				simple_files_display(t_file *files, t_args *args);
void				long_files_display(t_file *files, t_args *args, int is_dir);
void				print_nbr(int nlink, int space);
void				print_str(char *str, int space);
void				print_majmin(t_file *file, t_space *spaces);
void				print_permissions(t_file *file);
void				print_date(time_t date);
void				start_ls(t_args *args, t_array *paths);
void				ft_error(char *str);
int					cmp_alpha(t_file *file1, t_file *file2);
int					cmp_time(t_file *file1, t_file *file2);
t_file				*sort_file(t_file *lst, t_args *args);
t_args				*init_args(void);
int					count_digit(int i);
void				display_multidir(char *str);
void				put_permission(char c);
void				destroy_array(t_array *array);
void				destroy_files(t_file *files);
void				prepare_dir(t_args *args, t_array *paths, int multi_dir);
void				scan(char *str, t_array **files, t_array **dirs);
void				recursive_display(t_file *files, t_args *args);
int					need_total_print(t_file *files, t_args *args, int mdir);
void				ls_usage(char c, t_args **args);
#endif
