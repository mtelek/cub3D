/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 23:46:24 by mtelek            #+#    #+#             */
/*   Updated: 2024/11/13 02:05:17 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3D.h"

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
	int		isNeg;
	int		i;

	number = 0;
	i = 0;
	isNeg = 0;
	while (i <= (int)ft_strlen(str))
	{
		if (str[i] >= '0' && str[i] <= '9')
			number = str[i] - '0' + number * 10;
		else if (str[i] > '9' || (str[i] < '0' && i > 0))
			break ;
		else if (str[0] == '-' && i == 0)
			isNeg = 1;
		else if (str[0] == '+' && i == 0)
			;
		else
			break ;
		i++;
	}
	if (isNeg)
		number = 0 - number;
	return (number);
}

char *ft_strtok(char *str, char sepa)
{
    static char *stock = NULL;
    char *start;

    if (str != NULL)
        stock = str;
    if (stock == NULL)
        return NULL;
    while (*stock == sepa)
        stock++;
    if (*stock == '\0')
    {
        stock = NULL;
        return NULL;
    }
    start = stock;
    while (*stock != '\0' && *stock != sepa)
        stock++;
    if (*stock == sepa)
    {
        *stock = '\0';
        stock++;
    }
    return start;
}

char	*ft_strchr(const char *str, int c)
{
	while (*str != '\0')
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if ((char)c == '\0')
		return ((char *)str);
	return (NULL);
}

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n && (str1[i] != '\0' || str2[i] != '\0'))
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	return (0);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (0);
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

char	*ft_strdup(const char *s1)
{
	char	*s2;

	s2 = (char *)malloc(ft_strlen(s1) + 1);
	if (!s2)
		return (0);
	ft_memcpy(s2, s1, ft_strlen(s1) + 1);
	return (s2);
}
