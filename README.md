# SNUCSE_CG
## Computer graphics Assignment 4

### How to compile

터미널 상에서 cd ./mathclass/mathclass/build 명령어를 입력하여 해당 폴더에 들어갑니다.

터미널 상에서 해당 폴더에서 cmake .. 명령어를 입력합니다.

터미널 상에서 해당 폴더에서 make ?j4 명령어를 입력합니다.

터미널 상에서 해당 폴더에서 cd ../../.. 명령어를 입력하여 압축 파일을 푼 기존 폴더로 되돌아갑니다.

터미널 상에서 해당 폴더에서 make 명령어를 입력하여 ./hw4 파일을 컴파일합니다.

터미널 상에서 해당 폴더에서 ./hw4 bolt3d.txt 명령어를 입력하여 프로그램을 실행합니다.

### What have I done

Translucent한 Cube의 여섯 면 각각에 다른 6개의 Material 을 표현하도록 했으며, opaque한 sweep surface와 겹치도록 만들었습니다.

Opaque한 Sweep surface 의 표면에도 vertexwise normal과 material을 적용하여 Gourard Shading 되도록 하였습니다.

Depth sorting algorithm을 BSP tree algorithm으로 구현했습니다.

Virtual trackball 을 적용하여 마우스, 방향키, 마우스 휠 키로 조종할 수 있도록 만들었습니다.

세 방향에 광원을 만들고 light coefficient들을 다르게 설정하였습니다.

임의의 standard format sweep surface data 를 넣으면, 올바른 방향으로 cross section 들이 연결된다는 가정 하에, opaque 물체를 rendering할 수 있으며 이 물체도 depth sorting 됩니다.

### What I haven't done

Depth sorting으로 만들어진 BSP tree를 rendering하면 translucent한 물체와 겹쳐질 때 올바르게 rendering되지 않습니다.

Complex translucent object를 구현하지 못했습니다.

### How I have implemented

Depth Ordering Algorithm

제 모델에는 BSP tree algorithm 을 이용하여 depth sorting 을 구현하였습니다. 그러나 구현에 문제가 있는 것인지 결과가 제대로 나오지 않았습니다. 

Mesh의 모든 polygon 들이 삼각형이라고 가정합니다. 모든 polygon 은 삼각형들로 분할할 수있기 때문에 이 가정은 임의의 polygon mesh에 대해 가능합니다. Root node 의 polygon 이 extend되어 만들어지는 평면과, 그 평면의 front에 위치하는지 back에 위치하는지 결정해야 하는 polygon 이 intersect 하는 경우 다음과 같은 경우의 수로 나뉠 수 있습니다. 평면과 polygon이 polygon들의 점들에 대해 : 

edge에서만 만나는 경우 : 이 경우 평면과 polygon은 polygon의 두 edge에서 만나게 됩니다. 각각의 edge에서 점을 찾아, 평면의 한 점으로부터 그 점 까지의 벡터와 평면의 법선벡터의 내적이 0이 되도록 합니다. 그 점은 평면과 edge가 만나는 점이 됩니다. Vector linear interpolation 으로 각각의 edge들에서 생성된 두 점의 위치와 normal 을 결정합니다. 
그 두 점을 이용해 삼각형 polygon 을 세 개의 삼각형 polygon 으로 분할합니다. 이제 나눠진 삼각형들은 평면의 front에 있는지 back에 있는지 결정할 수 있습니다. .

한 점에서 만나는 경우

나머지 두 점이 평면의 front에 위치하는 경우 : 해당 polygon은 평면의 front에 위치합니다.

나머지 두 점이 평면의 back 에 위치하는 경우 : 해당 polygon은 평면의 rear에 위치합니다.

한 점은 front에, 다른 점은 back 에 위치하는 경우 : 이 경우 평면과 polygon은 polygon의 한 점과 한 edge에서 만나게 됩니다. 그 edge에서 점을 찾아, 평면의 한 점으로부터 그 점 까지의 벡터와 평면의 법선벡터의 내적이 0이 되도록 합니다. 그 점은 평면과 그 edge가 만나는 점이 됩니다. Vector linear interpolation 으로 각각의 edge들에서 생성된 두 점의 위치와 normal 을 결정합니다. 그 두 점을 이용해 삼각형 polygon 을 두 개의 삼각형 polygon 으로 분할합니다. 이제 나눠진 삼각형들은 평면의 front에 있는지 back에 있는지 결정할 수 있습니다. .

두 점에서 만나는 경우

나머지 한 점이 평면의 front에 위치하는 경우 : 해당 polygon은 평면의 front에 위치합니다.

나머지 한 점이 평면의 back 에 위치하는 경우 : 해당 polygon은 평면의 back에 위치합니다.

세 점에서 만나는 경우 : 해당 polygon은 평면의 front에 위치합니다.

전혀 만나지 않는 경우 : 해당 polygon은 평면의 front에 있는지 back에 있는지 결정할 수 있습니다.

제 BSP tree 생성 알고리즘은 다음과 같습니다. Tree node 와 polygon list 가 주어졌을 때:
Polygon list 에서 polygon을 고릅니다. 해당 polygon의 normal을 구합니다.

선택된 polygon을 제외한 polygon list의 polygon들에 대해 다음을 반복합니다.

선택된 polygon 위의 한 점으로부터 현재 polygon들의 세 점들까지의 벡터와 선택된 polygon의 normal을 내적합니다.

세 내적값들로부터 현재 polygon과 선택된 polygon의 위치관계를 결정하고, 각각의 경우에 대해 현재 polygon이 앞에서 설명한 대로 선택된 polygon의 front에 있는지 back에 있는지 결정하고 list로 분류합니다.

Node의 face를 선택된 polygon으로 결정합니다.

Front로 분류된 polygon들의 list와 node의 right node 에 대해 재귀합니다. Polygon list가 empty라면 재귀하지 않습니다.

Back로 분류된 polygon들의 list와 node의 left node 에 대해 재귀합니다. Polygon list가 empty라면 재귀하지 않습니다.

제 BSP tree rendering 알고리즘은 다음과 같습니다. Tree node가 not null이면 :

Node의 face 위 한 점으로부터 카메라의 위치까지의 벡터와 Node의 face의 normal을 내적합니다.

만일 내적값이 음이 아닌 실수라면,

:e Node의 left node 에 대해 재귀적으로 rendering합니다.

현재 node의 face를 rendering합니다.

Node의 right node에 대해 재귀적으로 rendering합니다.

만일 내적값이 음수라면 

Node의 right node 에 대해 재귀적으로 rendering합니다.

현재 node의 face를 rendering합니다.

Node의 left node에 대해 재귀적으로 rendering합니다.

Material Properites of each surface

제 모델에는 Ruby, Gold, Silver, Bronze, Pearl, Jade, Plastic 총 일곱 가지 물질을 구현했습니다. 

Ruby : Ambient light 의 경우 어두운 붉은 색을 내도록 했습니다. 보석이기 때문에 붉은 색의 난반사율을 높여 조금이라도 비슷해보이게 만들었습니다. 보석이므로 shininess와 specular coefficient를 높였고, 붉은색을 약간 더 높였습니다.

Gold, Silver, bronze : 금속이므로 광택을 내기 위해 specular 과 shininess coefficient를 높였습니다. 금속 자체의 색은 어두우므로 ambient light coefficient는 낮게 정했습니다. Diffuse coefficient는 각 금속의 색깔에 높은 값을 정했습니다. 

모두를 같은 값으로 정했습니다.

Pearl : 분홍빛이 도는 흰색을 구현하기 위해 ambient 와 diffuse coefficient의 red 값을 높였습니다. Pearl 의 질감을 살리려면 specular 보다 diffuse coefficient가 높아야한다고 생각하여 diffuse coefficient 값을 매우 높였습니다.

Jade : 푸른 빛이 도는 초록색을 만들기 위해 ambient light coefficient에서 blue 쪽을 높였습니다. 

Plastic : 플라스틱의 경우 금속과 같은 광택을 일으키는 정반사가 어울리지 않아 specular light coefficient를 낮췄습니다. 그리고 질감이 난반사에 의해 나온다고 생각되어 diffuse coefficient 를 ambient coefficient보다 높였습니다.

Light Configuration

(10.0 , 0.0 , 0.0) , (0.0 , 10.0 , 0.0) , (0.0 , 0.0 , 10.0) 즉 x, y, z 축 각각의 10.0만큼 떨어진 위치에 점광원을 만들었습니다. 세 점광원 모두 Specular 한 빛의 세기는 RGB alpha 모두에 1.0f 값을 주었습니다. Specular 의 세기를 높여서 빛의 위치에 의한 효과를 보고 싶었습니다.

(0.0, 0.0, 10.0) 에 위치한 빛은 Ambient light 와 Diffuse light 의 세기가 0.2 로같으며 

(10.0, 0.0, 0.0) 에 위치한 빛은 Ambient light의 세기가 0.5 로 Diffuse light 의 세기 0.1보다 큽니다. Ambient light에 의한 효과를 볼 때 씁니다.

(0.0, 10.0, 0.0) 에 위치한 빛은 Diffuse light 의 세기가 0.5 로 Ambient light 의 세기 0.1 보다 큽니다. Diffuse light 에 의한 효과를 볼 때 씁니다.

프로그램 시작 시에는 세 점광원 모두 켜져있습니다.

숫자키 1을 누르면 z = 10.0에 위치한 빛을 켜고 끌 수 있습니다.

숫자키 2을 누르면 x = 10.0에 위치한 빛을 켜고 끌 수 있습니다.

숫자키 3을 누르면 y = 10.0에 위치한 빛을 켜고 끌 수 있습니다.
