# SNUCSE_CG
## Computer graphics Assignment 5

## How to compile and execute

Ubuntu 16.04 LTS 환경입니다.

2. Freetype2 library를 설치합니다.  terminal에서 sudo apt-get install libfreetype6-dev 를 입력하여 (루트 권한을 가져야함) 설치합니다.

3. Cimg library 를 설치합니다. terminal에서 sudo apt-get install cimg-dev 를 입력하여 (루트 권한을 가져야함) 설치합니다.

4. terminal 상에서 압축을 푼 폴더에 들어간 후 make 를 입력하여 ./hw5라는 executable 이 생성되도록 합니다.

5. terminal 상의 해당 폴더에서 ./hw5 ./Glock.stl 를 입력하여 executable을 실행합니다. ./Glock.stl은 해당 geometry file을 import하겠다는 뜻입니다.

6. 실행이 끝나면 해당 폴더의 ./result.png 파일에 레이트레이싱 결과 이미지가 들어있습니다. Output image의 이름과 경로는 config.h 에서 원하는 이름과 경로로 바꿀 수 있습니다.


## What I have implemented

### Ray tracing spheres

구의 중심과 반지름을 잡고 중심으로부터 반지름만큼 떨어진 점들의 집합을 표면으로 삼았습니다. 표면 점들에서의 normal은 구의 중심으로부터 해당 점까지의 벡터로 정했습니다. 이 방법으로 sphere를 만들수 있었습니다. 그림에서도 볼 수 있듯 texture를 입힌 sphere과 물방울같은 refractive sphere이 phong illumination에 의해 제대로 ray tracing 되고 있는 것을 보실 수 있습니다.

### Ray tracing polygons

고차 polygon은 convex 성질까지 고려해야되서 삼각형 polygon만 구현했습니다. 세 점과 평면의 normal로부터 polygon을 결정할 수 있습니다. 그림에서도 볼 수 있듯 벽돌 texture를 입힌 벽과 회색 바닥, 정면과 측면에 있는 두 거울벽들이 전부 polygon으로 이루어 진 것들입니다. 중앙에 놓여있는 권총도 polygon의 집합입니다.

### Importing STL geometry files 

stl file을 import 하고 parsing 하여 polygon으로 그릴 수 있습니다. 그림에서도 볼 수 있듯 중앙에 놓인 권총 모형이 Glock.stl geometry 파일을 import하여 polygon들로 만들고 rendering 한 것입니다.

### Export image file as PNG

ray tracing 결과로 render된 이미지를 png format으로 저장할 수 있습니다. 설정을 바꾸어 이미지 저장 위치를 바꿀 수 있습니다.

### Texture mapped spheres and polygons

sphere 과 polygon 표면에 texture image를 mapping할 수 있습니다. 그림에서 볼 수 있듯 좌측 sphere은 세계지도 이미지를 texture 로 입힌 sphere이며 벽돌 벽은 벽돌 이미지를 texture로 입힌 polygon입니다. sphere는 xyz to uv mapping, polygon은 barycentric coordinate 를 이용하여 texture mapping을 구현했습니다.

### Phong illumination

ray가 표면과 만나면 phong illumination 을 통해 color 값을 output 합니다.  Texture image의 픽셀 rgb 값들은, texture를 입히지 않은 표면의 ambient coefficient, diffuse coefficient 값과 곱해져 해당 표면에 texture를 입힙니다. ray의 방향과 surface normal의 방향이 같은 경우 (즉 물체 안쪽에서 ray가 들어오는 경우) surface normal의 방향을 반대로 바꾸어 phong illumination을 실시합니다. 그림 상에서 sphere과 polygon의 빛의 diffuse illumination, 그림자, specular illumination 들을 관찰할 수 있습니다.

### Recursive reflection

ray와 표면이 만날 때 phong illumination을 끝내고, 표면의 reflective coefficient가 0이 아니라면ray를 반사하여 recursively trace할 지 결정합니다. 그림 상에서 정면과 오른쪽의 두 거울벽들을 통해 recursive reflection 을 관찰할 수 있습니다. 이로 인해 원래 두 구와 권총 모형 밖에 없지만 각 면에 반사되어 여덟개의 구와 네 개의 권총 모형이 놓여있는 것처럼 render되었습니다.

### Recursive refraction

ray와 표면이 만날 때 phong illumination을 끝내고, 표면의 refractive coefficient가 0이 아니라면ray를 표면 안쪽으로 굴절시켜 recursively trace할 지 결정합니다. 그림 상에서 빛이 굴절되는 물방울 모양의 구를 통해 recursive refraction을 관찰할 수 있습니다. 주위 물체에서 나온 ray가 구 내부에서 두 번 굴절되어 카메라에 도달하여, 왜곡된 상을 형성하는 것을 볼 수 있습니다.


## Settings

config.h 의 macro variable들의 값을 바꾸어 configuration 을 바꿀 수 있습니다. 바꾼 뒤엔 terminal 상에서 make를 다시 입력해야 configuration을 적용할 수 있습니다.

IMAGE_WIDTH : 결과 이미지의 width 값입니다.

IMAGE_HEIGHT : 결과 이미지의 height 값입니다.

PNG_EXPORT_PATH : 결과 이미지의 이름과 저장 경로입니다.

VERBOSE : 렌더링 진행 정도를 보여줄 지 말지 선택하는 bool값입니다.

WALL_TEXTURE_PATH : 벽 폴리곤의 텍스쳐 이미지 경로입니다.

SPHERE_TEXTURE_PATH : sphere의 텍스쳐 이미지 경로입니다.



