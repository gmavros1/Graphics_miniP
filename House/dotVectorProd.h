//
// Created by gmavros on 2/7/21.
//

#ifndef GRAPHICS_AUTH_DOTVECTORPROD_H
#define GRAPHICS_AUTH_DOTVECTORPROD_H

#endif //GRAPHICS_AUTH_DOTVECTORPROD_H

#include<stdio.h>

typedef struct{
    float i,j,k;
}Vector;



Vector crossProduct(Vector p0, Vector p1, Vector p2)
{
    Vector pl = { p2.i - p1.i, p2.j - p1.j, p2.k - p1.k};
    Vector pr = { p0.i - p1.i, p0.j - p1.j, p0.k - p1.k};
    Vector c = {pl.j * pr.k - pl.k * pr.j, pl.k * pr.i - pl.i * pr.k, pl.i * pr.j - pl.j * pr.i};

    return c;
}

