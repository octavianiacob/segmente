#include <graphics.h>
#include <winbgim.h>
#include <iostream>
#include <math.h>
#include "algorithms.h"
#include "customgraphics.h"

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
    drawText(button.name,button.x1,button.y1,WHITE,textSize,font);
    setcolor(WHITE);
    rectangle(button.x1,button.y1,button.x2,button.y2);
}

void changeButtonText(int buttonIndex, char text[20])
{
    Button
    button = buttons[buttonIndex];
    button.name=text;
    drawButton(buttonIndex,getpixel(1,1));
}

void drawScoreboard()
{
    setfillstyle(SOLID_FILL,RGB(250,250,250));
    bar(0.8*getwindowwidth(),0,getwindowwidth(),getwindowheight());
    int exitX=getwindowwidth()-140;
    int exitY=getwindowheight()-70;
    int scoreX=exitX-10;
    int scoreY=exitY-450;
    int player1X=scoreX-20;
    int player1Y=scoreY+150;
    int player2X=scoreX-20;
    int player2Y=scoreY+300;
    //drawButton("Exit",exitX,exitY,BLUE,15,COMPLEX_FONT); //nButton 11
    drawText("Score",scoreX,scoreY,BLACK,15);
    drawText(player1,player1X,player1Y,BLUE,15);
    drawText(player2,player2X,player2Y,GREEN,15);
}

void drawMenu()
{
    readimagefile("bg.bmp",0,0,getwindowwidth(),getwindowheight());
    int titleX=getwindowwidth()/2-200;
    int titleY=getwindowheight()/2-100;
    drawText("SEGMENTE",titleX,titleY,WHITE,28);
    rectangle(titleX,titleY,titleX+390,titleY+50);
    int buttonX=getwindowwidth()/2-80;
    int buttonY=getwindowheight()/2;
    buttons[nButtons]= {buttonX,buttonY,buttonX+130,buttonY+40,"Start"};
    drawButton(nButtons,RGB(3,36,80));
    nButtons++;
}

void drawOptions()
{
    setBackgroundColor(RGB(3,36,80));
    int titleX=getwindowwidth()/2-150;
    int titleY=40;
    drawText("OPTIONS",titleX,titleY,WHITE,28);
    rectangle(titleX,titleY,titleX+310,titleY+50);
    drawText("Game mode:",100,130,WHITE,16);
    drawText("Timer:",100,190,WHITE,16);
    drawText("Colored Points:",100,250,WHITE,16);
    drawText("Music:",100,310,WHITE,16);

    buttons[nButtons]={430,450,540,490,"Play"};
    drawButton(nButtons,getpixel(1,1)); //nButton1
    nButtons++;

    buttons[nButtons]={700,130,780,170,"PvC"};
    drawButton(nButtons,getpixel(1,1));
    nButtons++;

    buttons[nButtons]={700,190,780,230,"NO"};
    drawButton(nButtons,getpixel(1,1));
    nButtons++;

    buttons[nButtons]={700,250,780,290,"NO"};
    drawButton(nButtons,getpixel(1,1));
    nButtons++;

    buttons[nButtons]={700,310,780,350,"NO"};
    drawButton(nButtons,getpixel(1,1));
    nButtons++;

    std::cout<<"Number of buttons: "<<nButtons<<'\n';
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
