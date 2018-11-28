#include <iostream>
#include <graphics.h>
#include <winbgim.h>

struct point {
    int x,y;
};

struct segment {
    point a,b;
};

void drawLabel(char *text, point p, int colors=BLACK, int font=COMPLEX_FONT, int textSize=12)
{
    setcolor(colors);
    setbkcolor(getpixel(p.x, p.y));
    settextstyle(font,HORIZ_DIR,textSize);
    outtextxy(p.x, p.y, text);

}

void setBackgroundColor(int colors)
{
    setcolor(colors);
    rectangle(0,0,1280,720);
    setfillstyle(SOLID_FILL, colors);
    floodfill(1,1,colors);
}

int main()
{
    initwindow(1280,720);
    setBackgroundColor(BLUE);
    drawLabel("text frumos",{600,600}, RED, COMPLEX_FONT, 30);
    drawLabel("abc",{0,0}, MAGENTA, COMPLEX_FONT, 30);
    getch();
    closegraph();
}

