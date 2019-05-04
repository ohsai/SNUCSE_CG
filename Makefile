all : hw3

clean :
	-rm hw3

hw3: hw3.cpp
	g++ -o hw3 parse.cpp trackball.cpp model.cpp hw3.cpp -I mathclass/mathclass/include -Lmathclass/mathclass/build -lmathclass -lm -lGL -lGLU -lglut -std=c++11
