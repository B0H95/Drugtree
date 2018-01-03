CC = gcc
RUBY = ruby
INCS = -I./
CCFLAGS = -Wall -Wextra -pedantic
FILES = $(shell find . -name "*.c")
LIBS = -lfcgi
NAME = build/drugtreebackend

all: compile

compile :
	$(RUBY) generate.rb
	$(CC) $(CCFLAGS) $(FILES) -o $(NAME) $(LIBS) $(INCS) 