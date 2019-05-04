all : hw4

clean :
	-rm hw4

hw4 : hw4.cpp bsp.cpp model.cpp trackball.cpp parse.cpp 
	g++ -o hw4 parse.cpp trackball.cpp model.cpp hw4.cpp bsp.cpp -I mathclass/mathclass/include -Lmathclass/mathclass/build -lmathclass -lm -lGL -lGLU -lglut -std=c++11
