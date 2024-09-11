NAME = project4

SRC = main.cc

CLR = g++
FLAGS = -std=c++17 -Werror -Wextra -Wall

GREEN = \033[32m
YELLOW = \033[0;33m
RED = \033[0;31m
GRAY = \033[2;37m
CURSIVE = \033[3m
NO_COLOR = \x1b[0m
RESET = \033[0m


all: common rootfinder $(NAME)

$(NAME): $(SRC)
	@$(CLR) $(FLAGS) $< -L. rootfinder/RootFinder.a common/common.a -o $@
	@echo "----------------------------------------------------------\n"
	@printf "$(CURSIVE)Assembling $(NAME) ⚙️ ... $(GREEN)DONE! 🥂$(RESET)"
	@echo "\n"

common:
	@make -C common/
.PHONY: common

rootfinder:
	@make -C rootfinder/
.PHONY: rootfinder

clean:
	@make clean -C common/
	@make clean -C rootfinder/
	@rm -rf obj
.PHONY: clean

fclean: clean
	@make fclean -C common/
	@make fclean -C rootfinder/
	@rm -rf *.a a.out .*.swp *.*.gch .DS_Store test_bin a.out.dSYM $(NAME)
	@echo "$(GRAY)$(CURSIVE)---$(NAME) staff is completely cleaned!\n"

.PHONY: fclean

re: fclean all
.PHONY: re
