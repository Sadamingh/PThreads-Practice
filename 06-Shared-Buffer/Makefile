NAME = Buffer
CC      = g++
CFLAGS := -Wall
ifneq ($(ARCH),Darwin)
  LDFLAGS += -lpthread
endif

all: $(NAME)

%: %.c
	$(CC) -o $< $(CFLAGS) $(LDFLAGS) $@

clean:
	rm -f $(NAME)