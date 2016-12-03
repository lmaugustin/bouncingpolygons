#include "polygon.h"
#include "gfx.h"
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include <iostream>

using namespace std;

const int DEFAULT_RADIUS = 50;
const int VELOCITY_MIN = -20;
const int VELOCITY_MAX = 20;
const int DEFAULT_ACCELERATION = 1;
const int COLOR_MIN = 0;
const int COLOR_MAX = 255;

void gfx_color(Color c) {
  gfx_color(c.r, c.g, c.b);
}

Polygon::Polygon(int x, int y, int s) {
  if((s < 0) || (s == 1) || (s == 2)) {
    // number of sides must 0 (a circle) or 3 or greater. <0, 1, or 2 are not allowed
    cout << "Error: Attempt to create Polygon with sides: " << s << endl;
  }
  sides = s;
  xc = x;
  yc = y;
  // Random size (radius)
  rad = (s == 0) ? DEFAULT_RADIUS : ((DEFAULT_RADIUS*2*PI)/sides) ;
  // Random starting angle
  angle = 0;
  // Random color
  c.r = (rand() % (COLOR_MAX - COLOR_MIN)) + COLOR_MIN ;
  c.g = (rand() % (COLOR_MAX - COLOR_MIN)) + COLOR_MIN ;
  c.b = (rand() % (COLOR_MAX - COLOR_MIN)) + COLOR_MIN ;
  // Start with random velocity vectors
  // Make sure both vectors are non-zero
  do {
    vx = (rand() % (VELOCITY_MAX - VELOCITY_MIN)) + VELOCITY_MIN ;
    vy = (rand() % (VELOCITY_MAX - VELOCITY_MIN)) + VELOCITY_MIN ;
  } while ((vx == 0) || (vy == 0));
  dt = DEFAULT_ACCELERATION;
}

void Polygon::Draw() {
  double theta = angle;
  double i = (2*PI)/sides;
  double y = xc;
  double x = yc;
  double x1 = x+(rad*cos(theta));
  double y1 = y-(rad*sin(theta));
  
  gfx_color(c);

  if (sides == 0) {  // special case for sides == 0 is a circle
    gfx_circle(xc, yc, rad);
  } else {
    for(int j=0; j < sides; j++) {
      gfx_line(x,y,x1,y1);
#ifdef DEBUG
      cout << "gfx_line(" << x << "," << y << "," << x1 << "," << y1 << ")" << endl;
#endif
      theta += i;
      x=x1;
      y=y1;
      x1 = x+(rad*cos(theta));
      y1 = y-(rad*sin(theta));
    }
  }
#ifdef DEBUG
  cout << endl;
#endif
}

// Move and rotate the polygon.  Don't worry about hitting walls or other polygons
void Polygon::Move() {
  double ROTATION_RATE = PI/32.0;

  // Move the center according to the velocity vectors
  xc = xc + vx*dt;
  yc = yc + vy*dt;

  // Rotate the starting angle
  angle += ROTATION_RATE;
}

// Check if the Polygon has hit another Polygon.  Change the veolocity vectors of both
// Polygons to bounce of each other.
void Polygon::CheckHit(Polygon &p) {
}


// Check if the Polygon has hit a wall.  Change the veolocity vectors to bounce the Polygon
// if it has.
void Polygon::CheckWall(int width, int height) {
}
