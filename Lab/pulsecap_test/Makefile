TARGET:=main
SRCS:=pwm_test.c
OBJS:=$(SRCS:.c=.o)
INCLUDE_DIRS:=..
CFLAGS:=$(foreach incdir, $(INCLUDE_DIRS), -I$(incdir)) -g -O
LZED:=-lzed

# default rule to build target
all: $(TARGET)


.PHONY: clean


$(TARGET): $(OBJS)
	$(CC) -g -o $@ $^ $(LZED) -lm

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf $(OBJS) $(TARGET)
