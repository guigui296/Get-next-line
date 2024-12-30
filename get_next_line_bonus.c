/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbehra <gbehra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 01:37:25 by guigz             #+#    #+#             */
/*   Updated: 2024/12/30 11:14:00 by gbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*line_extractor(char *stash)
{
	char	*line;
	size_t	l;

	if (!*stash)
		return (NULL);
	l = 0;
	while (stash[l] && stash[l] != '\n')
		l++;
	if (stash[l] == '\n')
		l++;
	line = ft_substr(stash, 0, l);
	if (!line)
		return (NULL);
	stash = NULL;
	return (line);
}

static char	*join_line(char *line1, char *line2)
{
	char	*fline;

	if (!line1)
		line1 = ft_strdup("");
	fline = ft_strjoin(line1, line2);
	free(line1);
	free(line2);
	return (fline);
}

static void	update_stash(char *stash)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	j = 0;
	while (stash[i])
		stash[j++] = stash[i++];
	stash[j] = '\0';
}

static char	*extract_join_and_update(char *stash, char *line)
{
	line = join_line(line, line_extractor(stash));
	if (ft_strchr(stash, '\n'))
		update_stash(stash);
	else
		stash[0] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	stash[420][BUFFER_SIZE + 1];
	char		*line;
	int			readreturn;

	if (fd < 0 || fd >= 512 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	while (stash[fd][0] || !line || !ft_strchr(line, '\n'))
	{
		if (!stash[fd][0])
		{
			readreturn = read(fd, stash[fd], BUFFER_SIZE);
			if (readreturn <= 0)
			{
				if (readreturn == 0)
					return (line);
				return (free(line), NULL);
			}
			stash[fd][readreturn] = '\0';
		}
		line = extract_join_and_update(stash[fd], line);
		if (line && ft_strchr(line, '\n'))
			break ;
	}
	return (line);
}
