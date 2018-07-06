
NAME = compress

SOURCES = main.cpp \

SRCS = $(addprefix src/,$(SOURCES))

OBJ = $(SOURCES:.cpp=.o)

HEADERS = inc/compress.hpp \

CC = clang++

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ)
	@echo "\033[32mcompress\033[33m MAKED\033[0m"

$(OBJ): $(SRCS) $(HEADERS)
	$(CC) $(FLAGS) -c $(SRCS) -I $(HEADERS)

clean:
	rm -f $(OBJ)
	@echo "\033[33mCLEANED\033[0m"

fclean: clean
	rm -f $(NAME)
	@echo "\033[33mCLEANED ALL\033[0m"

re: fclean all

.PHONY: all clean fclean re