/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 00:20:44 by mtelek            #+#    #+#             */
/*   Updated: 2024/11/21 16:25:48 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MESSAGES_H
# define ERROR_MESSAGES_H

// CHECKS
# define ERR_NO_MAP "Error: no map given\n"
# define ERR_TOO_MANY_ARGS "Error: too many arguments\n"
# define ERR_TEXTURE_MISSING "Error: texture is missing\n"
# define ERR_WRONG_F_TYPE "Error: wrong file type given\n"

// MALLOC
# define ERR_MAIN_STRUCT "Error, malloc for creating main struct failed\n"
# define ERR_MF_CONTENT "Error, malloc for creating content failed\n"
# define ERR_MF_STRDUP "Error, malloc for duplicating string failed\n"
# define ERR_MF_TEXTURES "Error, malloc for creating textures struct failed\n"
# define ERR_MF_MAP "Error: malloc for the map failed.\n"
# define ERR_MF_MAP_LINE "Error: malloc for map line failed.\n"
# define ERR_MF_MAPX "Error: malloc for variable mapX failed\n"
# define ERR_MF_DATA "Error: malloc for creating data struct failed\n"
# define ERR_MF_MAP_S "Error: malloc for creeating map struct failed\n"
# define ERR_MF_TEX "Error: malloc for creating textures failed\n"
# define ERR_MF_PLAYER_D "Error: malloc for creating player data failed\n"
# define ERR_MF_D_RAY "Error: malloc for creating d_ray failed\n"
# define ERR_MF_TEMP_TEXT "Error: malloc for creating temp_text failed\n"

// PERROR
# define ERR_OPEN_FILE "Error opening file"
# define ERR_CLOSE_FILE "Error closing file"

// MLX
# define ERR_DISPLAY "Failed to open X display\n"
# define ERR_INIT_MLX "Error initializing MLX\n"
# define ERR_WINDOW "Error creating window\n"
# define ERR_FRAME_BUFF "Framebuffer error, using 800x800.\n"
# define ERR_NO_RES "Could not read resolution. Falling back to 800x800\n"
# define ERR_NO_IMG "Error: failed to create image\n"
# define ERR_NO_IMG_DATA_ADDRESS "Error: Failed to get image data address\n"
# define ERR_MLX_HOOK_F "Error: one of mlx hooks has failed\n"
# define ERR_LOOP_HOOK "Error: Failed to register loop hook.\n"
# define ERR_NO_MLX_WIN_PTR "Error: mlx_put_image_to_window failed\n."
# define ERR_IMG_CREATE_F "Error: creating image  failed\n"
# define ERR_NO_MLX_PTR "Error: mlx_ptr missing, mlx_loop failed\n."

// MAP
# define ERR_INV_MAP "Error: invalid map\n"

// TEXTURES
# define ERR_INV_RGB "Invalid RGB values\n"
# define ERR_LOAD_TEX "Error loading textures\n"
# define ERR_NO_TEX_DATA "Error: creating data for textures failed\n"

#endif
