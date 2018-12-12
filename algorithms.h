#ifndef ALGORITHMS_H_INCLUDED
#define ALGORITHMS_H_INCLUDED

struct Point
{
    int x,y;
};

struct Segment
{
    Point a,b;
};

bool isOnSegment(Segment s, Point r);

int getOrientation(Point p, Point q, Point r);

bool doIntersect(Segment s1, Segment s2);

bool isCollinear(Point a, Point b, Point c);


#endif // ALGORITHMS_H_INCLUDED
