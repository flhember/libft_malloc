
NAME 	= libft_malloc_$(HOSTTYPE).so
CC 	= clang

CFLAGS 	+= -Wall
CFLAGS 	+= -Wextra
CFLAGS 	+= -Werror

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
LIB_PATH  = ./Libft/
INC_PATH  = ./includes/

SRC_FILES = $(LIBFT_MALLOC_FILES:%=%.c)
OBJ_FILES = $(SRC_FILES:.c=.o)

#------------------------------------------RULES--------------------------------#

LIB_FILES = libft_malloc.h
LIB = $(addprefix $(LIB_PATH), $(LIB_FILES))
LIB_HEADER = $(addprefix $(LIB_PATH), $(INC_PATH))

OBJ_FILES = $(SRC_FILES:.c=.o)
	OBJ_EXEC = $(addprefix $(OBJ_PATH), $(OBJ_FILES))

all: $(NAME)

$(OBJ_PATH):
	@mkdir $(OBJ_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) $(FLAGS) -c $< -o $@ -I $(INC_PATH) -I $(LIB_HEADER)
	@echo "\033[40mCompilation of \033[1m$(notdir $<)\033[0m \033[32mdone.\033[0m"

$(LIB):
	@make -C $(LIB_PATH)

$(NAME): $(LIB) $(OBJ_PATH) $(OBJ_EXEC)
	@cp libft/libft.a $(NAME)
	@ar rc $(NAME) $(OBJ_EXEC)
	@ranlib $(NAME)
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
