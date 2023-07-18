/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_split_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:06:49 by gunjkim           #+#    #+#             */
/*   Updated: 2023/02/27 20:04:37 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_bonus.h"

int	is_white(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	else
		return (0);
}

static size_t	pipex_w_count(char const *s)
{
	int		flag;
	int		c_flag;
	size_t	wc;

	wc = 0;
	flag = 1;
	c_flag = 0;
	while (*s)
	{
		if (!is_white(*s) && flag == 1)
		{
			wc++;
			flag = 0;
			if (*s == '\'')
				c_flag = 1;
			else if (*s == '\"')
				c_flag = -1;
		}
		else if (is_white(*s) && c_flag == 0)
			flag = 1;
		else if ((*s == '\'' && c_flag == 1) || (*s == '\"' && c_flag == -1))
			c_flag = 0;
		s++;
	}
	return (wc);
}

static size_t	pipex_strlen(char const *s, char c)
{
	size_t	len;

	len = 0;
	if (is_white(c) == 1 && (*s != '\'') && (*s != '\"'))
	{
		while (!is_white(*s) && (*s != '\0'))
		{
			s++;
			len++;
		}
	}
	else if (*s == '\'' || *s == '\"')
	{
		if (*s == '\"')
			c = '\"';
		else
			c = '\'';
		s++;
		while (*s != c && *s != '\0')
		{
			s++;
			len++;
		}
	}
	return (len);
}

void	pipex_free_all(char **arr, size_t n)
{
	size_t	index;

	index = 0;
	while (index < n)
		free(arr[index++]);
	free(arr);
}

char	**pipex_split(char const *s, char c)
{
	size_t	wc;
	size_t	wl;
	size_t	index;
	char	**result;

	index = 0;
	wc = pipex_w_count(s);
	result = (char **)malloc(sizeof(char *) * (wc + 1));
	if (result == NULL)
		return (NULL);
	while (index < wc)
	{
		while (is_white(*s))
			s++;
		wl = pipex_strlen(s, c);
		result[index] = (char *)malloc(sizeof(char) * (wl + 1));
		if (result[index] == NULL)
			return (NULL);
		if (*s == '\'' || *s == '\"')
			s++;
		ft_strlcpy(result[index++], s, wl + 1);
		s = s + wl + 1;
	}
	result[index] = NULL;
	return (result);
}
