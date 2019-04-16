CC := g++ 
CFLAGS := -g 
LFLAGS := -lpthread 
TARGET := main # name of the file where the main function in . 
SRCS := $(wildcard *.cpp)  
OBJS := $(SRCS:.cpp=.o)   # replace .cpp by .o



all:$(TARGET)  
%.o:%.cpp
	$(CC) $(CFLAGS) -c $< -o $@ $(LFLAGS)
$(TARGET):$(OBJS)  
	$(CC) $(CFLAGS) $(OBJS) -o $@  $(LFLAGS)


clean:  
	rm -rf $(TARGET) *.o  

test:
	echo $(SRCS)
	echo $(OBJS)
	echo $<
	echo $(CFLAGS)
