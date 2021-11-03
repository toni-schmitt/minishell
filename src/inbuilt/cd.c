/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:12:17 by tblaase           #+#    #+#             */
/*   Updated: 2021/11/03 22:13:22 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_home(char **envp, char **env_var)
{
	int		i;
	char	*path;

	i = 0;
	while (env_var && env_var[i] && ft_strcmp(env_var[i], "HOME=") != 0)
		i++;
	if (!env_var || ft_strlen(env_var[i]) <= 6) // env_var[i] == NULL not needed because strlen <= 6 will protect for that case as well
	{
		i = 0;
		while (envp[i])
		{
			if (ft_strcmp(envp[i], "HOME=") == 0)
			{
				path = ft_strdup(ft_strchr(envp[i], '=') + 1);
				return (path);
			}
			i++;
		}
	}
	return (ft_strdup(env_var[i]));
}

int	cd(char **argv, char **envp, char **env_var)
{
	char	*home;
	char	**split;
	int		i;

	home = find_home(envp, env_var);
printf("homefolder found:%s\n", home);
	if (argv[1] == NULL)
	{
		if (chdir(home) != 0)
		{
			perror("Error");
			return (1);
		}
		else
			return (0);
	}
	if (ft_strchr(argv[1], '~') != NULL)
	{
		// argv[1] = home; // need to refine that depending on the real input, probably leaks
		split = ft_split(argv[1], '~'); // dont need to split, i need to replace every occurance of it with home
	printf("split: %s, %s, %s\n", split[0], split[1], split[2]);
		i = 0;
		while (split[i + 1])
		{
			split[0] = ft_strstrjoin(split[0], split[i++], home);
		printf("argv[1]: %s\n", argv[1]);
		}
	}
	else if (opendir(argv[1]) == NULL && errno != 0)
	{
		perror("Error");
		return (1);
	}
	if (chdir(argv[1]) != 0)
	{
		perror("Error");
		return (1);
	}
	return (0);
}
