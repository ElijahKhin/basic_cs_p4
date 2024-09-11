NAME = RootFinder.a

PREREQUISITE_P4 = \
				  Makefile \
					RootFinder.h \
					../common/libft.h \
				  colors.h
#					../common/common.a 

SRC = RootFinder.cc

OBJ_FOLDER = obj
OBJ = $(SRC:%.cc=$(OBJ_FOLDER)/%.o)

CLR = g++
FLAGS = -std=c++17 -Werror -Wextra -Wall -I.

GREEN = \033[32m
YELLOW = \033[0;33m
RED = \033[0;31m
GRAY = \033[2;37m
CURSIVE = \033[3m
NO_COLOR = \x1b[0m
RESET = \033[0m


#all: tasks_lib $(NAME)
all: $(NAME)

$(NAME):  $(OBJ_FOLDER) $(OBJ)
	@ar rc $@ obj/*	
	@ranlib $(NAME)
	@echo "----------------------------------------------------------\n"
	@printf "$(CURSIVE)Assembling $(NAME) ⚙️ ... $(GREEN)DONE! 🥂$(RESET)"
	@echo "\n"

$(OBJ_FOLDER):
	@mkdir $(OBJ_FOLDER)

$(OBJ_FOLDER)/%.o: %.cc $(PREREQUISITE_P4)
	@$(CLR) -c $(FLAGS) $< -o $@

clean:
	@echo "$(RED)Cleaning $(NAME) objects..."
	@rm -rf obj
	@echo "$(GRAY)$(CURSIVE)---$(NAME) objects are cleaned!\n"
.PHONY: clean

fclean: clean
	@rm -rf *.a a.out .*.swp *.*.gch .DS_Store test_bin a.out.dSYM $(NAME)
	@echo "$(GRAY)$(CURSIVE)---$(NAME) staff is completely cleaned!\n"

.PHONY: fclean

re: fclean all
.PHONY: re
