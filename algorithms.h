#ifndef ALGORITHMS_H_INCLUDED
#define ALGORITHMS_H_INCLUDED

struct Point
{
    int x,y;
};

struct SegmentEnd {
    int x,y;
    int segmIndex;
};

struct Segment
{
    Point a,b;
};

bool isOnSegment(Segment s, Point r);

int getOrientation(Point p, Point q, Point r);

bool doIntersect(Segment s1, Segment s2);

#endif // ALGORITHMS_H_INCLUDED
