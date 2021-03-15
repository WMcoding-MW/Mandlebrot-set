TARGET=mandlebrot
MODULES=mandlebrot.o ioutil.o
CPPFLAGS=$(shell Magick++-config --cppflags) -g -ansi -Wall -Wconversion
LDFLAGS=$(shell Magick++-config --ldflags) -g

$(TARGET): $(MODULES)
	g++ $(LDFLAGS) $(MODULES) -o $(TARGET)

mandlebrot.o: mandlebrot.cpp 
	g++ $(CPPFLAGS) -c mandlebrot.cpp 

clean:
	rm -f $(TARGET) $(MODULES)

all:
	clean $(TARGET)










