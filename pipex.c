/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luguilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 13:39:54 by luguilla          #+#    #+#             */
/*   Updated: 2022/06/23 16:59:56 by luguilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	openfiles(char *filename, int mode)
{
	if (mode == 0)
	{
		if (access(filename, F_OK) == -1)
		{
			write(2, "pipex: ", 7);
			write(2, filename, ft_strlen(filename));
			write(2, ": No such file or directory\n", 28);
			return (-1);
		}
		else if (access(filename, R_OK) == -1)
		{
			permission_denied(filename);
			return (-1);
		}
		return (open(filename, O_RDONLY));
	}
	else if ((access(filename, W_OK) == -1) && (access(filename, F_OK) == 0))
	{
		permission_denied(filename);
		return (-1);
	}
	else
		return (open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777));
	
}

char	*get_path(char *cmd, char **envp)
{
	int		i;
	char	*path;
	char	**dir;
	char	*line;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	path = envp[i] + 5;
	dir = ft_split(path, ':');
	i = 0;
	while (dir[i])
	{
		line = ft_strjoin(dir[i], cmd);
		if (access(line, F_OK) == 0)
		{
			free_tab(dir);
			return (line);
		}
		free(line);
		i++;
	}
	free_tab(dir);
	return (cmd);
}

void	child_two(int *fd, char *cmd, char **envp)
{
	char	**args;
	char	*path;

	args = ft_split(cmd, ' ');
	if (check_char(args[0], '/') == 1)
		path = args[0];
	else
		path = get_path(args[0], envp);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(fd[0]);
	execve(path, args, envp);
	free_tab(args);
	exit_all(cmd);
}

void	execute(char *cmd1, char *cmd2, char **envp)
{
	int		fd[2];
	int		pid;
	char	**args;
	char	*path;
	 
	args = ft_split(cmd1, ' ');
	if (check_char(args[0], '/') == 1)
		path = args[0];
	else
		path = get_path(args[0], envp);
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve(path, args, envp);
		exit_all(cmd1);
	}
	waitpid(pid, NULL, 0);
	free_tab(args);
	free(path);
	child_two(fd, cmd2, envp);
}

int	main(int argc, char **argv, char **envp)
{
	int	fdin;
	int	fdout;

	if (argc != 5)
	{
		write(1, "./pipex file1 cmd1 cmd2 file2", 29);
		return (1);
	}
	fdin = openfiles(argv[1], 0);
	if (fdin == -1)
		return (1);
	fdout = openfiles(argv[4], 1);
	if (fdout == -1)
		return (1);
	dup2(fdin, 0);
	dup2(fdout, 1);
	execute(argv[2], argv[3], envp);
	return (0);
}