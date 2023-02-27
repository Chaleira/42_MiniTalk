# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chales <chales@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/27 13:52:31 by chales            #+#    #+#              #
#    Updated: 2023/02/27 14:14:01 by chales           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER = server

CLIENT = client

LIBFT = libft/libft.a

SEREVR_SRC = server.c

CLIENT_SRC = client.c

CFLAGS =

RM = rm -fr

all : $(SERVER) $(CLIENT)

$(SERVER):		$(SEREVR_SRC)
				@make -s -C libft
				@gcc $(CFLAGS) $(SEREVR_SRC) $(LIBFT) -o $(SERVER)

$(CLIENT):		$(CLIENT_SRC)
				@make -s -C libft
				@gcc $(CFLAGS) $(CLIENT_SRC) $(LIBFT) -o $(CLIENT)

clean:			
				@make clean -s -C libft

fclean:			
				@make fclean -s -C libft
				@$(RM) $(SERVER) $(CLIENT)

re:				fclean $(SERVER) $(CLIENT)
				@make re -s -C libft