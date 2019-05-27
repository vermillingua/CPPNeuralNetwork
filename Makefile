CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

Main: Main.o neural-network/NeuralNetwork.o math/Matrix.o math/Vector.o
	$(CXX) $(CXXFLAGS) -o Main Main.o neural-network/NeuralNetwork.o math/Matrix.o math/Vector.o

Main.o: Main.cpp neural-network/NeuralNetwork.hpp math/Matrix.h math/Vector.h
	$(CXX) $(CXXFLAGS) -c Main.cpp

neural-network/NeuralNetwork.o: neural-network/NeuralNetwork.hpp

math/Matrix.o: math/Matrix.h

math/Vector.o: math/Vector.h math/Matrix.h

