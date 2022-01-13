#include <iostream>
#include <math.h>
#include <vector>
#include <stdlib.h>
#include <stdio.h>


using namespace std;

int r[1080];

void init();

int distl(int dN, int x, int y);

typedef struct {
    int x;
    int y;
} point;

int distPP(point p, point p1);


typedef struct {
    bool vertical;// 0 if horizontal
    int startX, startY;
    int length;
} border;
border borders[11];

int main() {
    init();
    for (int i = 0; i < 10; ++i) {
        int x = 2728;
        int y = 1915;
        for (int j = 0; j < 11; ++j) {
            printf("distance from (%4d,%4d) to border %2d is %d\n", x, y, j, distl(j, x, y));
        }

    }
    return 0;
}


void init() {
    borders[0].startX = 0;
    borders[0].startY = 0;
    borders[0].length = 6924;
    borders[0].vertical = true;

    borders[1].startX = 0;
    borders[1].startY = 0;
    borders[1].length = 3424;
    borders[1].vertical = false;

    borders[2].startX = 3424;
    borders[2].startY = 0;
    borders[2].length = 6924;
    borders[2].vertical = true;

    borders[3].startX = 0;
    borders[3].startY = 6924;
    borders[3].length = 3424;
    borders[3].vertical = false;

    borders[4].startX = 962;
    borders[4].startY = 1428;
    borders[4].length = 1500;
    borders[4].vertical = false;

    borders[5].startX = 962;
    borders[5].startY = 1428;
    borders[5].length = 38;
    borders[5].vertical = true;

    borders[6].startX = 2462;
    borders[6].startY = 1428;
    borders[6].length = 38;
    borders[6].vertical = true;

    borders[7].startX = 962;
    borders[7].startY = 1462;
    borders[7].length = 1500;
    borders[7].vertical = false;

    borders[8].startX = 962;
    borders[8].startY = 5462;
    borders[8].length = 1500;
    borders[8].vertical = false;

    borders[9].startX = 962;
    borders[9].startY = 5462;
    borders[9].length = 1462;
    borders[9].vertical = true;

    borders[10].startX = 2462;
    borders[10].startY = 5462;
    borders[10].length = 1462;
    borders[10].vertical = true;
}

/**
 * distanceLight
 * Returns squared distance between the target border and point(for faster computing)
 * @param bN target border
 * @param x x coord of target point
 * @param y y coord of target point
 * @return
 */
int distl(int bN, int x, int y) {
    int t[2];
    int p[2];
    if (!borders[bN].vertical) {
        //invert x and y
        p[0] = y;
        p[1] = x;
        t[0] = borders[bN].startY;
        t[1] = borders[bN].startX;
    } else {
        p[0] = x;
        p[1] = y;
        t[0] = borders[bN].startX;
        t[1] = borders[bN].startY;
    }
    if (t[1] > p[1]) {
        return (p[1] - t[1]) * (p[1] - t[1]) + (p[0] - t[0]) * (p[0] - t[0]);
    }
    if ((t[1] + borders[bN].length) < p[1]) {
        return (t[1] + borders[bN].length - p[1]) * (t[1] + borders[bN].length - p[1]) + (p[0] - t[0]) * (p[0] - t[0]);
    }
    return (p[0] - t[0]) * (p[0] - t[0]);
}


int isCrossed(int x, int y, double deg, int bN) {
    int t[2];
    int p[2];
    if (!borders[bN].vertical) {
        p[0] = y;
        p[1] = x;
        t[0] = borders[bN].startY;
        t[1] = borders[bN].startX;
    } else {
        p[0] = x;
        p[1] = y;
        t[0] = borders[bN].startX;
        t[1] = borders[bN].startY;
    }
    if (t[0] > p[0] && (deg < 0 || deg > 180))return -1;
    if (t[0] < p[0] && (deg > 0 && deg < 180))return -1;
    int ry = (t[0] - p[0]) * tan(deg) + p[1];
    if (ry > t[1] && ry < t[1] + borders[bN].length) {
        if (borders[bN].vertical) {
            return distPP(point{t[0], ry}, point{x, y});
        } else {
            return distPP(point{ry, t[0]}, point{x, y});
        }
    } else return -1;
}

int distPP(point p, point p1) {
    return sqrt((p.x - p1.x) * (p.x - p1.x) + (p.y - p1.y) * (p.y - p1.y));
}
