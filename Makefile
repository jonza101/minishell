# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/11 18:15:58 by zjeyne-l          #+#    #+#              #
#    Updated: 2020/04/15 20:37:30 by zjeyne-l         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c func.c split.c split_echo.c builtin.c env.c
SRC += gnl/libft/libft.a

INC = -I gnl/


all:
	gcc -g $(SRC) $(INC)