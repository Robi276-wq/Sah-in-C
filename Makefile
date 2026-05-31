CC = gcc
TARGET = joc_sah
SRC = main.c grafic.c reguli.c

$(TARGET): $(SRC)
	$(CC) -o $(TARGET).exe $(SRC)

clean:
	del $(TARGET).exe