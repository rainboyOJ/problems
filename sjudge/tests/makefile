CXX=gcc

SRC=$(wildcard *.c)
TARGET=$(patsubst %.c,%.out,$(SRC))

CPPSRC=$(wildcard *.cpp)
CPPTARGET=$(patsubst %.cpp,%.out,$(CPPSRC))

all: $(TARGET) $(CPPTARGET)
	@echo done

%.out : %.c
	gcc -g -o $@ $<

%.out : %.cpp
	g++ -g -o $@ $<

clean:
	rm -rf $(TARGET)
	rm -rf $(CPPTARGET)
	rm -rf *.out
	rm -rf *_out
	rm -rf *_err
	rm -rf *log.txt
