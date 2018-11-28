#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#include "customgraphics.h"

struct point {
    int x,y;
};

struct segment {
    point a,b;
};


int main()
{
    setupWindow();
    return 0;
}

