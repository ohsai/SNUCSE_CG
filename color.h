#ifndef COLOR_H
#define COLOR_H
class color{
    public:
        float rgb[3];
        color();
        color(float rgb[3]);
        color(const color &c2);
};
color operator& (const color& c1, const color& c2);
color operator+ (const color& c1, const color& c2);
color operator*(const float& f1, const color& c2);

#endif
