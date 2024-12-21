/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifications_checker_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:03:29 by alvicina          #+#    #+#             */
/*   Updated: 2024/03/07 18:54:16 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static int	check_path(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	i = i - 1;
	while (str[i] == ' ')
		i--;
	if (str[i + 1] == ' ')
		str[i + 1] = 0;
	if (str[i] != 'm' || str[i - 1] != 'p' || str[i - 2] != 'x'
		|| str[i - 3] != '.')
		return (EXIT_FAILURE);
	if (open(str, O_RDONLY) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	find_texture_path_for_valid(char *str, t_data *data)
{
	is_white_space(&str);
	if (!ft_strncmp(str, "F", 1))
	{
		if (check_colors(str, &data->floor))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if ((!ft_strncmp(str, "C", 1)))
	{
		if (check_colors(str, &data->ceiling))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	while (*str != ' ')
		str++;
	if (!str)
		return (EXIT_FAILURE);
	is_white_space(&str);
	if (!str)
		return (EXIT_FAILURE);
	if (check_path(str))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	spec_valid_check(t_data *data)
{
	size_t	i;

	i = 0;
	while (data->textures[i])
	{
		if (find_texture_path_for_valid(data->textures[i], data))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

void	is_white_space(char **str)
{
	while (*str)
	{
		if (**str == ' ')
			(*str)++;
		else
			break ;
	}
}
