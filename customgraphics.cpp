#include <graphics.h>
#include <winbgim.h>
#include <iostream>
#include <math.h>
#include "algorithms.h"
#include "customgraphics.h"

Button buttons[10];
int dotRadius=5,nButtons;

void setBackgroundColor(int color)
{
    setfillstyle(SOLID_FILL, color);
    bar(0,0,getwindowwidth(),getwindowheight());
}

void drawGameArea() {
    setfillstyle(SOLID_FILL,BLACK);
    bar(0,0,0.8*getwindowwidth(),getwindowheight());
}

void drawText(char *text, int x, int y, int color=BLACK, int textSize=12,int font=COMPLEX_FONT)
{
    setcolor(color);
    setbkcolor(getpixel(x, y));
    settextstyle(font,HORIZ_DIR,textSize);
    outtextxy(x, y, text);
}

void drawButton(char *text, int x1, int y1, int bgColor=RED, int textSize=16,int font=COMPLEX_FONT) {
    int x2=x1+1.7*textSize*strlen(text);
    int y2=y1+2.7*textSize;
    setfillstyle(SOLID_FILL, bgColor);
    bar(x1,y1,x2,y2);
    drawText(text,x1,y1,WHITE,textSize,font);
    buttons[nButtons++]={x1,y1,x2,y2,text};
}

void drawMenu() {
    setBackgroundColor(MAGENTA);
    int titleX=getwindowwidth()/2-200;
    int titleY=getwindowheight()/2-120;
    drawText("SEGMENTE",titleX,titleY,WHITE,30);
    int buttonX=getwindowwidth()/2-80;
    int buttonY=getwindowheight()/2;
    drawButton("Start",buttonX,buttonY,BLUE);
}

void drawDot(Point p, int color)
{
    setfillstyle(SOLID_FILL, color);
    fillellipse(p.x,p.y,dotRadius,dotRadius);
}

void drawSegment(Point a, Point b, int thickness, int color)
{
    setcolor(color);
    for(int i=1;i<=thickness;i++)
    {
        line(a.x,a.y,b.x,b.y);
        line(a.x+i-1,a.y,b.x+i-1,b.y);
        line(a.x-i+1,a.y,b.x-i+1,b.y);
    }
}

bool isInsideButton(int x,int y,int buttonIndex) {
    Button button=buttons[buttonIndex];
    std::cout<<buttons[0].x1<<" "<<buttons[0].y1<<" "<<buttons[0].x2<<" "<<buttons[0].y2<<'\n';
    return x>=button.x1&&x<=button.x2&&y>=button.y1&&y<=button.y2;
}

bool isInsideDot(Point p,Point c) {
    return sqrt((p.x-c.x)*(p.x-c.x)+(p.y-c.y)*(p.y-c.y))<=dotRadius;
}
