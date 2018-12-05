#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#include <stdlib.h>
#include <time.h>
#include "customgraphics.h"
#define MAX 100

struct Point
{
    int x,y;
} points[MAX];

struct Segment
{
    Point a,b;
};

int nPoints,nSegments;

bool isOver() {
    return false;
}

void addPoints(int number) {
    srand(time(NULL));
    int width=getwindowwidth();
    int height=getwindowheight();
    for(int i=1;i<=number;i++) {
        int x=rand()%(width*4/5);
        int y=rand()%height;
        points[nPoints++]={x,y};
        drawPoint(x,y);
    }
}

void showGameScreen() {
    drawGameArea();
    //drawScoreboard();
    addPoints(50);
    while(!isOver()) {
        if(ismouseclick(WM_LBUTTONDOWN)) {
            int x,y;
            getmouseclick(WM_LBUTTONDOWN,x,y);
            if(isInsideButton(x,y,0)) {
                break;
            }
        }
    }
}

void showStartScreen() {
    drawMenu();
    do {
        if(ismouseclick(WM_LBUTTONDOWN)) {
            int x,y;
            getmouseclick(WM_LBUTTONDOWN,x,y);
            if(isInsideButton(x,y,0)) {
                break;
            }
        }
    } while(true);
}

void startGame() {
    initwindow(960,540);
    showStartScreen();
    //showOptionsScreen();
    showGameScreen();
    getch();
    closegraph();
}


int main()
{
    startGame();
    return 0;
}

