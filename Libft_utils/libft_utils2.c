/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:05:45 by mtelek            #+#    #+#             */
/*   Updated: 2024/11/21 16:27:30 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3D.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int		number;
	int		is_neg;
	int		i;

	number = 0;
	i = 0;
	is_neg = 0;
	while (i <= (int)ft_strlen(str))
	{
		if (str[i] >= '0' && str[i] <= '9')
			number = str[i] - '0' + number * 10;
		else if (str[i] > '9' || (str[i] < '0' && i > 0))
			break ;
		else if (str[0] == '-' && i == 0)
			is_neg = 1;
		else if (str[0] == '+' && i == 0)
			;
		else
			break ;
		i++;
	}
	if (is_neg)
		number = 0 - number;
	return (number);
}
