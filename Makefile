# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mschmit <mschmit@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/03/20 14:58:09 by mcassagn          #+#    #+#              #
#    Updated: 2015/06/01 11:07:09 by mschmit          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

SRC		=	srcs/

INCDIR 		=	includes/

SOURCE		=	$(SRC)main.c		\
				$(SRC)action.c		\
				$(SRC)hungry.c		\
				$(SRC)philo.c		\
				$(SRC)rootines.c	\
				$(SRC)sticks.c		\
				$(SRC)drop_stick.c	\
				$(SRC)display.c		\
				$(SRC)init_display.c\
				$(SRC)getndraw.c 	\
				$(SRC)startnend.c	\

OBJ		=	$(SOURCE:.c=.o)

LIBDIR 		=	libft/

LIB 		=	$(LIBDIR)libft.a

LIB_COMP 	=	-L ./$(LIBDIR) -lft

CC 		=	gcc

FLAG 		=	-I $(INCDIR) -g -lpthread -lncurses

RED = \033[33;31m
BLUE = \033[33;34m
GREEN = \033[33;32m
RESET = \033[0m

.PHONY: all re fclean

all: $(SERVER) $(NAME)

$(LIB):
		@$(MAKE) -C $(LIBDIR)

$(NAME): $(LIB) $(OBJ)
		@$(CC) -o $(NAME) $^ $(FLAG) $(LIB_COMP)
		@rm -f $(DEP).gch
		@echo "[$(GREEN)Compilation $(BLUE)$(NAME) $(GREEN)ok$(RESET)]"

%.o: %.c
		@$(CC) -c -o $@ $^ $(FLAG)

clean:
	@cd $(LIBDIR) && $(MAKE) $@
	@rm -f $(OBJ)
	@echo "[$(RED)Supression des .o de $(BLUE)$(NAME) $(GREEN)ok$(RESET)]"

fclean: clean
		@cd $(LIBDIR) && $(MAKE) $@
		@rm -f $(NAME)
		@echo "[$(RED)Supression de $(BLUE)$(NAME) $(GREEN)ok$(RESET)]"

re: fclean all
