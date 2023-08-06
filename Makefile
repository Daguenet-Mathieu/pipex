NAME = pipex

HEADER = pipex.h

SRCS =	main.c\
		error.c\
		ft_split.c\
		utils.c\
		utils_2.c\
		handle_arg.c\
		file.c\
		file_utils.c\
		exec.c\
		dup_close.c\
		error_utils.c\
		get_next_line.c

OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

CC = cc

FLAGS = -Wall -Werror -Wextra -g

$(NAME) : $(OBJS) $(HEADER)
		 $(CC) $(FLAGS) $(OBJS) -o $(NAME)

%.o: %.c
		$(CC) $(FLAGS) -MMD -c $< -o $@

all : $(NAME)

clean :
		rm -f $(OBJS) $(DEPS)

fclean : clean
		rm -f $(NAME) $(DEPS)

re : fclean all

-include : $(DEPS)

.PHONY: all clean fclean re