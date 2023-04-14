# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/27 13:52:31 by chales            #+#    #+#              #
#    Updated: 2023/04/14 18:30:34 by plopes-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER = server
SERVER_BONUS = server_bonus

CLIENT = client
CLIENT_BONUS = client_bonus

LIBFT = libft/libft.a

SERVER_SRC = server.c
SERVER_BONUS_SRC = server_bonus.c
CLIENT_SRC = client.c
CLIENT_BONUS_SRC = client_bonus.c

SERVER_OBJ = server.o
SERVER_BONUS_OBJ = server_bonus.o
CLIENT_OBJ = client.o
CLIENT_BONUS_OBJ = client_bonus.o

CFLAGS = -Wall -Wextra -Werror

RM = rm -fr

all : $(SERVER) $(CLIENT) 

$(SERVER):			$(SERVER_OBJ)
					@make -s -C libft
					@cc $(CFLAGS) $(SERVER_OBJ) $(LIBFT) -o $(SERVER)

$(SERVER_BONUS):	$(SERVER_BONUS_OBJ)
					@make -s -C libft
					@cc $(CFLAGS) $(SERVER_BONUS_OBJ) $(LIBFT) -o $(SERVER_BONUS)

$(CLIENT):			$(CLIENT_OBJ)
					@make -s -C libft
					@cc $(CFLAGS) $(CLIENT_OBJ) $(LIBFT) -o $(CLIENT)

$(CLIENT_BONUS):	$(CLIENT_BONUS_OBJ)
					@make -s -C libft
					@cc $(CFLAGS) $(CLIENT_BONUS_OBJ) $(LIBFT) -o $(CLIENT_BONUS)

bonus:			$(SERVER_BONUS) $(CLIENT_BONUS)

clean:			
				@make clean -s -C libft
				@$(RM) $(SERVER_OBJ) $(CLIENT_OBJ) $(CLIENT_BONUS_OBJ) $(SERVER_BONUS_OBJ)

fclean:			clean
				@make fclean -s -C libft
				@$(RM) $(SERVER) $(CLIENT) $(SERVER_BONUS) $(CLIENT_BONUS)

re:				fclean $(SERVER) $(CLIENT)
				@make re -s -C libft