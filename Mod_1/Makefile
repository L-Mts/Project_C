CC=gcc
CCFLAGS= -W -Wall -Werror -g 

mod1 : list.o tree_etu.o main.o
		$(CC) -g list.o tree_etu.o main.o -o mod1

tree_etu.o : tree_etu.h tree_etu.c
		$(CC) -c  $(CCFLAGS) tree_etu.c

main.o : main.c tree_etu.h list.h
		$(CC) -c $(CCFLAGS) main.c
