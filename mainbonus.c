/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainbonus2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbehra <gbehra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 10:51:50 by gbehra            #+#    #+#             */
/*   Updated: 2024/12/30 10:57:54 by gbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

void	test_multiple_fds(const char *files[])
{
	int		fds[11];
	char	*lines[11];
	int		i;
	int		all_tests_passed;
	int		finished;

	i = 0;
	all_tests_passed = 1;
	while (files[i] != NULL && i < 11)
	{
		fds[i] = open(files[i], O_RDONLY);
		if (fds[i] < 0)
		{
			perror("Erreur d'ouverture fichier");
			all_tests_passed = 0;
		}
		else
		{
			lines[i] = get_next_line(fds[i]);
		}
		i++;
	}
	finished = 0;
	while (!finished)
	{
		finished = 1;
		i = 0;
		while (i < 11)
		{
			if (lines[i] != NULL)
			{
				free(lines[i]);
				lines[i] = get_next_line(fds[i]);
				finished = 0;
			}
			i++;
		}
	}
	if (all_tests_passed)
		printf("Test OK: Tous les fichiers ont été lus.\n");
	else
		printf("Test NOK: Un ou plusieurs fichiers sont en erreur.\n");
	i = 0;
	while (i < 11)
	{
		if (fds[i] >= 0)
			close(fds[i]);
		i++;
	}
}

int	main(void)
{
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

	test_multiple_fds(files);
	return (0);
}
