#ifndef CELL_H
#define CELL_H

#include "point.h"

class Cell {
 public:
  Cell();
  Cell(bool cell_alive, Point cell_coordinates);
  bool is_alive();
  void born();
  void die();
  int get_x();
  int get_y();
  void set_coordinates(Point cell_coordinates);
 private:
  Point coordinates;
  bool alive;
};

#endif
