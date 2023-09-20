/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherman <aherman@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:33:37 by aherman           #+#    #+#             */
/*   Updated: 2023/09/19 22:09:28 by aherman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	find_index_envp(char **envp)
{
	int		i;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			break ;
	}
	return (i);
}

char	*ft_getpath(char **envp, char *prog)
{
	char	**env;
	char	*path;
	char	*new_path;
	char	*temp;
	int		i;

	path = NULL;
	i = find_index_envp(envp);
	env = ft_split(envp[i] + 5, ':');
	i = -1;
	while (env[++i])
	{
		temp = ft_strjoin(env[i], "/");
		new_path = ft_strjoin(temp, prog);
		free(temp);
		if (access(new_path, X_OK | F_OK) == 0)
		{
			path = new_path;
			break ;
		}
		else
			free(new_path);
	}
	free_tab(env);
	return (path);
}

void	free_tab(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	pipex(int f1, int f2, t_info *info, char **envp)
{
	int		status;

	info->cmd1 = ft_getpath(envp, info->split1[0]);
	if (info->cmd1 == 0)
		ft_error(-1);
	info->cmd2 = ft_getpath(envp, info->split2[0]);
	if (info->cmd2 == 0)
		ft_error(-1);
	if (pipe(info->_pipe) < 0)
		ft_error(-1);
	info->p_id_c1 = fork();
	if (info->p_id_c1 < 0)
		ft_error(-1);
	if (info->p_id_c1 == 0)
		child_one(f1, info->cmd1, info, envp);
	info->p_id_c2 = fork();
	if (info->p_id_c2 < 0)
		ft_error(-1);
	if (info->p_id_c2 == 0)
		child_two(f2, info->cmd2, info, envp);
	close(info->_pipe[0]);
	close(info->_pipe[1]);
	waitpid(info->p_id_c1, &status, 0);
	waitpid(info->p_id_c2, &status, 0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_info	info;

	if (argc != 5 || argv[2][0] == '\0' || argv[3][0] == '\0')
	{
		if (argc != 5)
			ft_putendl_fd("Error: Invalid number of arguments", 2);
		else
			ft_putendl_fd("Error: Command null", 2);
		exit (1);
	}
	info.fd1 = open(argv[1], O_RDONLY);
	if (info.fd1 < 0)
		ft_error(-1);
	info.fd2 = open(argv[4], O_CREAT | O_TRUNC | O_WRONLY, 0000644);
	if (info.fd2 < 0)
		ft_error(-1);
	info.split1 = ft_split(argv[2], ' ');
	info.split2 = ft_split(argv[3], ' ');
	pipex(info.fd1, info.fd2, &info, envp);
	return (EXIT_SUCCESS);
}
