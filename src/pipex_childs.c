/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_childs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherman <aherman@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:05:46 by aherman           #+#    #+#             */
/*   Updated: 2023/09/19 22:06:28 by aherman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_tab_free(void **p)
{
	int	c1;

	c1 = 0;
	while (p[c1])
	{
		free(p[c1]);
		c1++;
	}
	free(p);
}

void	ft_error(int flag)
{
	if (flag == 1)
		ft_putendl_fd("Error: command does not exist", 2);
	else
		perror("Error");
	exit(1);
}

void	child_one(int f1, char *cmd1, t_info *info, char **envp)
{
	close(info->_pipe[0]);
	dup2(f1, STDIN_FILENO);
	dup2(info->_pipe[1], STDOUT_FILENO);
	close(f1);
	close(info->_pipe[1]);
	execve(cmd1, info->split1, envp);
	ft_error(-1);
}

void	child_two(int f2, char *cmd2, t_info *info, char **envp)
{
	int	status;

	dup2(f2, STDOUT_FILENO);
	dup2(info->_pipe[0], STDIN_FILENO);
	close(info->_pipe[1]);
	close(f2);
	waitpid(info->p_id_c1, &status, 0);
	execve(cmd2, info->split2, envp);
	ft_error(-1);
}
