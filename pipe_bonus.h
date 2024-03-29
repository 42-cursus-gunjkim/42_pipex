/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:40:35 by gunjkim           #+#    #+#             */
/*   Updated: 2023/02/27 20:04:44 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_BONUS_H
# define PIPE_BONUS_H

# include "./libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

typedef struct s_pipe
{
	int		fd[2];
	int		index;
	int		max_i;
	int		outfile_flag;
	int		is_heredoc;
	char	**argv;
	char	**path;
	char	**cmd_argv;
	char	**envp;
	char	*cmd_with_path;
	char	*infile;
	char	*outfile;
}	t_pipe;

char	**get_path(char *envp[]);
char	*cmd_with_path(t_pipe *pipex);
void	error_and_exit(const char *error_msg, int ecode);
void	error_free_exit(const char *error_msg, t_pipe *pipex, int ecode);
void	make_child(t_pipe *pipex);
void	free_pipex(t_pipe *pipex);
char	**pipex_split(char const *s, char c);
void	free_double_arr(char **arr);
void	here_doc(char *argv[], t_pipe *pipex);
int		strequal(char *str1, char *str2, int flag);
void	wait_all(int number_of_cmd);

#endif