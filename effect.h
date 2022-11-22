#include "console.h"

#ifndef _EFFECT
#define _EFFECT

class effect
{
    float x_offset, y_offset;

    int width, height;

    char *buffer;
    bool init;

public:
    effect(int width, int height) { makeNull(); reset(width, height); }    
    ~effect() { cleanup(); }

    bool initalised() { return init; }
    void reset(int width, int height);

    void draw(console::console &destination);

    void next();
    
protected:
    void makeNull();
    void cleanup();
};

#endif