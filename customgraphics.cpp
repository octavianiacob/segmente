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

void drawGameArea() {
    setfillstyle(SOLID_FILL,BLACK);
    bar(0,0,0.8*getwindowwidth(),getwindowheight());
}

void drawText(char *text, int x, int y, int color=BLACK, int textSize=12,int font=GOTHIC_FONT)
{
    setcolor(color);
    setbkcolor(getpixel(x, y));
    settextstyle(font,HORIZ_DIR,textSize);
    outtextxy(x, y, text);
}

void drawButton(char *text, int x1, int y1, int x2, int y2, int bgColor=RED, int textSize=16,int font=COMPLEX_FONT) {
    setfillstyle(SOLID_FILL, bgColor);
    bar(x1,y1,x2,y2);
    drawText(text,x1,y1,WHITE,textSize,font);
    setcolor(WHITE);
    rectangle(x1,y1,x2,y2);
    buttons[nButtons++]={x1,y1,x2,y2,text};
}

void drawScoreboard() {
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

void drawMenu() {
    readimagefile("bg.bmp",0,0,getwindowwidth(),getwindowheight());
    int titleX=getwindowwidth()/2-200;
    int titleY=getwindowheight()/2-100;
    drawText("SEGMENTE",titleX,titleY,WHITE,28);
    rectangle(titleX,titleY,titleX+390,titleY+50);
    int buttonX=getwindowwidth()/2-80;
    int buttonY=getwindowheight()/2;
    drawButton("Start",buttonX,buttonY,buttonX+130,buttonY+40,getpixel(buttonX,buttonY));
}

void drawOptions() {
    /*setBackgroundColor(MAGENTA);
    int titleX=getwindowwidth()/2-200;
    int titleY=getwindowheight()/2-120;
    drawText("Options",25,25,WHITE,5);
    line(0,70,getwindowwidth(),70);
    drawButton("Play",430,470,BLUE,15,COMPLEX_FONT); //nButton 1
    drawText("Game Mode:",25,100,WHITE,4);
    drawButton("Player vs Player",270,105,BLUE,3); //nButton 2
    drawButton("Player vs Computer",570,105,BLUE,3); //nButton 3
    drawText("Best of:",25,170,WHITE,4);
    drawButton("3",270,170,BLUE,3); //nButton 4
    drawButton("5",370,170,BLUE,3); //nButton 5
    drawButton("7",470,170,BLUE,3); //nButton 6
    drawText("Player1 Color:",25,240,WHITE,4);
    drawButton("Select",340,245,BLUE,3); //nButton 7
    drawText("Player2 Color:",525,240,WHITE,4);
    drawButton("Select",840,245,BLUE,3); //nButton 8
    drawText("Timer:",25,310,WHITE,4);
    drawButton("Yes",180,315,BLUE,3); //nButton 9
    drawButton("No",250,315,BLUE,3); //nButton 10*/
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
    for(int i=1;i<=thickness;i++)
    {
        line(a.x,a.y,b.x,b.y);
        line(a.x+i-1,a.y,b.x+i-1,b.y);
        line(a.x-i+1,a.y,b.x-i+1,b.y);
    }
}

bool isInsideButton(int x,int y,int buttonIndex) {
    Button button=buttons[buttonIndex];
    return x>=button.x1&&x<=button.x2&&y>=button.y1&&y<=button.y2;
}

bool isInsideDot(Point p,Point c) {
    return sqrt((p.x-c.x)*(p.x-c.x)+(p.y-c.y)*(p.y-c.y))<=dotRadius;
}
