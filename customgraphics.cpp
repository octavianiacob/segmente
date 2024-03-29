#include <graphics.h>
#include <winbgim.h>
#include <iostream>
#include <math.h>
#include "algorithms.h"
#include "customgraphics.h"
#include <string.h>

Button buttons[10];
int dotRadius=5,nButtons;

char player1[20]="Player1";
char player2[20]="Player2";

void setBackgroundColor(int color)
{
    setfillstyle(SOLID_FILL, color);
    bar(0,0,getwindowwidth(),getwindowheight());
}

void drawGameArea()
{
    clearviewport();
    setfillstyle(SOLID_FILL,BLACK);
    bar(0,0,0.8*getwindowwidth(),getwindowheight());
}

void drawText(char *text, int x, int y, int color=BLACK, int textSize=12,int font=GOTHIC_FONT)
{
    setcolor(color);
    setbkcolor(getpixel(x+1, y+1));
    settextstyle(font,HORIZ_DIR,textSize);
    outtextxy(x, y, text);
}

void drawButton(int buttonIndex, int bgColor, int textSize,int font)
{
    Button button=buttons[buttonIndex];
    setfillstyle(SOLID_FILL, bgColor);
    bar(button.x1,button.y1,button.x2,button.y2);
    //std::cout<<button.name<<" ";
    drawText(button.name,button.x1,button.y1,WHITE,textSize,font);
    setcolor(WHITE);
    rectangle(button.x1,button.y1,button.x2,button.y2);
}

void changeButtonText(int buttonIndex, char *text)
{
    Button button = buttons[buttonIndex];
    strcpy(button.name,text);
}
void drawScoreboard(int mode, bool timer)
{
    setfillstyle(SOLID_FILL,RGB(250,250,250));
    if(mode==2 && timer==true)
        readimagefile("scoreboardpvp.bmp",738,0,getwindowwidth(),getwindowheight());
    if(mode==2 && timer==false)
        readimagefile("scoreboardpvpnotimer.bmp",738,0,getwindowwidth(),getwindowheight());
    if(mode==1 && timer==true)
        readimagefile("scoreboardpvc.bmp",738,0,getwindowwidth(),getwindowheight());
    if(mode==1 && timer==false)
        readimagefile("scoreboardpvcnotimer.bmp",738,0,getwindowwidth(),getwindowheight());
}

void drawMenu()
{
    readimagefile("bgnou.bmp",0,0,getwindowwidth(),getwindowheight());
    //drawText("SEGMENTE",titleX,titleY,WHITE,28);
    //rectangle(titleX,titleY,titleX+390,titleY+50);
    int buttonX1=410;
    int buttonY1=260;
    int buttonX2=557;
    int buttonY2=307;
    buttons[0]= {buttonX1,buttonY1,buttonX2,buttonY2};
    //drawButton(nButtons,RGB(3,36,80));
    nButtons++;
}

void drawOptions()
{
    readimagefile("optiuni.bmp",0,0,getwindowwidth(),getwindowheight());
    buttons[nButtons]= {420,437,540,481};
    //drawButton(nButtons,getpixel(1,1)); //nButton1
    nButtons++;

    readimagefile("1p.bmp",608,182,722,217);
    buttons[nButtons]= {608,182,722,217};
    //drawButton(nButtons,getpixel(1,1));
    nButtons++;

    readimagefile("no.bmp",608,242,722,277);
    buttons[nButtons]= {608,242,722,277};
    //drawButton(nButtons,getpixel(1,1));
    nButtons++;

    readimagefile("no.bmp",608,302,722,337);
    buttons[nButtons]= {608,302,722,337};
    //drawButton(nButtons,getpixel(1,1));
    nButtons++;

    readimagefile("no.bmp",608,362,722,397);
    buttons[nButtons]= {608,362,722,397};
    //drawButton(nButtons,getpixel(1,1));
    nButtons++;

}

void drawDot(Point p, int color)
{
    setcolor(color);
    setfillstyle(SOLID_FILL, color);
    fillellipse(p.x,p.y,dotRadius,dotRadius);
}

void drawSegment(Point a, Point b, int color,int thickness)
{
    setcolor(color);
    for(int i=1; i<=thickness; i++)
    {
        line(a.x,a.y,b.x,b.y);
        line(a.x+i-1,a.y,b.x+i-1,b.y);
        line(a.x-i+1,a.y,b.x-i+1,b.y);
    }
}

bool isInsideButton(int x,int y,int buttonIndex)
{
    Button button=buttons[buttonIndex];
    return x>=button.x1&&x<=button.x2&&y>=button.y1&&y<=button.y2;
}

bool isInsideDot(Point p,Point c)
{
    return sqrt((p.x-c.x)*(p.x-c.x)+(p.y-c.y)*(p.y-c.y))<=dotRadius;
}

void showNotice()
{
    buttons[nButtons]= {430,145,542,180};
    nButtons++;
    do
    {
        int x,y;
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN,x,y);
            if(isInsideButton(x,y,nButtons-1))
                return;
        }
    }
    while(true);
}

void updateTimer(int timer) {

    char timestr[20];
    itoa(timer,timestr,10);
    char pftime[10]="00:";
    if(timer<10)
        strcat(pftime,"0");
    strcat(pftime,timestr);
    drawText(pftime,800,470,WHITE,15);
}
