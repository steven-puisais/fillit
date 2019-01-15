/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 11:42:12 by vrobin            #+#    #+#             */
/*   Updated: 2019/01/15 14:46:56 by vrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		check_spot(char **tab, char **tile, int x, int y, int size)
{
	int tile_x;
	int tile_y;
	int ok;

	tile_y = 0;
	ok = 0;
	while (tile_y < 4 && y + tile_y < size)
	{
		tile_x = 0;
		while (tile_x < 4 && x + tile_x < size)
		{
			if (tab[y + tile_y][x + tile_x] == '.'
					&& tile[tile_y][tile_x] != '.')
				ok++;
			tile_x++;
		}
		tile_y++;
	}
	if (ok == 4)
		return (1);
	return (0);
}

int		count_connections(char **tile, int x, int y)
{
	int count;

	count = 0;
	if (y - 1 != -1 && tile[y - 1][x] != '.')
		count++;
	if (y + 1 != 4 && tile[y + 1][x] != '.')
		count++;
	if (x - 1 != -1 && tile[y][x - 1] != '.')
		count++;
	if (x + 1 != 4 && tile[y][x + 1] != '.')
		count++;
	return (count);
}

int		get_connections(char **tile)
{
	int connections;
	int y;
	int x;

	connections = 0;
	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			if (tile[y][x] != '.')
				connections += count_connections(tile, x, y);
			x++;
		}
		y++;
	}
	if (connections == 6 || connections == 8)
		return (1);
	return (0);
}

int		is_valid(char *buffer, int buflen)
{
	int len;
	int i;
	int lnum;
	int blocs;

	i = 0;
	lnum = 1;
	blocs = 0;
	while (i < buflen)
	{
		len = 0;
		while (buffer[i] != '\n' && buffer[i] != '\0')
		{
			if (buffer[i++] == '#')
				blocs++;
			len++;
		}
		if ((lnum % 5 == 0 && len != 0) || (lnum % 5 == 0 && blocs != 4)
				|| (lnum % 5 != 0 && len != 4))
			return (-1);
		if (lnum++ % 5 == 0)
			blocs = 0;
		i++;
	}
	return ((lnum + 1) / 5);
}