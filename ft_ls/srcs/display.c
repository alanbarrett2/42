/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 11:18:41 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/06 16:52:11 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>
#include "../includes/ft_ls.h"

void		ft_display_file_permissions(t_file *file)
{
	ft_printf("%c", ft_file_type(file->stats.st_mode));
	ft_printf((file->stats.st_mode & S_IRUSR) ? "r" : "-");
	ft_printf((file->stats.st_mode & S_IWUSR) ? "w" : "-");
	if (file->stats.st_mode & S_ISUID)
		ft_printf(file->stats.st_mode & S_IXUSR ? "s" : "S");
	else
		ft_printf((file->stats.st_mode & S_IXUSR) ? "x" : "-");
	ft_printf((file->stats.st_mode & S_IRGRP) ? "r" : "-");
	ft_printf((file->stats.st_mode & S_IWGRP) ? "w" : "-");
	if (file->stats.st_mode & S_ISGID)
		ft_printf(file->stats.st_mode & S_IXGRP ? "s" : "S");
	else
		ft_printf((file->stats.st_mode & S_IXGRP) ? "x" : "-");
	ft_printf((file->stats.st_mode & S_IROTH) ? "r" : "-");
	ft_printf((file->stats.st_mode & S_IWOTH) ? "w" : "-");
	if (file->stats.st_mode & S_ISVTX)
		ft_printf(file->stats.st_mode & S_IXOTH ? "t" : "T");
	else
		ft_printf((file->stats.st_mode & S_IXOTH) ? "x" : "-");
	ft_printf("%c", ft_get_file_acl(*file));
}

void		ft_display_file(t_file *file, t_options params, t_display datas)
{
	char	*link_path;
	char	*path;

	if (!params.long_format)// && params.no_columns)
		return ((void)ft_printf("%s\n", file->name));
	//if (!params.long_format)
	//	return ((void)ft_printf("%-*s\t", datas.max_name_len, file->name));
	ft_display_file_permissions(file);
	ft_printf("%*lld %-*s %-*s ",
				datas.hard_link_len + 1, file->stats.st_nlink,
				datas.user_len + 1, file->user,
				datas.group_len + 1, file->group);
	if (file->major == -1 && file->minor == -1)
		ft_printf("%*lld ", datas.size_len, file->stats.st_size);
	else
		ft_printf("%*d, %*d ", datas.major_len, file->major,
				datas.minor_len, file->minor);
	ft_display_format_time(file->stats.st_mtime);
	if (S_ISLNK(file->stats.st_mode))
	{
		path = ft_set_path(params.current_path, file->name);
		link_path = ft_get_link_path(path);
		free(path);
		ft_printf(" %s -> %s\n", file->name, link_path);
		free(link_path);
	}
	else
		ft_printf(" %s\n", file->name);
}

t_display	ft_calcul_file_datas(t_file *files)
{
	t_display	datas;
	t_file		*ptr;

	ptr = files;
	ft_memset(&datas, 0, sizeof(datas));
	while (ptr)
	{
		datas.hard_link_len = ft_max(datas.hard_link_len,
				ft_nbrlen(ptr->stats.st_nlink));
		datas.size_len = ft_max(datas.size_len,
				ft_nbrlen((uintmax_t)ptr->stats.st_size));
		if (ptr->major > -1 || ptr->minor > -1)
			datas.major_len = ft_max(datas.major_len,
									ft_nbrlen((uintmax_t)ptr->major) + 1);
		if (ptr->major > -1 || ptr->minor > -1)
			datas.minor_len = ft_max(datas.minor_len,
									ft_nbrlen((uintmax_t)ptr->minor));
		datas.user_len = ft_max(datas.user_len, (int)ft_strlen(ptr->user));
		datas.group_len = ft_max(datas.group_len, (int)ft_strlen(ptr->group));
		datas.name_len = ft_max(datas.name_len, (int)ft_strlen(ptr->name));
		datas.total_blocks += ptr->stats.st_blocks;
		ptr = ptr->next;
	}
	if (datas.minor_len > 0 || datas.major_len > 0)
		datas.size_len = ft_max(datas.size_len,
				(datas.major_len + datas.minor_len + 2));
	return (datas);
}

void		ft_display_files(t_file *files, t_options params)
{
	t_file		*ptr;
	t_display	datas;

	ptr = files;
	datas = ft_calcul_file_datas(files);
	if (params.long_format && ptr && params.folders)
		ft_printf("total %d\n", datas.total_blocks);
	while (ptr)
	{
		ft_display_file(ptr, params, datas);
		ptr = ptr->next;
	}
}

void		ft_display_dir(t_dir *dir, t_options params)
{
	if (params.display_dirs || (params.recursive && params.dirs_count > 1))
	{
		if (params.dirs_count > 1)
			ft_printf("%c%s:\n", '\n', dir->name);
		else
			ft_printf("%s:\n", dir->name);
	}
	ft_display_files(dir->files, params);
}
