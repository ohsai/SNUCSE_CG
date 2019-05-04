## How to compile

### Environment : 

Ubuntu 16.04 LTS

gcc 5.4.0

Cmake 3.5.1

freeglut (version same as tutorial)

1. Download 2014-13485.tar.gz

2. Type

tar -xvzf 2014-13485.tar.gz 

in directory where nothing other than 2014-13485.tar.gz is placed.

3. Type 

cd ./mathclass/mathclass

mkdir build

cmake ..

make -j4

and let libmathclass.a be compiled.

4. Return to directory where 2014-13485.tar.gz is placed and type

make clean

make

then ./hw3 is compiled.

## What I have implemented

1. Parser which reads text file with standard format and loads control point data of cross sections and transformation data of cross sections.

2. Decide whether to draw closed curve cross section as B-spline or Catmull-Rom spline.

3. Read scaling factor, axis-angle, translation data and convert these to scalar, unit quaternion, 3d vector data and perform bezier spline interpolation to these for smooth transformation.

4. Decide points based on interpolated control point and transformation data processed above, and draw polygonal mesh based on these points. Polygonal mesh was drawn in wireframe.

5. Virtual trackball to rotate by mouse, translate by arrow keys, zoom in and out by mouse wheel is attached. Can see the whole scene by pressing enter key.

6.  Created bolt model by 113 cross sections of swept surfaces.

## How I have implemented

1. Parser was implemented in parse.h and parse.cpp. I used list type of standard c++11 to store data. I assumed standard format of text file is solid, so I extracted data by ifstream and >> operator sequentially.

2. In B-spline, I assumed cross section control points to be more than 4 points, since I was trying to use cubic B-spline. I copied three control points from the front and appended at the back, since it was closed curve I thought it was alright. In Catmull-Rom spline, I assumed cross section control points to be more than 2 points. I copied two control points from the front and appended at the back, and a control point from the back and appended at the front, since Catmull-Rom spline needs average difference of previous and next point to calculate tangent value of current point, and the last control point and first control point must also be interpolated to form a closed curve.  In both cases I used matrix multiplication to get closed curve points.

3. scale factor, axis-angle, translation data are each translated to m_real, quaternion, vector of math library. Using quaternion slerp and vector interpolation I used De casteljiau algorithm to implement bezier spline interpolation for the data.

4. I first decided closed curve points on xz plane using cross section control points. Then I transformed it according to transformation data. After that I drawed points using glvertex3f. I used triangle strip for drawing a mesh, so I needed previous closed curve points and current closed curve points to draw a part of surface.

5. I loaded the exact virtual trackball used in homework 2, but only changed lookat point, camera position and lookup vector at the start of the program, and when I pressed enter.(show all command)

6. I first drew upward spiral of circle for helix of bolt, and drew two cylinders for the top and body of the bolt.

## What I have not implemented

1. Polygonal mesh was drawn in wireframe, so we cannot visualize the model as solid or textured surface.

2. Implementation of vector, quaternion, m_real is from mathclass library, not mine.


## How to use it

Type in terminal

./hw3 (text file for swept surface)

to load text file and visualize swept surface model.


Type in terminal 

./hw3 bolt.txt

to see bolt model created by swept surface.

Press Enter to see the whole scene of the model. (show all)

Press right or left button and drag the mouse to rotate the model.

Roll the mouse wheel to zoom in or out the scene.

Press up or down arrow key to dolly in or out.


