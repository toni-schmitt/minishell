/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 18:28:36 by tschmitt          #+#    #+#             */
/*   Updated: 2021/12/02 19:31:15 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "brain.h"

/*
 * STILL USES clear_history INSTEAD OF rl_clear_history
 * SUBJECT.PDF DOES NOT ALLOW CLEAR_HISTORY
 * GITHUB ACTION ONLY KNOWS clear_history!!!
 */
static int	exit_routine(void *to_free, int exit_status)
{
	clear_history(); // CHANGE TO rl_clear_history();
	free(to_free);
	return (exit_status);
}

static char	*get_nosebang(char *line)
{
	char	*nosebang;
	char	**arr;

	arr = ft_split_set(ft_strstr(line, "<<") + 2, " \t\n\v\f\r");
	if (arr == NULL)
		return (NULL);
	nosebang = ft_strdup(arr[0]);
	if (nosebang == NULL)
		return (NULL);
	ft_free_split(arr);
	return (nosebang);
}

static int	wait_for_nosebang(char *line)
{
	char	*buf;
	char	*nosebang;

	nosebang = get_nosebang(line);
	if (nosebang == NULL)
		return (EXIT_FAILURE);
	while (true)
	{
		buf = readline("> ");
		if (ft_strncmp(buf, nosebang, ft_strlen(buf)) == 0)
		{
			free(nosebang);
			free(buf);
			return (EXIT_SUCCESS);
		}
		free(buf);
	}
	return (EXIT_FAILURE);
}

static int	routine(void)
{
	char	*buf;

	while (true)
	{
		buf = readline("minishell$ ");
		if (ft_strlen(buf) > 0)
			add_history(buf);
		if (ft_strstr(buf, "<<"))
		{
			if (wait_for_nosebang(buf) == EXIT_FAILURE)
				return (exit_routine((void *)buf, EXIT_FAILURE));
		}
		if (lexer(buf) == EXIT_FAILURE)
			return (exit_routine((void *)buf, EXIT_FAILURE));
		free(buf);
	}
	return (exit_routine((void *)buf, EXIT_FAILURE));
}

int	main(int argc, char *argv[], char *envp[])
{
	return (lexer("echo hi | wc -l >>file1 && echo \"hi\" \"how are you doing\" \'$HI\' && ( echo \"this is such bullshit $PWD\" && false || ( echo \"pls stop\" | wc -l >file2 && cat file1 | wc >>file3 ) && cat file3 ) && false && echo stop << end cat"));
	if (argc != 1)
		return (EXIT_FAILURE);
	(void)argv;
	set_envp(envp);
	if (routine() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
