CXX = g++
CXXFLAGS = -Wall -g

Main: Main.o neural-network/NeuralNetwork.o matrix/Matrix.o
	$(CXX) $(CXXFLAGS) -o Main Main.o neural-network/NeuralNetwork.o matrix/Matrix.o

Main.o: Main.cpp neural-network/NeuralNetwork.hpp matrix/Matrix.hpp
	$(CXX) $(CXXFLAGS) -c Main.cpp

neural-network/NeuralNetwork.o: neural-network/NeuralNetwork.hpp

matrix/Matrix.o: matrix/Matrix.hpp

