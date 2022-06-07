# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flhember <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/09 18:09:39 by flhember          #+#    #+#              #
#    Updated: 2022/06/07 15:43:10 by flhember         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = clang
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Werror
#-------------------------------------COLOR VARIABLE----------------------------#

red_li=$ \033[1;31m
red_da=$ \033[0;31m
grn_li=$ \033[1;32m
grn_da=$ \033[0;32m
yel=$ \033[1;33m
blu=$ \033[1;34m
mag=$ \033[1;35m
cyn=$ \033[1;36m
whi=$ \033[1;37m
end=$ \033[0m

#-------------------------------SRC/INC--------------------------------------------

LIBFT=  ft_strlen
INC = libft.h
SRC_FILES = $(LIBFT:%=%.c)

#-------------------------PATH/OBJ/DEP---------------------------------------------

SRC_PATH = ./srcs/
OBJ_PATH = ./obj/
INC_PATH = ./includes/

INC_FILES = $(addprefix $(INC_PATH), $(INC))
OBJ_FILES = $(patsubst %.c, $(OBJ_PATH)%.o, $(SRC_FILES))
DEPS=$(OBJ_FILES:%.o=%.d)

#---------------------------RULE----------------------------------------------------

.PHONY: all, clean, fclean, re

all: $(NAME)

$(OBJ_PATH):
	@mkdir $(OBJ_PATH)

$(OBJ_FILES): $(OBJ_PATH)%.o : $(SRC_PATH)%.c
	@$(CC) $(CFLAGS) -c -I $(INC_PATH) $< -o $@
	@echo "Compilation of $(whi)$(notdir $<)$(grn_da) done.$(end)"

$(NAME): $(INC_FILES) $(OBJ_PATH) $(OBJ_FILES)
	@ar rcs $(NAME) $(OBJ_FILES)
	@echo "$(grn_li)$(notdir $(NAME))$(grn_da) done.$(end)"

clean:
	@$(RM) -R $(OBJ_PATH) $(DEPS)
	@echo "$(red_li)Objects files of $(notdir $(NAME))$(red_da) removed.$(end)"

fclean: clean
	@$(RM) -R $(NAME)
	@echo "$(red_li)$(notdir $(NAME))$(red_da) removed.$(end)"

re: fclean
	@make all
