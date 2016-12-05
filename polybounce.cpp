// Andrea Augustin
// polybounce.cpp

#include "polygon.h"
#include "gfx.h"
#include <unistd.h>
#include <cstdlib>
#include <iostream>

using namespace std;

static int WIN_WIDTH = 600;
static int WIN_HEIGHT = 600;
static int LOOPTIME = 100000;

int main() {
  char input_c = ' ';
  int side_counter = 0;
  polygon_array_t Polygons;
  Polygon *p;

  gfx_open(WIN_WIDTH, WIN_HEIGHT, "Bouncing Polygons");

  while( input_c != 'q') {
    if(gfx_event_waiting()) {
      input_c = gfx_wait();
      if(input_c == 1) { // mouse click
	// Add a polygon
	int x = gfx_xpos();
	int y = gfx_ypos();
	p = new Polygon(x,y,side_counter);
	Polygons.push_back(*p);
	// special case the for the first circle
	side_counter = (side_counter == 0) ? (3) : (side_counter + 1);
#ifdef DEBUG
	cout << "New Polygon added: " << side_counter-1 << endl;
#endif
      }
    }

    gfx_clear();

    for(auto i = Polygons.begin(); i != Polygons.end(); i++) {
      i->Draw();
      i->Move();
    }

    for(auto i = Polygons.begin(); i != Polygons.end(); i++) {
      for(auto j = Polygons.begin(); j != Polygons.end(); j++) {
	if (i != j) {
	  i->CheckHit(*j);
	}
      }
    }

    for(auto i = Polygons.begin(); i != Polygons.end(); i++) {
      i->CheckWall(WIN_WIDTH, WIN_HEIGHT);
    }

    gfx_flush();
    usleep(LOOPTIME);
  }
}
