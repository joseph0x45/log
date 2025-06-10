CC = gcc
# CFLAGS = -g -Wall -Wextra -std=c17 -Werror -pedantic
CFLAGS = -std=c17 -O2 -Wall -Wextra -Wpedantic -fstack-protector-strong -D_FORTIFY_SOURCE=2 -fPIE
LDFLAGS = -pie -Wl,-z,relro,-z,now

PREFIX ?= /usr/local
BINDIR  = $(PREFIX)/bin

TARGET = log
SRC = main.c

.PHONY: all clean install uninstall

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o $(TARGET)

clean:
	rm -rf $(TARGET)

install: $(TARGET)
	install -Dm755 $(TARGET) $(DESTDIR)$(BINDIR)/$(TARGET)

uninstall:
	rm -rf $(DESTDIR)$(BINDIR)/$(TARGET)
