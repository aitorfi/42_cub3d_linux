/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afidalgo <afidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:35:35 by afidalgo          #+#    #+#             */
/*   Updated: 2024/03/12 18:53:16 by afidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static int	init_window(t_mlx *mlx);
static int	init_img(t_mlx *mlx);
static int	charge_textures(t_data *data);

int	init_gui(t_data *data)
{
	data->mlx = malloc(sizeof(t_mlx));
	if (data->mlx == NULL)
		return (EXIT_FAILURE);
	data->mlx->mlx_ptr = mlx_init();
	if (data->mlx->mlx_ptr == NULL)
	{
		free(data->mlx);
		return (EXIT_FAILURE);
	}
	if (init_window(data->mlx) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_img(data->mlx) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (charge_textures(data) == EXIT_FAILURE)
	{
		mlx_destroy_image(data->mlx->mlx_ptr, data->mlx->img_ptr);
		mlx_destroy_window(data->mlx->mlx_ptr, data->mlx->win_ptr);
		free(data->mlx->mlx_ptr);
		free(data->mlx);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	init_window(t_mlx *mlx)
{
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (mlx->win_ptr == NULL)
	{
		free(mlx->mlx_ptr);
		free(mlx);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	init_img(t_mlx *mlx)
{
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (mlx->img_ptr == NULL)
	{
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		free(mlx->mlx_ptr);
		free(mlx);
		return (EXIT_FAILURE);
	}
	mlx->img_data.pixels = mlx_get_data_addr(
			mlx->img_ptr,
			&mlx->img_data.bits_per_pixel,
			&mlx->img_data.line_len,
			&mlx->img_data.endian);
	return (EXIT_SUCCESS);
}

static int	charge_textures(t_data *data)
{
	size_t	i;
	int		x;

	x = 64;
	i = 0;
	init_textures(data);
	while (data->textures[i])
	{
		if (set_texture(data->textures[i], data))
		{
			check_free(data);
			return (EXIT_FAILURE);
		}
		i++;
	}
	if (get_addr(data, x))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	get_addr(t_data *data, int x)
{
	if (image_north(data, x))
		return (EXIT_FAILURE);
	if (image_south(data, x))
		return (EXIT_FAILURE);
	if (image_east(data, x))
		return (EXIT_FAILURE);
	if (image_west(data, x))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
