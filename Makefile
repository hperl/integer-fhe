CC       = gcc
CFLAGS   = -Wall -Werror -g3 -ggdb -I/opt/local/include
LDFLAGS += -L/opt/local/lib -lgmp
SOURCE   = $(shell find * -name '*.c')
OBJECTS  = $(SOURCE:.c=.o)
.PHONY:    clean

all: integer-fhe

integer-fhe: $(OBJECTS)
	$(CC) -o integer-fhe $^ $(LDFLAGS)

clean:
	rm -f $(OBJECTS) integer-fhe

