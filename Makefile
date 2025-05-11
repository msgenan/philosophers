NAME = philo
SRCS = ./srcs/philo.c \
		./srcs/arg.c \

CC = cc
BUILD_DIR = build
CFLAGS = -Wall -Wextra -Werror
LIB_PATH = library
İNCLUDE = -I./library -I./srcs
LIB = $(LIB_PATH)/library.a
OBJS = $(SRCS:./src/%.c=$(BUILD_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(İNCLUDE) $(OBJS) -o $(NAME)
	@echo "✅ Build completed."

$(BUILD_DIR)/%.o: ./src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(LIB):
	@make -C $(LIB_PATH) > /dev/null 2>&1

clean:
	@rm -rf $(BUILD_DIR)
	@make clean -C $(LIB_PATH) > /dev/null 2>&1
	@echo "🗑️  Object files removed."

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIB_PATH) > /dev/null 2>&1
	@echo "🗑️  Executable removed."

re: fclean all

.PHONY: all clean fclean re