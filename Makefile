
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

Main: Main.o neural-network/NeuralNetwork.o math/Matrix.o math/Vector.o mnist/mnist.o stopwatch/stopwatch.o
	$(CXX) $(CXXFLAGS) -o Main Main.o neural-network/NeuralNetwork.o math/Matrix.o math/Vector.o mnist/mnist.o stopwatch/stopwatch.o

Main.o: Main.cpp neural-network/NeuralNetwork.hpp mnist/mnist.h stopwatch/stopwatch.h
	$(CXX) $(CXXFLAGS) -c Main.cpp

mnist/mnist.o: mnist/mnist.h

neural-network/NeuralNetwork.o: neural-network/NeuralNetwork.hpp math/LinearAlgebra.h

math/LinearAlgebra.h: math/Matrix.h math/Vector.h

math/Matrix.o: math/Matrix.h math/LinearAlgebra.h

math/Vector.o: math/Vector.h math/LinearAlgebra.h

stopwatch/stopwatch.o: stopwatch/stopwatch.h

