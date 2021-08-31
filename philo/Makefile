SRC		=	main.c threads.c mutex.c utils/ft_atoi.c watcher_routine.c philo_routine.c finish.c utils/time.c utils/ft_usleep.c utils/message.c utils/ft_putstr_fd.c utils/ft_itoa.c utils/ft_strjoin.c
PROG	=	philo
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -pthread -g
HEADER	=	philosophers.h

.PHONY	:	all re clean fclean

all		:	$(PROG)

$(PROG)	:	$(HEADER) $(SRC)
			$(CC) $(CFLAGS) $(SRC) -o $(PROG)

clean	:
			rm -f $(PROG)

fclean	:	clean

re		:	fclean all