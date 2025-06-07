/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 11:35:45 by fde-alme          #+#    #+#             */
/*   Updated: 2025/06/07 11:35:51 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**extract_paths_envp(char *envp[])
{
	char	**paths;
	char	*env_path;

	paths = NULL;
	env_path = NULL;
	while (*envp && !env_path)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			env_path = *envp + 5;
			break ;
		}
		envp++;
	}
	if (env_path)
		paths = ft_split(env_path, ':');
	return (paths);
}
