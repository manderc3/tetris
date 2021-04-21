CC = g++
CFLAGS = -Wall -std=c++17
TARGET = tetris

all: $(TARGET)

$(TARGET): 
	$(CC) $(TARGET).cpp $(CFLAGS) -o $(TARGET)

clean:
	$(RM) $(TARGET)
