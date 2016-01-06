# mekfile progetto reti
# Autor: Andrea Bachechi
CC = gcc
CFLAGS=-Wall
all:forza_client forza_server

forza_client:f4client.c mylib.h
	CC -o forza_client f4client.c 

forza_server:f4server.c serverlib.h
	CC -o forza_server f4server.c 
