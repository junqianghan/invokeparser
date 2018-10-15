CXX = g++
CFLAGS = -g -std=c++11

INCLUDE = $(wildcard ./*.h)
SOURCES = $(wildcard ./*.cpp)

TARGET = mainApp

OBJECTS = $(patsubst %.cpp,%.o,$(SOURCES))

$(TARGET) : $(OBJECTS)
	$(CXX) $(CFLAGS) $^ -o $@ $(CLIBS)

$(OBJECTS) : %.o : %.cpp
	$(CXX) -c $(CFLAGS) $< -o $@

.PHONY : clean
clean:
	rm -rf *.o $(TARGET)