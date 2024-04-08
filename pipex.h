/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luguilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 14:02:44 by luguilla          #+#    #+#             */
/*   Updated: 2022/06/23 16:49:36 by luguilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

char	**ft_split(char const *s, char c);
int		check_char(char *str, char c);
void	execute(char *cmd1, char *cmd2, char **envp);
void	child_two(int *fd, char *cmd, char **envp);
int		openfiles(char *filename, int mode);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
void	exit_all(char *cmd);
int		ft_strlen(char *str);
void	free_tab(char **tab);
void	permission_denied(char *filename);

#endif
