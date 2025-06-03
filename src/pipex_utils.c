/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:19:34 by fde-alme          #+#    #+#             */
/*   Updated: 2025/06/03 20:24:15 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Open the file and returns its FD 
	0: input - 1: output */
int	open_file(char filename, int )
{
	int	fd;

	fd = -1;
	if (option == 0)
		fd = open(filename, O_RDONLY);
	if (option == 1)
		fd = open(filename, O_CREAT | O_WRONLY, 0644);
	return (fd);
}

/* Joins the provided path and command to form the fullpath
	Ex: "/usr/bin" "grep" turns into "/usr/bin/grep" */
char	*build_cmd_path(char *path, char *command)
{
	char	*path_slash;
	char	*full_path;

	path_slash = ft_strjoin(path, "/");
	full_path = ft_strjoin(path_slash, command);
	free(path_slash);
	return (full_path);
}

/* Frees the strings and the array allocated by the function ft_split */
void	free_split(char **arr)
{
	size_t	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
