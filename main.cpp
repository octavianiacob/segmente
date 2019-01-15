#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "algorithms.h"
#include "customgraphics.h"
#include <Windows.h>
#include <MMSystem.h>
#define MAX_POINTS 100
#define PLAYER1 RGB(0,255,255)
#define PLAYER2 YELLOW
Point points[MAX_POINTS];

enum GameMode
{
    PvP=2,
    PvC=1

};

GameMode gameMode=PvC;
bool timer=false,music=false,coloredPoints=false;
int nPoints,nSegments;
int turn=PLAYER1,player1Score,player2Score;
int colors[MAX_POINTS];
int levelStartTime;
Segment seg[MAX_POINTS/2];

bool isValidSegment(Segment s)
{
    if(coloredPoints&&getpixel(s.a.x,s.a.y)!=getpixel(s.b.x,s.b.y))
        return false;
    if(s.a.x==s.b.x&&s.a.y==s.b.y)
        return false;
    for(int i=0; i<nSegments; i++)
        if(doIntersect(s, seg[i]))
            return false;
    for(int i=0;i<nPoints;i++)
        if(((s.a.x!=points[i].x||s.a.y!=points[i].y)&&(s.b.x!=points[i].x||s.b.y!=points[i].y))&&isCollinear(s.a,s.b,points[i]))
            return false;
    return true;
}

bool isGameOver()
{
    for(int i=0; i<nPoints; i++)
        for(int j=i+1; j<nPoints; j++)
            if(points[i].x&&points[j].x&&isValidSegment({points[i], points[j]}))
                return false;
    return true;
}

void recolorPoints()
{
    srand(time(0));
    for(int i=0; i<nPoints; i++)
        if(points[i].x)
        {
            if(rand()%2==0)
            {
                drawDot(points[i],PLAYER1);
                colors[i]=PLAYER1;
            }
            else
            {
                drawDot(points[i],PLAYER2);
                colors[i]=PLAYER2;
            }
        }
}

void addPoints()
{
    nPoints=0,nSegments=0;
    srand(time(NULL));
    int width=getwindowwidth();
    int height=getwindowheight();
    for(int i=1; i<=8; i++)
    for(int j=1; j<=10; j++)
    {
        Point p= {j*70-20,i*60-20};
        p.x+=rand()%30-15;
        p.y+=rand()%30-15;
        points[nPoints++]=p;
        drawDot(p);
    }
}

int getPointIndex(Point p)
{
    for(int i=0; i<nPoints; i++)
        if(isInsideDot(p,points[i]))
            return i;
    return -1;
}

void addSegmentToArray(int index1, int index2)
{
    Segment s = {points[index1], points[index2]};
    seg[nSegments++]=s;
    points[index1].x=0;
    points[index2].x=0;
}

bool isBlocked(Point p)
{
    for(int i=0; i<nPoints; i++)
        if(points[i].x&&isValidSegment({p,points[i]}))
            return false;
    return true;
}

bool isValidPoint(int index)
{
    if(coloredPoints&&turn!=colors[index])
        return false;
    return points[index].x;
}

bool isValidNeighbour(int i,int n)
{
    if(!isValidPoint(i)||!isValidPoint(i+n))
        return false;
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

int countFreeNeighbours(int pointIndex)
{
    int counter=0;
    int neighbours[]= {-11,-10,-9,-1,1,9,10,11};
    for(int i=0; i<8; i++)
    {
        int neighbourIndex=pointIndex+neighbours[i];
        if(isValidNeighbour(pointIndex,neighbours[i]))
            counter++;
    }
    return counter;
}

void doComputerMove()
{
    turn=PLAYER2;
    bool found=false;
    int point1Index=-1,point2Index=-1;
    int neighbours[]= {-11,-10,-9,-1,1,9,10,11};
    nSegments++;
    for(int i=0; i<nPoints&&!found; i++)
    {
        if(isValidPoint(i)&&!isBlocked(points[i])&&countFreeNeighbours(i)<=4)
        {
            for(int j=0; j<8&&!found; j++)
                for(int k=j+1; k<8&&!found; k++)
                {
                    int ji=i+neighbours[j],ki=i+neighbours[k];
                    if(isValidNeighbour(i,neighbours[j])&&isValidNeighbour(i,neighbours[k])
                            &&isValidSegment({points[ji],points[ki]}))
                    {
                        seg[nSegments]= {points[ji],points[ki]};
                        int temp1=points[ji].x,temp2=points[ki].x;
                        points[ji].x=points[ki].x=0;
                        point1Index=ji,point2Index=ki;
                        if(isBlocked(points[i]))
                        {
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
    if(point1Index==-1)
    {
        for(int i=0; i<nPoints; i++)
            for(int j=i+1; j<nPoints; j++)
                if(isValidPoint(i)&&isValidPoint(j)&&isValidSegment({points[i],points[j]}))
                    point1Index=i,point2Index=j;
    }
    drawSegment(points[point1Index],points[point2Index],PLAYER2);
    drawDot(points[point1Index],PLAYER2);
    drawDot(points[point2Index],PLAYER2);
    addSegmentToArray(point1Index,point2Index);
}

void doPlayerMove()
{
    int x,y,p1,p2;
    clock_t startTime=clock(),lastTime=31;
    do
    {
        getmouseclick(WM_LBUTTONDOWN,x,y);
        p1=getPointIndex({x,y});
        int timeLeft=20-(clock()-startTime)/CLOCKS_PER_SEC;
        if(timer&&lastTime!=timeLeft)
            updateTimer(timeLeft);

        if(timer&&timeLeft==0)
        {
            updateTimer(30);
            return;
        }
        if(coloredPoints&&lastTime!=timeLeft&&((clock()-levelStartTime)/CLOCKS_PER_SEC)%10==0)
            recolorPoints();
        lastTime=timeLeft;
        if(p1<0)
            continue;
        if(isValidPoint(p1))
            drawDot(points[p1],turn);
        else
        {
            p1=-1;
            continue;
        }
        do
        {
            getmouseclick(WM_LBUTTONDOWN,x,y);
            p2=getPointIndex({x,y});
            timeLeft=20-(clock()-startTime)/CLOCKS_PER_SEC;
            if(timer&&timeLeft==0)
            {
                drawDot(points[p1],WHITE);
                updateTimer(30);
                return;
            }
            if(coloredPoints&&((clock()-levelStartTime)/CLOCKS_PER_SEC)%10==0)
            {
                recolorPoints();
                if(!isValidPoint(p1))
                {
                    p1=-1,p2=-1;
                    break;
                }
            }
            if(timer&&timeLeft!=lastTime)
                updateTimer(timeLeft);
            lastTime=timeLeft;
            if(!coloredPoints&&p2==p1)
            {
                drawDot(points[p1]);
                p1=-1;
                break;
            }
            if(p2>=0&&isValidPoint(p2)&&isValidSegment({points[p1],points[p2]}))
            {

                drawSegment(points[p1],points[p2],turn);
                drawDot(points[p2],turn);
                addSegmentToArray(p1,p2);
            }
            else
                p2=-1;
        }
        while(p2<0);
    }
    while(p1<0);
}

void updateScores()
{
    char score1[2], score2[2];
    itoa(player1Score,score1,10);
    itoa(player2Score,score2,10);
    setfillstyle(SOLID_FILL,RGB(250,250,250));
    if(player1Score>=1)
        readimagefile("star.bmp",805,217,835,247);
    if(player2Score>=1)
        readimagefile("star.bmp",805,332,835,362);

    if(player1Score>=2)
        readimagefile("star.bmp",835,217,865,247);
    if(player2Score>=2)
        readimagefile("star.bmp",835,332,865,362);

    if(player1Score>=3)
        readimagefile("star.bmp",865,217,895,247);
    if(player2Score>=3)
        readimagefile("star.bmp",865,332,895,362);
}

void playLevel()
{
    drawGameArea();
    drawScoreboard(gameMode, timer);
    if(gameMode==PvP)
    {
        setcolor(RGB(0,255,255));
        line(770,215,930,215);
    }
    updateScores();
    addPoints();
    if(coloredPoints)
        recolorPoints();
    turn=PLAYER1;
    if(timer)
        updateTimer(30);
    levelStartTime=clock();
    if(music)
        PlaySound("soundtrack.wav", NULL, SND_ASYNC);
    while(!isGameOver())
    {
        if(gameMode==PvC&&turn==PLAYER2)
            doComputerMove();
        else
            doPlayerMove();
        if(turn==PLAYER1)
        {
            turn=PLAYER2;
            if(gameMode==PvP)
            {
                setcolor(YELLOW);
                line(770,330,930,330);
                setcolor(BLACK);
                line(770,215,930,215);
            }
        }
        else
        {
            turn=PLAYER1;
            if(gameMode==PvP)
            {
                setcolor(RGB(0,255,255));
                line(770,215,930,215);
                setcolor(BLACK);
                line(770,330,930,330);
            }
        }

    }
    if(turn==PLAYER1)
    {
        player2Score++;
        if(gameMode==PvC)
            readimagefile("computerwin.bmp",0,0,getwindowwidth(),210);
        else
            readimagefile("p2win.bmp",0,0,getwindowwidth(),210);
    }
    else
    {
        player1Score++;
        readimagefile("p1win.bmp",0,0,getwindowwidth(),210);
    }
    showNotice();
    if(player1Score+player2Score<3)
        playLevel();
    else
        showNotice();
}

void showGameScreen()
{
    clearviewport();
    drawScoreboard(gameMode, timer);
    for(int i=1; i<=3; i++)
    {
        updateScores();
        playLevel();
    }
}

void showStartScreen()
{
    drawMenu();
    do
    {
        int x,y;
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN,x,y);
            if(isInsideButton(x,y,0))
                break;
        }
    }
    while(true);
}

void showOptionsScreen()
{
    drawOptions();
    bool hovered=false;
    do
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            int x,y;
            getmouseclick(WM_LBUTTONDOWN,x,y);
            if(isInsideButton(x,y,1))
                break;
            else if(isInsideButton(x,y,2)) //Game mode button
            {
                if(gameMode==PvC)
                {
                    gameMode=PvP;
                    readimagefile("2p.bmp",608,182,722,217);
                }
                else
                {
                    gameMode=PvC;
                    readimagefile("1p.bmp",608,182,722,217);
                }
            }
            if(isInsideButton(x,y,3)) //Timer Button
            {
                timer=!timer;
                if(timer)
                    readimagefile("yes.bmp",608,242,722,277);
                else
                    readimagefile("no.bmp",608,242,722,277);
            }
            if(isInsideButton(x,y,4)) //Colored Points Button
            {
                coloredPoints=!coloredPoints;
                if(coloredPoints)
                    readimagefile("yes.bmp",608,302,722,337);
                else
                    readimagefile("no.bmp",608,302,722,337);
            }
            if(isInsideButton(x,y,5)) //Music Button
            {
                music=!music;
                if(music)
                    readimagefile("yes.bmp",608,362,722,397);
                else
                    readimagefile("no.bmp",608,362,722,397);
            }
        }
    }
    while(true);
    showGameScreen();
}

void startGame()
{
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

