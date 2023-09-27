/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherman <aherman@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:33:37 by aherman           #+#    #+#             */
/*   Updated: 2023/09/27 12:22:08 by aherman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	ft_find_envp(char **envp)
{
	int		c1;

	c1 = -1;
	while (envp[++c1])
	{
		if (ft_strncmp("PATH=", envp[c1], 5) == 0)
			break ;
	}
	return (c1);
}

char	*ft_get_path(char **envp, char *cmd)
{
	int		c1;
	char	**env;
	char	*path;
	char	*new_path;
	char	*temp;

	path = NULL;
	c1 = ft_find_envp(envp);
	env = ft_split(envp[c1] + 5, ':');
	c1 = -1;
	while (env[++c1])
	{
		temp = ft_strjoin(env[c1], "/");
		new_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(new_path, X_OK | F_OK) == 0)
		{
			path = new_path;
			break ;
		}
		else
			free(new_path);
	}
	ft_free_char(env);
	return (path);
}

void	pipex(t_info *info, char **envp)
{
	int		status;

	info->cmd1 = ft_get_path(envp, info->split1[0]);
	if (info->cmd1 == 0)
		ft_error(1);
	info->cmd2 = ft_get_path(envp, info->split2[0]);
	if (info->cmd2 == 0)
		ft_error(1);
	if (pipe(info->_pipe) < 0)
		ft_error(-1);
	info->p_id_c1 = fork();
	if (info->p_id_c1 < 0)
		ft_error(-1);
	if (info->p_id_c1 == 0)
		child_one(info, envp);
	info->p_id_c2 = fork();
	if (info->p_id_c2 < 0)
		ft_error(-1);
	if (info->p_id_c2 == 0)
		child_two(info, envp);
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
	pipex(&info, envp);
	free(info.cmd1);
	free(info.cmd2);
	ft_free_char(info.split1);
	ft_free_char(info.split2);
	return (EXIT_SUCCESS);
}
