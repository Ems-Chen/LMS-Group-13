CC      = gcc
CFLAGS  = -std=c99 -Wall -Wextra -Wpedantic
TARGET  = library
SOURCES = main.c book.c issue.c storage.c report.c input.c
HEADERS = book.h issue.h storage.h report.h input.h

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

run: $(TARGET)
	mkdir -p data
	./$(TARGET)

clean:
	rm -f $(TARGET) $(TARGET).exe data/*.dat
