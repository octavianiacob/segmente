#include <graphics.h>
#include <winbgim.h>

void drawText(char *text, int x, int y, int color=BLACK, int font=COMPLEX_FONT, int textSize=12)
{
    setcolor(color);
    setbkcolor(getpixel(x, y));
    settextstyle(font,HORIZ_DIR,textSize);
    outtextxy(x, y, text);

}

void setBackgroundColor(int color)
{
    setcolor(color);
    rectangle(0,0,960,540);
    setfillstyle(SOLID_FILL, color);
    floodfill(1,1,color);
}

void drawPoint(int x, int y, int radius=5, int color=WHITE)
{
    setcolor(color);
    circle(x,y,5);
    setfillstyle(SOLID_FILL, color);
    floodfill(x,y,color);
}

void drawSegment(int ax, int ay, int bx, int by, int thickness=1, int color=WHITE)
{
    setcolor(color);
    for(int i=1;i<=thickness;i++)
    {
        line(ax,ay,bx,by);
        line(ax+i-1,ay,bx+i-1,by);
        line(ax-i+1,ay,bx-i+1,by);
    }
}

void setupWindow()
{
    initwindow(960,540);
    setBackgroundColor(COLOR(25,53,73));
    drawText("Segment",280,0, COLOR(165,255,144), COMPLEX_FONT, 20);
    drawText("New Game",380,250, COLOR(255,198,19), COMPLEX_FONT, 16);
    rectangle(5,5,955,535);
    //TEST AREA
    drawPoint(30,30,5,RED);
    drawPoint(60,60,5,GREEN);
    drawSegment(30,30,60,60,2,YELLOW);

    getch();
    closegraph();
}

