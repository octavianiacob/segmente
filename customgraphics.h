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

void drawPoint(int x, int y, int radius=5, int color=WHITE);

void drawSegment(int ax, int ay, int bx, int by, int thickness=1, int color=WHITE);

bool isInsideButton(int x,int y,int buttonIndex);

#endif // CUSTOMGRAPHICS_H_INCLUDED
