CC = gcc
CXX = gcc
CC_ARGS = -fpic -Wall
CXX_ARGS = -fpic
INCLUDE = 
#INCLUDE = -I ../json/include/ -I ../tclap-1.2.2/include/
LIBS = -lm
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c*))
HEADERS = $(wildcard *.h)

all: libxcg.so xcg

%.o: %.c $(HEADERS)
	$(CC) $(CC_ARGS) $(INCLUDE) -c $< -o $@

libxcg.so: $(OBJECTS)
	$(CXX) $(CXX_ARGS) $(INCLUDE) -shared -o $@ $(OBJECTS) $(LIBS)

xcg: libxcg.so
	$(CXX) $(CXX_ARGS) $(INCLUDE) -o $@ -L. -lxcg $(LIBS)

clean:
	rm xcg
	rm -f *.so
	rm -f *.o
	rm -f *.bak *~

remake: clean all