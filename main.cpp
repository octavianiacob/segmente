#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#include <stdlib.h>
#include <time.h>
#include "algorithms.h"
#include "customgraphics.h"
#define MAX 100

Point points[MAX];

int nPoints,nSegments,turn=BLUE;

bool isOver() {
    return false;
}

void addPoints(int number) {
    srand(time(NULL));
    int width=getwindowwidth();
    int height=getwindowheight();
    for(int i=1;i<=number;i++) {
        Point p={rand()%(width*4/5-10)+10,rand()%(height-10)+10};
        points[nPoints++]=p;
        drawDot(p);
    }
}

int getPointIndex(Point p) {
    for(int i=0;i<nPoints;i++)
        if(isInsideDot(p,points[i]))
            return i;
    return -1;
}

bool isValidSegment(Point a, Point b) {
    return true;
}

void showGameScreen() {
    drawGameArea();
    drawScoreboard();
    addPoints(50);
    while(!isOver()) {
        if(ismouseclick(WM_LBUTTONDOWN)) {
            int x,y,p1,p2;
            getmouseclick(WM_LBUTTONDOWN,x,y);
            p1=getPointIndex({x,y});
            if(p1>=0) {
                do {
                    getmouseclick(WM_LBUTTONDOWN,x,y);
                    p2=getPointIndex({x,y});
                    if(p2>=0&&isValidSegment(points[p1],points[p2]))
                        drawSegment(points[p1],points[p2],turn);
                } while(p2<0);
            }
            if(turn==BLUE)
                turn=GREEN;
            else
                turn=BLUE;
        }
    }
}

void showStartScreen() {
    drawMenu();
    do {
        if(ismouseclick(WM_LBUTTONDOWN)) {
            int x,y;
            getmouseclick(WM_LBUTTONDOWN,x,y);
            if(isInsideButton(x,y,0))
                break;
        }
    } while(true);
}

void showOptionsScreen() {
    drawOptions();
    do {
        if(ismouseclick(WM_LBUTTONDOWN)) {
            int x,y;
            getmouseclick(WM_LBUTTONDOWN,x,y);
            std::cout<<x<<" "<<y<<" ";
            if(isInsideButton(x,y,1))
                showGameScreen();
        }
    } while(true);
}

void startGame() {
    initwindow(960,540);
    showStartScreen();
    showOptionsScreen();
    showGameScreen();
    getch();
    closegraph();
}

int main()
{
    startGame();
    return 0;
}

