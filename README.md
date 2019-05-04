# SNUCSE_CG
## Computer graphics Assignment 5

## How to compile and execute

Ubuntu 16.04 LTS ȯ���Դϴ�.

2. Freetype2 library�� ��ġ�մϴ�.  terminal���� sudo apt-get install libfreetype6-dev �� �Է��Ͽ� (��Ʈ ������ ��������) ��ġ�մϴ�.

3. Cimg library �� ��ġ�մϴ�. terminal���� sudo apt-get install cimg-dev �� �Է��Ͽ� (��Ʈ ������ ��������) ��ġ�մϴ�.

4. terminal �󿡼� ������ Ǭ ������ �� �� make �� �Է��Ͽ� ./hw5��� executable �� �����ǵ��� �մϴ�.

5. terminal ���� �ش� �������� ./hw5 ./Glock.stl �� �Է��Ͽ� executable�� �����մϴ�. ./Glock.stl�� �ش� geometry file�� import�ϰڴٴ� ���Դϴ�.

6. ������ ������ �ش� ������ ./result.png ���Ͽ� ����Ʈ���̽� ��� �̹����� ����ֽ��ϴ�. Output image�� �̸��� ��δ� config.h ���� ���ϴ� �̸��� ��η� �ٲ� �� �ֽ��ϴ�.


## What I have implemented

### Ray tracing spheres

���� �߽ɰ� �������� ��� �߽����κ��� ��������ŭ ������ ������ ������ ǥ������ ��ҽ��ϴ�. ǥ�� ���鿡���� normal�� ���� �߽����κ��� �ش� �������� ���ͷ� ���߽��ϴ�. �� ������� sphere�� ����� �־����ϴ�. �׸������� �� �� �ֵ� texture�� ���� sphere�� ����ﰰ�� refractive sphere�� phong illumination�� ���� ����� ray tracing �ǰ� �ִ� ���� ���� �� �ֽ��ϴ�.

### Ray tracing polygons

���� polygon�� convex �������� ����ؾߵǼ� �ﰢ�� polygon�� �����߽��ϴ�. �� ���� ����� normal�κ��� polygon�� ������ �� �ֽ��ϴ�. �׸������� �� �� �ֵ� ���� texture�� ���� ���� ȸ�� �ٴ�, ����� ���鿡 �ִ� �� �ſﺮ���� ���� polygon���� �̷�� �� �͵��Դϴ�. �߾ӿ� �����ִ� ���ѵ� polygon�� �����Դϴ�.

### Importing STL geometry files 

stl file�� import �ϰ� parsing �Ͽ� polygon���� �׸� �� �ֽ��ϴ�. �׸������� �� �� �ֵ� �߾ӿ� ���� ���� ������ Glock.stl geometry ������ import�Ͽ� polygon��� ����� rendering �� ���Դϴ�.

### Export image file as PNG

ray tracing ����� render�� �̹����� png format���� ������ �� �ֽ��ϴ�. ������ �ٲپ� �̹��� ���� ��ġ�� �ٲ� �� �ֽ��ϴ�.

### Texture mapped spheres and polygons

sphere �� polygon ǥ�鿡 texture image�� mapping�� �� �ֽ��ϴ�. �׸����� �� �� �ֵ� ���� sphere�� �������� �̹����� texture �� ���� sphere�̸� ���� ���� ���� �̹����� texture�� ���� polygon�Դϴ�. sphere�� xyz to uv mapping, polygon�� barycentric coordinate �� �̿��Ͽ� texture mapping�� �����߽��ϴ�.

### Phong illumination

ray�� ǥ��� ������ phong illumination �� ���� color ���� output �մϴ�.  Texture image�� �ȼ� rgb ������, texture�� ������ ���� ǥ���� ambient coefficient, diffuse coefficient ���� ������ �ش� ǥ�鿡 texture�� �����ϴ�. ray�� ����� surface normal�� ������ ���� ��� (�� ��ü ���ʿ��� ray�� ������ ���) surface normal�� ������ �ݴ�� �ٲپ� phong illumination�� �ǽ��մϴ�. �׸� �󿡼� sphere�� polygon�� ���� diffuse illumination, �׸���, specular illumination ���� ������ �� �ֽ��ϴ�.

### Recursive reflection

ray�� ǥ���� ���� �� phong illumination�� ������, ǥ���� reflective coefficient�� 0�� �ƴ϶��ray�� �ݻ��Ͽ� recursively trace�� �� �����մϴ�. �׸� �󿡼� ����� �������� �� �ſﺮ���� ���� recursive reflection �� ������ �� �ֽ��ϴ�. �̷� ���� ���� �� ���� ���� ���� �ۿ� ������ �� �鿡 �ݻ�Ǿ� �������� ���� �� ���� ���� ������ �����ִ� ��ó�� render�Ǿ����ϴ�.

### Recursive refraction

ray�� ǥ���� ���� �� phong illumination�� ������, ǥ���� refractive coefficient�� 0�� �ƴ϶��ray�� ǥ�� �������� �������� recursively trace�� �� �����մϴ�. �׸� �󿡼� ���� �����Ǵ� ����� ����� ���� ���� recursive refraction�� ������ �� �ֽ��ϴ�. ���� ��ü���� ���� ray�� �� ���ο��� �� �� �����Ǿ� ī�޶� �����Ͽ�, �ְ�� ���� �����ϴ� ���� �� �� �ֽ��ϴ�.


## Settings

config.h �� macro variable���� ���� �ٲپ� configuration �� �ٲ� �� �ֽ��ϴ�. �ٲ� �ڿ� terminal �󿡼� make�� �ٽ� �Է��ؾ� configuration�� ������ �� �ֽ��ϴ�.

IMAGE_WIDTH : ��� �̹����� width ���Դϴ�.

IMAGE_HEIGHT : ��� �̹����� height ���Դϴ�.

PNG_EXPORT_PATH : ��� �̹����� �̸��� ���� ����Դϴ�.

VERBOSE : ������ ���� ������ ������ �� ���� �����ϴ� bool���Դϴ�.

WALL_TEXTURE_PATH : �� �������� �ؽ��� �̹��� ����Դϴ�.

SPHERE_TEXTURE_PATH : sphere�� �ؽ��� �̹��� ����Դϴ�.



