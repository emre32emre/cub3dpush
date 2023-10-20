/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:14:08 by ayaman            #+#    #+#             */
/*   Updated: 2023/09/11 15:47:24 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static	void	setplane(t_game *game, char c)
{
	if (c == 'N')
	{
		game->ray.planex = 1;
		game->ray.planey = 0;
	}
	else if (c == 'S')
	{
		game->ray.planex = -1;
		game->ray.planey = 0;
	}
	else if (c == 'W')
	{
		game->ray.planex = 0;
		game->ray.planey = -1;
	}
	else if (c == 'E')
	{
		game->ray.planex = 0;
		game->ray.planey = 1;
	}
}

void	player_position(t_game *game, int i, int j)
{
	game->ray.posx = i + 0.5;
	game->ray.posy = j + 0.5;
	if (game->map[i][j] == 'N')
	{
		game->ray.dirx = 0;
		game->ray.diry = -1;
	}
	else if (game->map[i][j] == 'S')
	{
		game->ray.dirx = 0;
		game->ray.diry = 1;
	}
	else if (game->map[i][j] == 'W')
	{
		game->ray.dirx = -1;
		game->ray.diry = 0;
	}
	else if (game->map[i][j] == 'E')
	{
		game->ray.dirx = 1;
		game->ray.diry = 0;
	}
	setplane(game, game->map[i][j]);
}
