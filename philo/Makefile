NAME = philo

SRCS = ./src/philo.c \
       ./src/initialize.c \
       ./src/actions.c \
       ./src/threads.c \
       ./src/utils.c

OBJS = $(SRCS:./src/%.c=build/%.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./include
BUILD_DIR = build

all: $(NAME)

$(NAME): $(BUILD_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "✅ Build completed."

$(BUILD_DIR)/%.o: ./src/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	@rm -rf $(BUILD_DIR)
	@echo "🗑️  Object files removed."

fclean: clean
	@rm -f $(NAME)
	@echo "🗑️  Executable removed."

re: fclean all

.PHONY: all clean fclean re
