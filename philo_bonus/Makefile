SRC		=	main.c utils/ft_atoi.c utils/message.c utils/time.c utils/ft_itoa.c utils/ft_putstr_fd.c utils/ft_strjoin.c processes.c semaphores.c check_meals.c philo_routine.c watcher_routine.c
PROG	=	philo_bonus
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -pthread -g
HEADER	=	philo_bonus.h

.PHONY	:	all re clean fclean

all		:	$(PROG)

$(PROG)	:	$(HEADER) $(SRC)
			$(CC) $(CFLAGS) $(SRC) -o $(PROG)

clean	:
			rm -f $(PROG)

fclean	:	clean

re		:	fclean all
