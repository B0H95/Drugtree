CC = gcc
RUBY = ruby
INCS = -I./
LIBDIRS = -L/usr/lib64/mysql
CCFLAGS = -Wall -Wextra -pedantic -std=c11
FILES = $(shell find . -name "*.c")
LIBS = -lfcgi -lmysqlclient
NAME = build/drugtreebackend

all: compile

compile :
	$(RUBY) generate.rb
	$(CC) $(CCFLAGS) $(FILES) -o $(NAME) $(LIBS) $(LIBDIRS) $(INCS) 