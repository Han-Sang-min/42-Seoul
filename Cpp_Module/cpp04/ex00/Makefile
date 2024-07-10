CXX = c++

CXXFLAGS = -pedantic -std=c++98 -Wall -Wextra -Werror -I .

TARGET = ex00

SRC =	main.cpp \
		Animal.cpp \
		Cat.cpp \
		Dog.cpp \
		WrongAnimal.cpp \
		WrongCat.cpp

OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

re : clean all

clean:
	rm -f $(OBJ) $(TARGET)