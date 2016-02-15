CC=g++
CFLAGS=-O2 -c -Wall
LDFLAGS=-O2
MAIN_S=game_main.cpp
EXEC=game
EXEC_D=game_main.o 
OBJS=$(EXEC_D) 

$(EXEC): $(OBJS) 
	    $(CC) $(LDFLAGS) -o $(EXEC) $(OBJS)

game_main.o: game_main.cpp game_algorithms.hpp game_board.hpp game_piece.hpp
	    $(CC) $(CFLAGS) $(MAIN_S)

clean:
	    rm $(EXEC_D) $(EXEC)
