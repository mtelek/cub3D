/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 00:20:44 by mtelek            #+#    #+#             */
/*   Updated: 2024/10/16 23:08:34 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MESSAGES_H
# define ERROR_MESSAGES_H

//CHECKS
# define ERR_NO_MAP "Error, no map given\n"
# define ERR_TOO_MANY_ARGS "Error, too many arguments\n"
# define ERR_TEXTURE_MISSING "Error, texture is missing\n"

//MALLOC
# define ERR_MAIN_STRUCT "Error, malloc for creating main struct failed\n"
# define ERR_MF_CONTENT "Error, malloc for creating content failed\n"
# define ERR_MF_STRDUP "Error, malloc for duplicating string failed\n"
# define ERR_MF_TEXTURES "Error, malloc for creating textures struct failed\n"
# define ERR_MF_MAP "Error: Memory allocation for the map failed.\n"
# define ERR_MF_MAP_LINE "Error: Memory allocation for map line failed.\n"

//PERROR
# define ERR_OPEN_FILE "Error opening file"
# define ERR_CLOSE_FILE "Error closing file"

#endif
