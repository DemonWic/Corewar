/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_errors.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loram <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 02:54:53 by loram             #+#    #+#             */
/*   Updated: 2021/01/14 02:54:54 by loram            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_ASM_ERRORS_H
# define ASM_ASM_ERRORS_H

# define ERR_PARSER_INIT		"ERROR: Couldn\'t initialize parser"
# define ERR_READ_FILE			"ERROR: Couldn\'t read file"
# define ERR_CREATE_FILE		"ERROR: Couldn\'t create file"
# define ERR_DATA_INIT			"ERROR: Couldn\'t initialize data"
# define ERR_CREATE_CHAMPION	"ERROR: Couldn\'t create champion file"
# define ERR_INVALID_FILE		"ERROR: Invalid file name"
# define ERR_NO_FILE			"ERROR: file not found"
# define ERR_NO_NAME			"ERROR: Couldn\'t create name file"
# define ERR_NO_HEADER			"ERROR: No name nor comment for champion"
# define ERR_NO_NAME_CH			"ERROR: No name for champion"
# define ERR_NO_COMMENT			"ERROR: No comment for champion"
# define ERR_NO_DATA_CH			"ERROR: No data for champion"
# define ERR_DATA_FORMAT		"ERROR: Invalid data format for champion"
# define ERR_DUP_NAME_CH		"ERROR: Duplicate name for champion"
# define ERR_DUP_COMMENT		"ERROR: Duplicate comment for champion"
# define ERR_NAME_CH			"ERROR: Invalid format for champion's name"
# define ERR_COMMENT			"ERROR: Invalid format for champion's comment"
# define ERR_LONG_NAME			"ERROR: Champion's name too long"
# define ERR_LONG_COMMENT		"ERROR: Champion's comment too long"
# define ERR_NO_DATA_CH			"ERROR: No data for champion"
# define ERR_INVALID_ARGUMENT	"ERROR: Invalid argument"

#endif
