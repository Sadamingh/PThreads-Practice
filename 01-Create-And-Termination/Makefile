NAME = CAT
CC      = g++
CFLAGS := -Wall
ifneq ($(ARCH),Darwin)
  LDFLAGS += -lpthread
endif

all: $(NAME)

%: %.c
	$(CC) -o $< $(CFLAGS) $(LDFLAGS) $@