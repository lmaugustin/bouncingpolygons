#include "polygon.h"
#include "gfx.h"
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include <iostream>

using namespace std;

Polygon::Polygon(int x, int y, int s) {
  sides = s;
  xc = x;
  yc = y;
  angle = rad = 0;
  c = WHITE;
}

void Polygon::Draw() {
  double theta = angle;
  double i = (2*PI)/sides;
  int y = xc;
  int x = yc;
  int x1 = x+(25*cos(theta));
  int y1 = y-(25*sin(theta));
  
  gfx_color(this->c);

  for(int j=0; j < sides; j++) {
    gfx_line(x,y,x1,y1);
    cout << "gfx_line(" << x << "," << y << "," << x1 << "," << y1 << ")" << endl;
    theta += i;
    x=x1;
    y=y1;
    x1 = x+(25*cos(theta));
    y1 = y-(25*sin(theta));
  }
  cout << endl;
}

void Polygon::Move() {
  double ROTATION_RATE = PI/32.0;

  // Move the center according to the velocity vectors
  // xc = xc + vx*dt;
  // yc = yc + vy*dt;
  // Rotate the starting angle
  angle += ROTATION_RATE;
}

void gfx_color(Color c) {
  gfx_color(c.r, c.g, c.b);
}

void Polygon::CheckHit(Polygon &p) {
}

void Polygon::CheckWall(int width, int height) {
}
