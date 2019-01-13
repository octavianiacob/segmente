#ifndef CUSTOMGRAPHICS_H_INCLUDED
#define CUSTOMGRAPHICS_H_INCLUDED

struct Button {
    int x1, y1, x2, y2;
    char name[20];
};

void drawButton(int buttonIndex, int bgColor=RGB(3,36,80), int textSize=16,int font=COMPLEX_FONT);

void changeButtonText(int buttonIndex, char text[20]);

void drawGameArea();

void drawScoreboard();

void drawText(char *text, int x, int y, int color, int font, int textSize);

void setBackgroundColor(int color);

void drawMenu();

void drawOptions();

void drawDot(Point p, int color=WHITE);

void drawSegment(Point a, Point b,int color=WHITE, int thickness=1);

bool isInsideButton(int x,int y,int buttonIndex);

bool isInsideDot(Point p,Point c);

void showNotice();

#endif // CUSTOMGRAPHICS_H_INCLUDED
