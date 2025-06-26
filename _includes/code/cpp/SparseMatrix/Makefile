CXX = g++
CXXFLAGS = -std=c++11 -Wall -Iinclude

SRC = src/Triplet_MATRIX_H.cpp src/OrthogonalMatrix.cpp main.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = sparse_matrix_demo

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)