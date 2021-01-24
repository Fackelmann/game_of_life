#ifndef GRID_H
#define GRID_H

#include <string>
#include "cell.h"
#include "point.h"

class Grid {
 public:
  Grid(int init_width, int init_height);
  Grid(std::string input_file_name);
  ~Grid();
  int get_width();
  int get_height();
  void play(float refresh_frequency_hz);
  Point& get_neighbor_coordinates(Point cell_coordinates);
  int get_cell_alive_neighbors(Cell& my_cell);
  void update_cell(Cell& my_cell);
  void update_grid();
  void print_grid();
  Cell** cells;
  Cell** successor_cells;
private:
  int iteration;
  int width;
  int height;
  bool _is_valid_coordinate(Point& point);
};

#endif
