#include "algorithms.h"
#include <iostream>
using namespace std;

bool isOnSegment(Point p,Point q,Point r)
{
    if(q.x<=max(p.x, r.x)&&q.x>=min(p.x, r.x) &&
        q.y<=max(p.y, r.y)&&q.y>=min(p.y, r.y))
       return true;
    return false;
}

int getOrientation(Point p, Point q, Point r)
{
    int val=(q.y-p.y)*(r.x-q.x)-(q.x - p.x)*(r.y - q.y);
    if (val==0)
        return 0;
    return (val>0)?1:2;
}

bool doIntersect(Segment s1, Segment s2)
{
    Point p1=s1.a;
    Point q1=s1.b;
    Point p2=s2.a;
    Point q2=s2.b;
    int o1=getOrientation(p1, q1, p2);
    int o2=getOrientation(p1, q1, q2);
    int o3=getOrientation(p2, q2, p1);
    int o4=getOrientation(p2, q2, q1);
    if(o1!=o2&&o3!=o4)
        return true;
    if(o1==0&&isOnSegment(p1, p2, q1))
        return true;
    if(o2==0&&isOnSegment(p1, q2, q1))
        return true;
    if(o3==0&&isOnSegment(p2, p1, q2))
        return true;
    if(o4==0&&isOnSegment(p2, q1, q2))
        return true;
    return false;
}

bool isCollinear(Point a, Point b, Point c)
{
    return(a.x*b.y+b.x*c.y+c.x*a.y-c.x*b.y-a.x*c.y-b.x*a.y==0);
}
