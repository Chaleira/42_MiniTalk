# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/27 13:52:31 by chales            #+#    #+#              #
#    Updated: 2023/03/08 15:57:26 by plopes-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER = server

CLIENT = client

LIBFT = libft/libft.a

SERVER_SRC = server.c
CLIENT_SRC = client.c

SERVER_OBJ = server.o
CLIENT_OBJ = client.o

CFLAGS = -Wall -Wextra -Werror

RM = rm -fr

all : $(SERVER) $(CLIENT) 

$(SERVER):		$(SERVER_OBJ)
				@make -s -C libft
				@cc $(CFLAGS) $(SERVER_OBJ) $(LIBFT) -o $(SERVER)

$(CLIENT):		$(CLIENT_OBJ)
				@make -s -C libft
				@cc $(CFLAGS) $(CLIENT_OBJ) $(LIBFT) -o $(CLIENT)

clean:			
				@make clean -s -C libft
				@$(RM) $(SERVER_OBJ) $(CLIENT_OBJ)

fclean:			clean
				@make fclean -s -C libft
				@$(RM) $(SERVER) $(CLIENT)

re:				fclean $(SERVER) $(CLIENT)
				@make re -s -C libft