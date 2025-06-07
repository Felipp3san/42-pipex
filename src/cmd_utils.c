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

char	*quote_lookup(char *cmd_str)
{
	if (strchr(cmd_str, '\"'))
		return ("\"");
	if (strchr(cmd_str, '\''))
		return ("\'");
	return (NULL);
}

void	trim_cmd(char **cmd)
{
	char	*old_str;
	int		i;

	i = 0;
	while (*(cmd + i))
	{
		old_str = *(cmd + i);
		*(cmd + i) = ft_strtrim(*(cmd + i), " \"");
		free(old_str);
		old_str = NULL;
		i++;
	}
}

/* Create a matrix of cmds with its arguments. [["ls", "-la"], ["wc", "-l"]] */
char	***parse_commands(char **argv, int cmd_count)
{
	char	***cmds;
	char	*quote;
	int		i;

	i = 0;
	cmds = (char ***) malloc((cmd_count * sizeof(char **)));
	if (!cmds)
		return (NULL);
	while (i < cmd_count)
	{
		quote = quote_lookup(argv[i + 2]);
		if (quote)
			cmds[i] = ft_split(argv[i + 2], *quote);
		else
			cmds[i] = ft_split(argv[i + 2], ' ');
		if (!cmds[i])
		{
			while (i--)
				free_split(cmds[i]);
			return (free(cmds), NULL);
		}
		trim_cmd(cmds[i]);
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

/* Looks up for command binaries in the paths extracted from env path.
 * Skips command lookup if command is found as it is, ex: fullpath as arg */
char	*bin_lookup(char *cmd, char **paths)
{
	char	*bin_path;
	int		bin_found;

	bin_found = -1;
	if (!cmd)
		return (NULL);
	if (access(cmd, F_OK) != -1)
		return (ft_strdup(cmd));
	while (paths && *paths)
	{
		bin_path = build_cmd_path(*paths, cmd);
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
