##
## Makefile for  in /home/sauvau_m/rendu/PSU_2016_philo
##
## Made by Sauvau Mathieu
## Login   <mathieu.sauvau@epitech.eu>
##
## Started on  Mon Mar  6 10:11:36 2017 Sauvau Mathieu
## Last update Wed Mar 29 15:17:54 2017 Sauvau Mathieu
##

# USEFUL VARIABLES

RM      =	rm -rf

GREEN	=	\033[1;32m

WHITE	=	\033[0m

ECHO	=	echo -e

# SOURCES VARIABLES

SRC	=	$(wildcard src/*.c)

OBJS    =	$(SRC:.c=.o)


# PROJECT VARIABLES

NAME	=	lemipc

LIB	=	-lpthread

CFLAGS	=	-W -Wall -Wextra -Werror -g\
		-Iinclude/ \

CC	=	gcc $(CFLAGS) -g


# PROJECT RULES

$(NAME)	: 	$(OBJS)
			@$(CC) -o $(NAME) $(OBJS) $(LIB)

compile :       $(OBJS)
		@$(CC) -o $(NAME) $(OBJS) $(LIB)

all   	:
		@make -j 4 -s compile

clean	:
		@$(RM) $(OBJS)

fclean	: 	clean
		@$(RM) $(NAME)

re  	:	fclean all


.c.o	:
		@$(CC) -c $< -o $@
		@$(ECHO) "[$(GREEN)OK$(WHITE)] > $<\t \t "


.PHONY	:	all compile clean fclean re
