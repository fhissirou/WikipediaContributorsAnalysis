CC=g++
SRC= main.cpp load.cpp som.cpp
OBJ=$(SRC:.cpp=.o)
FLAGS=-Wall
LIBS= -lm -g -pthread
#LDFLAGS= -lSDL -lGL -lGLU 
EXEC= exec

$(EXEC):    $(OBJ) load.h som.h
	$(CC) -o $@ $(OBJ) $(LIBS)

%.o:	%.c
	$(CC) -c $<

clean:
	-rm *.o
	-rm $(EXEC)