#ifndef BALL_H
#define BALL_H

#include <vector>

using namespace std;

class Color {
 public:
  int r, g, b;
  Color(int red, int green, int blue) {r = red; g = green; b = blue;};
  Color() {r=g=b=0;};
};

const Color BLACK = Color(0,0,0);
const Color WHITE = Color(255,255,255);
const Color RED =   Color(255,0,0);
const Color GREEN = Color(0,255,0);
const Color BLUE =  Color(0,0,255);

void gfx_color(Color c);

static const double PI = 3.14159;

class Polygon {
 public:
  Polygon(int x, int y, int s);
  void Draw();
  void Move();
  void CheckHit(Polygon &p);
  void CheckWall(int width, int height);

  double xc, yc;   // x and y coordinators of the polygon center
  double rcx, rcy; // real center for moving polygons
  double vx, vy;   // velocity in the x and y directions
  double dt;       // acceleration.  volocity will be multiplied times this.
  double angle;    // rotation angle
  double rad;      // radius
  Color c;         // color
  int sides;       // number of sides
};

typedef vector<Polygon> polygon_array_t;

#endif
