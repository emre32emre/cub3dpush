/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:33:15 by ayaman            #+#    #+#             */
/*   Updated: 2023/09/11 19:16:13 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	exit_press(t_game *game)
{
	free_double_char(game->map);
	deinitialize(game);
	exit(EXIT_SUCCESS);
}

void	draw(t_game *game)
{
	int		x;
	int		y;

	y = -1;
	while (++y < SCREEN_H)
	{
		x = -1;
		while (++x < SCREEN_W)
			game->img.data[y * SCREEN_W + x] = game->buf[y][x];
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

void	raycast(t_game *game)
{
	int		x;
	t_calc	calc;

	x = 0;
	while (x < SCREEN_W)
	{
		start_ray(x, game, &calc);
		init_dda(game, &calc);
		perform_dda(game, &calc);
		init_wall_texture(game, &calc);
		input_wall_texture(x, game, &calc);
		x++;
	}
}

int	main_loop(t_game *game)
{
	raycast(game);
	draw(game);
	player_move(game);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	game.mlx = mlx_init();
	init_game(&game);
	check_arg(argc, argv, &game);
	init_map(&game);
	dup_map(&game);
	get_map_game(&game);
	game.win = mlx_new_window(game.mlx, SCREEN_W, SCREEN_H, "Cub3D");
	game.img.img = mlx_new_image(game.mlx, SCREEN_W, SCREEN_H);
	game.img.data = (int *)mlx_get_data_addr \
		(game.img.img, &game.img.bpp, &game.img.bpp, &game.img.bpp);
	mlx_hook(game.win, KEY_EVENT_PRESS, 0, &key_press, &game);
	mlx_hook(game.win, KEY_EVENT_RELEASE, 0, &key_release, &game);
	mlx_hook(game.win, KEY_EVENT_EXIT, 0, &exit_press, &game);
	mlx_loop_hook(game.mlx, &main_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
