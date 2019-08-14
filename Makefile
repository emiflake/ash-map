# **************************************************************************** #
#                                                                              #
#                                                              ::::::::        #
#    Makefile                                                :+:    :+:        #
#                                                           +:+                #
#    By: emiflake <marvin@student.codam.nl>                +#+                 #
#                                                         +#+                  #
#    Created: 2019/08/14 15:03:14 by emiflake            #+#    #+#            #
#    Updated: 2019/08/14 19:10:03 by emiflake            ########   odam.nl    #
#                                                                              #
# **************************************************************************** #

include colors.mk

PROJ_NAME=Ash-Map
NAME=libashmap.a

#=> Sources
OBJ_NAMES=	\
		ash_hashmap \
		ash_common \
		ash_bucket \
		ash_hasher \
		ash_iter \
		ash_clean \

#=> Tools
CC=clang
AR=ar
MKDIR=mkdir
RM=rm

#=> Flags
EXTRA=
CFLAGS=-Werror -Wextra -Wall $(EXTRA)

#=> Structure
OBJ_DIR=./.obj
MK_OBJ=$(MKDIR) -p $(OBJ_DIR)
OBJECTS=$(patsubst %, $(OBJ_DIR)/%.o, $(OBJ_NAMES))

INC_DIR=./inc
INCLUDES=$(wildcard $(INC_DIR)/*.h)

SRC_DIR=./src
SOURCES=$(wildcard $(SRC_DIR)/*.c)

#=> Rules
all:
	@echo "=> Building $(CBLUE)$(PROJ_NAME)$(CDEF)"
	@$(MAKE) $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES)
	@echo "$(TIME) $(CPLUS) $@"
	@$(MK_OBJ)
	@$(CC) -c -o $@ $(CFLAGS) -I$(INC_DIR) $<

$(NAME): $(OBJECTS) $(INCLUDES)
	@echo "$(TIME) $(CPLUS) $(NAME)"
	@$(AR) rcs $@ $(OBJECTS)

clean:
	@echo "$(TIME) $(CMINUS) $(OBJ_DIR)"
	@$(RM) -fr $(OBJ_DIR)

fclean: clean
	@echo "$(TIME) $(CMINUS) $(NAME)"
	@$(RM) -f $(NAME)

test: $(NAME)
	@echo "=> Testing $(CBLUE)$(PROJ_NAME)$(CDEF)"
	@$(CC) -o ./test_bin $(EXTRA) $(NAME) $(wildcard ./test/*.c)
	@echo "$(TIME) ./test_bin"
	@./test_bin


re:
	@$(MAKE) fclean
	@$(MAKE)
