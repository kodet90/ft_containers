NAME = containers

CC = c++

FLAGS = -std=c++98 -Wall -Wextra -Werror

RM = rm -f

all: $(NAME) std_$(NAME)
	./$(NAME) > output
	./std_$(NAME) > std_output
	diff output std_output

main.o: main.cpp Makefile vector.hpp map.hpp stack.hpp set.hpp input_iterator.hpp iterator.hpp iterator_traits.hpp tree_iterator.hpp RBtree.hpp reverse_iterator.hpp type_traits.hpp
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): main.o
	$(CC) -o $@ $^

std_main.o: main.cpp Makefile input_iterator.hpp
	$(CC) $(FLAGS) -c $< -o $@ -D STD=1

std_$(NAME): std_main.o
	$(CC) -o $@ $^ -D STD=1

intra: intra_$(NAME) intra_std_$(NAME)
	./intra_$(NAME) 0 > intra_output
	./intra_std_$(NAME) 0 > intra_std_output
	diff intra_output intra_std_output

intra_main.o: intra_main.cpp Makefile
	$(CC) $(FLAGS) -c $< -o $@

intra_$(NAME): intra_main.o
	$(CC) -o $@ $^

intra_std_main.o: intra_main.cpp Makefile
	$(CC) $(FLAGS) -c $< -o $@ -D STD=1

intra_std_$(NAME): intra_std_main.o
	$(CC) -o $@ $^

clean:
	$(RM) main.o std_main.o intra_main.o intra_std_main.o

fclean: clean
	$(RM) $(NAME) output std_$(NAME) std_output intra_$(NAME) intra_output intra_std_$(NAME) intra_std_output

re: fclean all

.PHONY: all intra clean fclean re
