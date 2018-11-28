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
    rectangle(0,0,1280,720);
    setfillstyle(SOLID_FILL, color);
    floodfill(1,1,color);
}

void setupWindow() {
    initwindow(1280,720);
    setBackgroundColor(0);
    drawText("text frumos",600,600, RED, COMPLEX_FONT, 30);
    drawText("abc",0,0, MAGENTA, COMPLEX_FONT, 30);
    getch();
    closegraph();
}
