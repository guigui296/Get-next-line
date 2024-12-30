/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbehra <gbehra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 10:04:01 by gbehra            #+#    #+#             */
/*   Updated: 2024/12/30 11:02:57 by gbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int	main(void)
{
	int			fd;
	char		*line;
	int			i;
	int			line_count;
	const char	*files[] = {
		"test12lignes.txt",
		"test1ligne.txt",
		"testvide.txt",
		"testavecretour.txt",
		"test200carac.txt",
		"testspace+caracspe.txt",
		"testligne+emptyligne.txt",
		"testretourchariot.txt",
		"testr+n.txt",
		"testbigligne.txt",
		"test1000lignes.txt",
		NULL
	};

	i = 0;
	while (files[i] != NULL)
	{
		printf("Fichier: %s\n", files[i]);
		fd = open(files[i], O_RDONLY);
		if (fd < 0)
		{
			perror("Erreur d'ouverture fichier");
			i++;
			continue ;
		}
		line_count = 0;
		line = get_next_line(fd);
		while (line != NULL)
		{
			line_count++;
			free(line);
			line = get_next_line(fd);
		}
		if (line_count > 0)
			printf("Test OK\n");
		else
			printf("Test NOK\n");
		close(fd);
		i++;
		printf("\n");
	}
	return (0);
}
