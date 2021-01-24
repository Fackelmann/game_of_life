#include "cell.h"

Cell::Cell():coordinates(), alive(false) {
}

Cell::Cell (bool cell_alive, Point cell_coordinates):coordinates(cell_coordinates), alive(cell_alive) {
}

bool Cell::is_alive() {
  return alive;
}

void Cell::born() {
  alive = true;
}

void Cell::die() {
  alive = false;
}

int Cell::get_x() {
  return coordinates.x;
}

int Cell::get_y() {
  return coordinates.y;
}

void Cell::set_coordinates(Point cell_coordinates) {
  coordinates = cell_coordinates;
}
