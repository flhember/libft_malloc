ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif


NAME 	= libft_malloc_$(HOSTTYPE).so

CC 	= gcc

FLAGS	 = -Wall -fpic

FLAGS_LIB = -shared -WL,-soname,$(NAME).1

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

LIBFT_MALLOC_FILES 	= malloc
LIBFT_MALLOC_INC_FILES 	= libft_malloc.h
LIB_BIN			= libft.a

#--------------------------------------PATH/FILES-------------------------------#

SRC_PATH  = ./srcs/
OBJ_PATH  = ./obj/
LIB_PATH  = ./libft/
INC_PATH  = ./includes/

SRC_FILES = $(LIBFT_MALLOC_FILES:%=%.c)
OBJ_FILES = $(SRC_FILES:.c=.o)

INC = $(addprefix $(INC_PATH), $(LIBFT_MALLOC_INC_FILES))
OBJ = $(patsubst %.c, $(OBJ_PATH)%.o, $(SRC_FILES))
LIB = $(addprefix $(LIB_PATH), $(LIB_BIN))
#------------------------------------------RULES--------------------------------#

all: $(NAME)


lib: $(LIB)

$(LIB):
	@make -C $(LIB_PATH)


$(OBJ_PATH):
	@mkdir $(OBJ_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) $(FLAGS) -c -I $(INC_PATH) -l $(LIB) $< -o $@
	@echo "\033[40mCompilation of \033[1m$(notdir $<)\033[0m \033[32mdone.\033[0m"


$(NAME): $(INC) $(LIB) $(OBJ_PATH) $(OBJ)
	#@$(CC) $(FLAGS_LIB) $(OBJ) $(LIB) -o $(NAME) -I $(INC_PATH) -lc
	@$(CC) -fpic $(OBJ) $(FLAGS_LIB) -o $(NAME)
	@echo "\033[1;32m$(notdir $(NAME))\033[1;0m\033[32m created.\033[0m"


clean:
	@/bin/rm -rf $(OBJ_PATH)
	@make clean -C $(LIB_PATH)
	@echo "\033[31mObjects files of \033[1;31m$(notdir $(NAME))\033[1;0m\033[31m removed.\033[0m"

fclean: clean
	@make fclean -C $(LIB_PATH)
	@/bin/rm -rf $(NAME)
	@echo "\033[1;31m$(notdir $(NAME))\033[1;0m\033[31m removed.\033[0m"

re: fclean all

.PHONY: all, clean, fclean, re
