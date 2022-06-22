ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

#----------------------------------------VARIABLE-------------------------------#

NAME 	= libft_malloc_$(HOSTTYPE).so

CC 	= gcc

FLAGS	 = -fpic
#FLAGS 	+= -g3 
#FLAGS 	+=-fsanitize=address

FLAGS_LIB = -shared 

#-------------------------------------COLOR VARIABLE----------------------------#

red_li	= $ \033[1;31m
red_da	= $ \033[0;31m
grn_li	= $ \033[1;32m
grn_da	= $ \033[0;32m
yel	= $ \033[1;33m
blu	= $ \033[1;34m
mag	= $ \033[1;35m
cyn	= $ \033[1;36m
whi	= $ \033[1;37m
end	= $ \033[0m

#-----------------------------------------SRC/INC-------------------------------#

LIBFT_MALLOC_FILES 	= malloc free show_alloc_mem
LIBFT_MALLOC_INC_FILES 	= libft_malloc.h
TEST_FILE		= test.c

#--------------------------------------PATH/FILES-------------------------------#

SRC_PATH  = ./srcs/
OBJ_PATH  = ./obj/
INC_PATH  = ./includes/
LIB_PATH  = ./lib/

SRC_FILES = $(LIBFT_MALLOC_FILES:%=%.c)
OBJ_FILES = $(SRC_FILES:.c=.o)

INC = $(addprefix $(INC_PATH), $(LIBFT_MALLOC_INC_FILES))
OBJ = $(patsubst %.c, $(OBJ_PATH)%.o, $(SRC_FILES))

#------------------------------------------RULES--------------------------------#

all: $(NAME)

$(OBJ_PATH):
	@mkdir $(OBJ_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) $(FLAGS) -c -I $(INC_PATH) $< -o $@
	@echo "\033[40mCompilation of \033[1m$(notdir $<)\033[0m \033[32mdone.\033[0m"


$(NAME): $(OBJ_PATH) $(INC) $(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(FLAGS_LIB)
	@echo "\033[1;32m$(notdir $(NAME))\033[1;0m\033[32m created.\033[0m"
	@mkdir $(LIB_PATH)
	@ln -fs libft_malloc_x86_64_Linux.so libft_malloc.so
	@mv $(NAME) $(LIB_PATH)
	@mv libft_malloc.so $(LIB_PATH)
	export LD_LIBRARY_PATH=$(PWD)/lib
	@echo "\033[1;32mlibft_malloc.so\033[1;0m\033[32m linked.\033[0m"

test: $(TEST_FILE)
	export LD_LIBRARY_PATH=$(shell pwd)/lib
	gcc $(TEST_FILE) -o test -lft_malloc -I includes -L lib

clean:
	@/bin/rm -rf $(OBJ_PATH)
	@echo "\033[31mObjects files of \033[1;31m$(notdir $(NAME))\033[1;0m\033[31m removed.\033[0m"

fclean: clean
	@/bin/rm -rf $(NAME)
	@/bin/rm -rf $(LIB_PATH)
	@echo "\033[1;31m$(notdir $(NAME))\033[1;0m\033[31m removed.\033[0m"

re: fclean all

.PHONY: all, clean, fclean, re
