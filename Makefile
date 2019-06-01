CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

Main: Main.o neural-network/NeuralNetwork.o math/Matrix.o math/Vector.o mnist/mnist.o
	$(CXX) $(CXXFLAGS) -o Main Main.o neural-network/NeuralNetwork.o math/Matrix.o math/Vector.o mnist/mnist.o

Main.o: Main.cpp neural-network/NeuralNetwork.hpp math/Matrix.h math/Vector.h mnist/mnist.h
	$(CXX) $(CXXFLAGS) -c Main.cpp

mnist/mnist.o: mnist/mnist.h

neural-network/NeuralNetwork.o: neural-network/NeuralNetwork.hpp math/Matrix.h math/Vector.h mnist/mnist.h

math/Matrix.o: math/Matrix.h math/Vector.h

math/Vector.o: math/Vector.h math/Matrix.h

