#ifndef CUSTOMGRAPHICS_H_INCLUDED
#define CUSTOMGRAPHICS_H_INCLUDED

struct Button {
    int x1, y1, x2, y2;
    char *name;
};

void drawGameArea();

void drawScoreboard();

void drawText(char *text, int x, int y, int color, int font, int textSize);

void setBackgroundColor(int color);

void drawMenu();

void drawDot(Point p, int color=WHITE);

void drawSegment(Point a, Point b, int thickness=1, int color=WHITE);

bool isInsideButton(int x,int y,int buttonIndex);

bool isInsideDot(Point p,Point c);

#endif // CUSTOMGRAPHICS_H_INCLUDED
