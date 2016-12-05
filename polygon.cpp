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
  rcx = xc;
  rcy = yc;
  // Random size (radius)
  rad = DEFAULT_RADIUS;
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
  double draw_radius = (sides == 0) ? rad : ((rad*2.0*PI)/sides) ;
  double x = xc-0.5*(draw_radius*cos(theta));
  double y = yc+0.5*(draw_radius*sin(theta));
  double x1 = x+(draw_radius*cos(theta));
  double y1 = y-(draw_radius*sin(theta));
  double xsum = 0.0;
  double ysum = 0.0;
  
  gfx_color(c);

  if (sides == 0) {  // special case for sides == 0 is a circle
    gfx_circle((int)xc, (int)yc, (int)draw_radius);
    rcx = xc;
    rcy = yc;
  } else {
    for(int j=0; j < sides; j++) {
      gfx_line(x,y,x1,y1);
      xsum = xsum + x;
      ysum = ysum + y;
#ifdef DEBUG
      cout << "gfx_line(" << x << "," << y << "," << x1 << "," << y1 << ")" << endl;
#endif
      theta += i;
      x=x1;
      y=y1;
      x1 = x+(draw_radius*cos(theta));
      y1 = y-(draw_radius*sin(theta));
    }
    rcx = xsum/sides;
    rcy = ysum/sides;
  }
  gfx_circle((int)rcx, (int)rcy, 2);
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

double sqr(double x) {
  return x*x;
}

// Check if the Polygon has hit another Polygon.  Change the veolocity vectors of both
// Polygons to bounce of each other.
void Polygon::CheckHit(Polygon &p) {
  double draw_radius = (sides == 0) ? rad : ((rad*2.0*PI)/sides) ;
  double distance = sqrt(sqr(rcx - p.rcx) + sqr(rcy - p.rcy));
  double delta = 1.2;

  if(distance < draw_radius) {
    if((vx > 0) && (p.vx > 0)) {
      if(rcx > p.rcx) {
	p.vx = -p.vx;
      } else {
	vx = -vx;
      }
    } else if ((vx < 0) && (p.vx < 0)) {
      if (rcx > p.rcx) {
	vx = -vx;
      } else {
	p.vx = -p.vx;
      }
    } else if ((vx < 0) && (p.vx > 0)) {
      if (rcx > p.rcx) {
	vx = -vx;
	p.vx = -p.vx;
      }
    } else {
      if (rcx < p.rcx) {
	vx = -vx;
	p.vx = -p.vx;
      }
    }
    
    if((vy > 0) && (p.vy > 0)) {
      if(rcy < p.rcy) {
	vy = -vy;
      } else {
	p.vy = -p.vy;
      }
    } else if ((vy < 0) && (p.vy < 0)) {
      if (rcy < p.rcy) {
	p.vy = -p.vy;
      } else {
	vy = -vy;
      }
    } else if ((vy < 0) && (p.vy > 0)) {
      if (p.rcy > rcy) {
	vy = -vy;
	p.vy = -p.vy;
      }
    } else {
      if (p.rcy < rcy) {
	vy = -vy;
	p.vy = -p.vy;
      }
    }

    // Move the center according to the new velocity vectors
    xc = xc + vx*dt*delta;
    yc = yc + vy*dt*delta;

    p.xc = p.xc + p.vx*p.dt*delta;
    p.yc = p.yc + p.vy*p.dt*delta;
  }
}


// Check if the Polygon has hit a wall.  Change the veolocity vectors to bounce the Polygon
// if it has.
void Polygon::CheckWall(int width, int height) {
  if(((rcx + rad) >= width) && (vx > 0)){       // right wall
    vx = -vx;
  }
  if(((rcx - rad) <= 0) && (vx < 0)) {         // left wall
    vx = -vx;
  }
  if(((rcy + rad) >= height) && (vy > 0)) {  // bottom wall
    vy = -vy;
  }
  if(((rcy - rad) <= 0) && (vy < 0)) {         // top wall
    vy = -vy;
  }
}
