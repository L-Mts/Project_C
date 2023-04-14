CC=gcc
CCFLAGS= -W -Wall -Werror -g 

mod2 : ../Mod_1/list.o tree_etu.o bloc.o main.o
		$(CC) -g ../Mod_1/list.o tree_etu.o bloc.o main.o -o mod2

tree_etu.o : ../Mod_1/tree_etu.h ../Mod_1/tree_etu.c
		$(CC) -c  $(CCFLAGS) ../Mod_1/tree_etu.c

bloc.o : bloc.h bloc.c
		$(CC) -c  $(CCFLAGS) bloc.c

main.o : main.c ../Mod_1/tree_etu.h ../Mod_1/list.h bloc.h
		$(CC) -c $(CCFLAGS) main.c
