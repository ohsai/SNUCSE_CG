CC = g++
CFLAGS = -std=c++11 -I /usr/include/freetype2
LDFLAGS = -O2 -L/usr/X11R6/lib -lm -lpthread -lX11 
PNGWRITER = -lPNGwriter -lz -lpng -lfreetype
#-L/home/shako/pngwriter/pngwriter -lPNGwriter -lz -lpng -lfreetype

all : hw5_201413485

clean :
	rm -f *.o hw5_201413485

color.o: color.cpp color.h
	$(CC) $(CFLAGS) -c color.cpp

vector.o: vector.cpp vector.h
	$(CC) $(CFLAGS) -c vector.cpp

surface.o: surface.cpp surface.h
	$(CC) $(CFLAGS) -c surface.cpp

texture.o: texture.cpp texture.h
	$(CC) $(CFLAGS) -c texture.cpp $(LDFLAGS)

phong.o: phong.cpp phong.h
	$(CC) $(CFLAGS) -c phong.cpp

ray.o: ray.cpp ray.h
	$(CC) $(CFLAGS) -c ray.cpp

light.o: light.cpp light.h
	$(CC) $(CFLAGS) -c light.cpp

polygon.o: polygon.cpp polygon.h
	$(CC) $(CFLAGS) -c polygon.cpp

sphere.o: sphere.cpp sphere.h
	$(CC) $(CFLAGS) -c sphere.cpp

ray_tracer.o: ray_tracer.cpp ray_tracer.h
	$(CC) $(CFLAGS) -c ray_tracer.cpp

scene.o: scene.cpp scene.h
	$(CC) $(CFLAGS) -c scene.cpp

window.o: window.cpp window.h
	$(CC) $(CFLAGS) -c window.cpp $(PNGWRITER)

camera.o: camera.cpp camera.h
	$(CC) $(CFLAGS) -c camera.cpp

stl.o : stl.cpp stl.h
	$(CC) $(CFLAGS) -c stl.cpp

hw5_201413485.o: hw5_201413485.cpp
	$(CC) $(CFLAGS) -c hw5_201413485.cpp

hw5_201413485: color.o vector.o phong.o ray.o surface.o light.o polygon.o sphere.o texture.o scene.o ray_tracer.o camera.o window.o stl.o hw5_201413485.o 
	$(CC) $(CFLAGS) color.o vector.o surface.o texture.o phong.o ray.o light.o polygon.o sphere.o ray_tracer.o scene.o camera.o window.o stl.o hw5_201413485.o -o hw5_201413485 $(LDFLAGS) $(PNGWRITER)
