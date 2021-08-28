#ifndef MY_COMMON_H
#define MY_COMMON_H

struct Vec2
{
    float x, y;
    Vec2() = default;
    Vec2(float x, float y)
        :x(x), y(y)
    {}
};

#endif
