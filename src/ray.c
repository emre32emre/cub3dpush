/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:56:55 by ayaman            #+#    #+#             */
/*   Updated: 2023/09/11 17:49:10 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_dda(t_game *game, t_calc *calc)
{
	if (calc->raydirx < 0)
	{
		calc->stepx = -1;
		calc->sidedistx = (game->ray.posx - calc->mapx) * calc->deltadistx;
	}
	else
	{
		calc->stepx = 1;
		calc->sidedistx = (calc->mapx + 1 - game->ray.posx) * calc->deltadistx;
	}
	if (calc->raydiry < 0)
	{
		calc->stepy = -1;
		calc->sidedisty = (game->ray.posy - calc->mapy) * calc->deltadisty;
	}
	else
	{
		calc->stepy = 1;
		calc->sidedisty = \
		(calc->mapy + 1.0 - game->ray.posy) * calc->deltadisty;
	}
}

void	perform_dda(t_game *game, t_calc *calc)
{
	while (calc->hit == 0)
	{
		if (calc->sidedistx < calc->sidedisty)
		{
			calc->sidedistx += calc->deltadistx;
			calc->mapx += calc->stepx;
			calc->side = 0;
		}
		else
		{
			calc->sidedisty += calc->deltadisty;
			calc->mapy += calc->stepy;
			calc->side = 1;
		}
		if (game->map[calc->mapy][calc->mapx] == '1')
			calc->hit = 1;
	}
	if (calc->side == 0)
		calc->perpwalldist = calc->sidedistx - calc->deltadistx;
	else
		calc->perpwalldist = calc->sidedisty - calc->deltadisty;
}

void	start_ray(int x, t_game *game, t_calc *calc)
{
	calc->camerax = (2 * x / (double)SCREEN_W) - 1;
	calc->raydirx = game->ray.dirx + game->ray.planex * calc->camerax;
	calc->raydiry = game->ray.diry + game->ray.planey * calc->camerax;
	calc->mapx = (int)game->ray.posx;
	calc->mapy = (int)game->ray.posy;
	calc->deltadistx = fabs(1 / calc->raydirx);
	calc->deltadisty = fabs(1 / calc->raydiry);
	calc->hit = 0;
}
