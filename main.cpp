#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "algorithms.h"
#include "customgraphics.h"
#define MAX_POINTS 100
#define PLAYER1 RGB(0,255,255)
#define PLAYER2 YELLOW
Point points[MAX_POINTS];

enum GameMode {
    PvP,
    PvC
};

GameMode gameMode=PvC;
int nPoints,nSegments;
int turn=PLAYER1,player1Score,player2Score;
Segment seg[MAX_POINTS/2];

bool isValidSegment(Segment s) {
    if(s.a.x==s.b.x&&s.a.y==s.b.y)
        return false;
    for(int i=0;i<nSegments;i++)
        if(doIntersect(s, seg[i]))
            return false;
    return true;
}

bool isGameOver() {
    for(int i=0;i<nPoints;i++)
    for(int j=i+1;j<nPoints;j++)
        if(points[i].x&&points[j].x&&isValidSegment({points[i], points[j]}))
            return false;
    return true;
}

void addPoints() {
    nPoints=0,nSegments=0;
    srand(time(NULL));
    int width=getwindowwidth();
    int height=getwindowheight();
    for(int i=1;i<=8;i++)
    for(int j=1;j<=10;j++) {
        Point p={j*70-20,i*60-20};
        p.x+=rand()%30-15;
        p.y+=rand()%30-15;
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

void addSegmentToArray(int index1, int index2) {
    Segment s = {points[index1], points[index2]};
    seg[nSegments++]=s;
    points[index1].x=0;
    points[index2].x=0;
}

bool isBlocked(Point p) {
    for(int i=0;i<nPoints;i++)
        if(points[i].x&&isValidSegment({p,points[i]}))
            return false;
    return true;
}

bool isValidNeighbour(int i,int n) {
    if(i+n<0||i+n>=nPoints)
        return false;
    if(points[i+n].x==0)
        return false;
    if(i%10==0&&(n==-11||n==-1||n==9))
        return false;
    if(i%10==9&&(n==-9||n==1||n==11))
        return false;
    return true;
}

int countFreeNeighbours(int pointIndex) {
    int counter=0;
    int neighbours[]={-11,-10,-9,-1,1,9,10,11};
    for(int i=0;i<8;i++) {
        int neighbourIndex=pointIndex+neighbours[i];
        if(isValidNeighbour(pointIndex,neighbours[i]))
            counter++;
    }
    return counter;
}

void doComputerMove() {
    bool found=false;
    int point1Index=-1,point2Index=-1;
    int neighbours[]={-11,-10,-9,-1,1,9,10,11};
    nSegments++;
    for(int i=0;i<nPoints&&!found;i++) {
        if(points[i].x&&countFreeNeighbours(i)<=4&&!isBlocked(points[i])) {
            for(int j=0;j<8&&!found;j++)
            for(int k=j+1;k<8&&!found;k++) {
                int ji=i+neighbours[j],ki=i+neighbours[k];
                if(isValidNeighbour(i,neighbours[j])&&isValidNeighbour(i,neighbours[k])
                   &&isValidSegment({points[ji],points[ki]})) {
                    seg[nSegments]={points[ji],points[ki]};
                    int temp1=points[ji].x,temp2=points[ki].x;
                    points[ji].x=points[ki].x=0;
                    point1Index=ji,point2Index=ki;
                    if(isBlocked(points[i])) {
                        points[i].x=0;
                        found=true;
                    }
                    points[ji].x=temp1;
                    points[ki].x=temp2;
                }
            }
        }
    }
    nSegments--;
    if(point1Index==-1) {
        for(int i=0;i<nPoints;i++)
        for(int j=i+1;j<nPoints;j++)
            if(points[i].x&&points[j].x&&isValidSegment({points[i],points[j]}))
                point1Index=i,point2Index=j;
    }
    drawSegment(points[point1Index],points[point2Index],PLAYER2);
    drawDot(points[point1Index],PLAYER2);
    drawDot(points[point2Index],PLAYER2);
    addSegmentToArray(point1Index,point2Index);
}

void doPlayerMove() {
    int x,y,p1,p2;
    do {
        getmouseclick(WM_LBUTTONDOWN,x,y);
        p1=getPointIndex({x,y});
        if(p1<0)
            continue;
        drawDot(points[p1],turn);
        do {
            getmouseclick(WM_LBUTTONDOWN,x,y);
            p2=getPointIndex({x,y});
            if(p2==p1) {
                drawDot(points[p1]);
                p1=-1;
                break;
            }
            if(p2>=0&&isValidSegment({points[p1],points[p2]})){
                drawSegment(points[p1],points[p2],turn);
                drawDot(points[p2],turn);
                addSegmentToArray(p1,p2);
            }
            else
                p2=-1;
        } while(p2<0);
    } while(p1<0);
}

void updateScores() {
    char score1[2], score2[2];
    itoa(player1Score,score1,10);
    itoa(player2Score,score2,10);
    setfillstyle(SOLID_FILL,RGB(250,250,250));
    drawText(score1,850,250,BLACK,12,GOTHIC_FONT);
    drawText(score2,850,400,BLACK,12,GOTHIC_FONT);
}

void playLevel() {
    drawGameArea();
    addPoints();
    turn=PLAYER1;
    while(!isGameOver()) {
        if(gameMode==PvC&&turn==PLAYER2)
            doComputerMove();
        else
            doPlayerMove();
        if(turn==PLAYER1)
            turn=PLAYER2;
        else
            turn=PLAYER1;
    }
    if(turn==PLAYER1)
        player2Score++;
    else
        player1Score++;
}

void showGameScreen() {
    clearviewport();
    drawScoreboard();
    for(int i=1;i<=3;i++) {
        updateScores();
        playLevel();
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
            if(isInsideButton(x,y,1))
                break;
        }
    } while(true);
    showGameScreen();
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

