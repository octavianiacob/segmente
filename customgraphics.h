#ifndef CUSTOMGRAPHICS_H_INCLUDED
#define CUSTOMGRAPHICS_H_INCLUDED

void drawText(char *text, int x, int y, int color=BLACK, int font=COMPLEX_FONT, int textSize=12);

void setBackgroundColor(int color);

void drawPoint(int x, int y, int color);

void drawSegment(int ax, int ay, int bx, int by, int thickness=1, int color=WHITE);

void setupWindow();

#endif // CUSTOMGRAPHICS_H_INCLUDED
