# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skroboth <skroboth@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/28 15:47:51 by skroboth          #+#    #+#              #
#    Updated: 2026/01/19 19:50:39 by skroboth         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.cpp 

OBJ_DIR = obj

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.cpp=.o))

DEPS = $(OBJ:.o=.d)

NAME = ex03

CXX = c++
CXXFLAGS = -Wall -Werror -Wextra -std=c++98 -MMD -MP #-pedantic -fsanitize=undefined

RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(OBJ) -o $(NAME) $(CXXFLAGS)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re