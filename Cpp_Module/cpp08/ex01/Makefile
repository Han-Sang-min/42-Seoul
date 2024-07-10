CXX = c++

CXXFLAGS = -std=c++98 -Wall -Wextra -Werror -I .

TARGET = ex01

SRC =	main.cpp \
		Span.cpp \

OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

re : clean all

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all re clean
