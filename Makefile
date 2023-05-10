CXX			= c++
NAME		= mst
SRCDIR		= srcs
OBJDIR		= objs
INCLUDES	= includes
SRCS		= $(wildcard $(SRCDIR)/*.cpp)
# OBJS		= $(SRCS:.cpp=.o)
OBJS = $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

CXXFLAGS	= -Wall -Wextra -Werror -std=c++17 -I$(INCLUDES)

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

# %.o : %.c

all: mkdir $(NAME)

mkdir:
	@mkdir -p $(SRCDIR) $(OBJDIR)

$(NAME):	$(OBJS)
	@$(CXX) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✅ Compiled!$(DEFAULT)"

clean:
	@rm -rf $(OBJDIR)
	@echo "$(RED)🧨 Objects are destroyed$(DEFAULT)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)🧨 Executable is destroyed$(DEFAULT)"

rmout:
	@rm -rf	out
	@echo "$(RED)🧨 out directory is destroyed$(DEFAULT)"

rmin:
	@rm -rf	in
	@echo "$(RED)🧨 in directory is destroyed$(DEFAULT)"

rmdir: rmin rmout

reset: fclean rmdir

re: fclean all

.PHONY: all clean fclean re rmout rmin rmdir reset

#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m