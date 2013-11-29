CC = g++
TEMPLATE_PATH = ../../../Template
INCLUDE_PATH += $(TEMPLATE_PATH)/include

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:%.cpp=%.o)

CFLAGS = $(foreach dir,$(INCLUDE_PATH),-I$(dir))
CFLAGS += -g
TARGET = radixSort

.PHONY:all
	all:$(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) -c $(SRCS)
	$(CC) $(OBJS) -o $(TARGET)

clean:
	rm -rf *.o
	rm -rf $(TARGET)

