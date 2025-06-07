/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 11:37:10 by fde-alme          #+#    #+#             */
/*   Updated: 2025/06/07 13:53:04 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Create a matrix of cmds with its arguments. [["ls", "-la"], ["wc", "-l"]] */
char	***parse_commands(char **argv, int cmd_count)
{
	char	***cmds;
	int		i;

	i = 0;
	cmds = (char ***) malloc((cmd_count * sizeof(char **)));
	if (!cmds)
		return (NULL);
	while (i < cmd_count)
	{
		cmds[i] = ft_split(argv[i + 2], ' ');
		if (!cmds[i])
		{
			while (i--)
				free_split(cmds[i]);
			return (free(cmds), NULL);
		}
		i++;
	}
	return (cmds);
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

/* Looks up for command binaries in the paths extracted from env path */
char	*bin_lookup(char *command, char **paths)
{
	char	*bin_path;
	int		bin_found;

	bin_found = -1;
	while (*paths)
	{
		bin_path = build_cmd_path(*paths, command);
		if (!bin_path)
			return (NULL);
		bin_found = access(bin_path, F_OK);
		if (bin_found == 0)
			return (bin_path);
		free(bin_path);
		paths++;
	}
	return (NULL);
}
