/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:48:46 by fde-alme          #+#    #+#             */
/*   Updated: 2025/06/02 22:48:20 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_commands()
{

}

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

char	***parse_args(int argc, char *argv[])
{
	char	***args;
	char	**split_args;
	int		i;

	i = 0;
	args = (char ***) malloc(argc * sizeof(char *) + 1);
	if (!args)
		return (NULL);
	while (argv[i + 1])
	{
		split_args = ft_split(argv[i + 1], ' ');
		if (!split_args)
		{
			i = 0;
			while(i < argc)
				free_split(args[i++]);
			return (free(args), NULL);
		}
		args[i] = split_args;
		i++;
	}
	args[i] = NULL;
	return (args);
}

ssize_t	check_args(char ***args, char **paths, size_t path_count)
{
	size_t	i;
	size_t	j;
	int		result;
	char	*path_slash;
	char	*full_path;

	i = 0;
	while (*args)
	{
		if (i == 0 || i == 3)
		{
			result = access(*args[i], F_OK);
			if (result == -1)
			{
				ft_printf("%s: %s", strerror(errno), *args[i]);
				return (-1);
			}
		}
		if (i == 1 || i == 2)
		{
			j = 0;
			while (j < path_count)
			{		
				path_slash = ft_strjoin(paths[j], "/");
				full_path = ft_strjoin(path_slash, *args[i]);
				free(path_slash);
				if (access(full_path, F_OK | X_OK) == 0)
					break;
				j++;
			}
			if (result == -1)
			{
				ft_printf("%s: %s", strerror(errno), *args[i]);
				return (-1);
			}
			i++;
		}
		args++;
	}
	return (0);
}

size_t	extract_paths_envp(char **envp, char ***paths)
{
	char	*env_path;
	int		count;

	env_path = NULL;
	while (*envp && !env_path)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			env_path = *envp + 5;
		envp++;
	}
	if (env_path && paths)
		*paths = ft_split(env_path, ':');
	count = 0;
	while (paths && paths[count])
		count++;
	return (count);
}

int	main(int argc, char *argv[], char **envp)
{
	char	***args;
	char	**paths;
	size_t	path_count;

	if (argc > 1)
	{
		args = parse_args(argc, argv);
		path_count = extract_paths_envp(envp, &paths);
		if (args)
			check_args(args, paths, path_count);
	}
	
	return (0);
}

void	print_matrix(char ***args)
{
	size_t	i;

	ft_printf("[\n");
	while (*args)
	{
		i = 0;
		ft_printf(" [");
		while((*args)[i])
			ft_printf("%s, ", (*args)[i++]);
		ft_printf("]\n");
		args++;
	}
	ft_printf("]\n");
}
