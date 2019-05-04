# SNUCSE_CG
## Computer graphics Assignment 1

### Assignment :

On OpenGL,

Create a hierarchical model using matrix stacks

The model should consists of three-dimensional primitives such as polygons, 

boxes, cylinders, spheres and quadrics.

The model should have a hierarchy of at least three levels

Animate the model to show the hierarchical structure

Eg) a car driving with rotating wheels

Eg) a runner with arms and legs swing

Make it aesthetically pleasing or technically illustrative

### How to compile :

g++ -o hierarchical_model hierarchical_model.cpp -lm -lGL -lGLU -lglut

### Theme : 

Thief and Cop

### Hierarchical Structure :

Thief

1.	Body

1.1.	Right Thigh

1.1.1.	Right Calf

1.1.1.1.	Right foot

1.2.	Left Thigh

1.2.1.	Left Calf

1.2.1.1.	Left foot

1.3.	Right upper arm

1.3.1.	Right lower arm

1.3.1.1.	Right hand

1.4.	Left upper arm

1.4.1.	Left lower arm

1.4.1.1.	Left hand

1.5.	Neck

1.5.1.	Head

Cop

2.	Body

2.1.	Right Thigh

2.1.1.	Right Calf

2.1.1.1.	Right foot

2.2.	Left Thigh

2.2.1.	Left Calf

2.2.1.1.	Left foot

2.3.	Right upper arm

2.3.1.	Right lower arm

2.3.1.1.	Right hand

2.4.	Left upper arm

2.4.1.	Left lower arm

2.4.1.1.	Left hand

2.4.1.1.1.	Truncheon (Rod)

2.5.	Neck

2.5.1.	Head

