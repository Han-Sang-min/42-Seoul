CXX = c++

CXXFLAGS = -pedantic -std=c++98 -I .

TARGET = ex03

SRC = 	main.cpp \
		AMateria.cpp \
		Ice.cpp \
		Cure.cpp \
		Character.cpp \
		MateriaSource.cpp
	
OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

re : clean all

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean re
