#include "polygon.h"
#include "gfx.h"
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include <iostream>

using namespace std;

static int WIN_WIDTH = 600;
static int WIN_HEIGHT = 600;
static int LOOPTIME = 1000000;

int main() {
  char c = ' ';
  int side_counter = 3;
  polygon_array_t Polygons;

  gfx_open(WIN_WIDTH, WIN_HEIGHT, "Bouncing Polygons");

  while( c != 'q') {
    gfx_clear();
    if(gfx_event_waiting()) {
      c = gfx_wait();
      if(c == 1) { // mouse click
	// Add a polygon
	int x = gfx_xpos();
	int y = gfx_ypos();
	Polygon *p = new Polygon(x,y,side_counter++);
	Polygons.push_back(*p);
	cout << "New Polygon added: " << side_counter-1 << endl;
      }
    }

    for(auto i = Polygons.begin(); i != Polygons.end(); i++) {
      i->Draw();
      i->Move();
    }

    for(auto i = Polygons.begin(); i != Polygons.end(); i++) {
      for(auto j = Polygons.begin(); j != Polygons.end(); j++) {
	i->CheckHit(*j);
      }
    }

    for(auto i = Polygons.begin(); i != Polygons.end(); i++) {
      i->CheckWall(WIN_WIDTH, WIN_HEIGHT);
    }

    gfx_flush();
    usleep(LOOPTIME);
  }
}
