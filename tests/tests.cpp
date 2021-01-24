#define CATCH_CONFIG_MAIN
#include <iostream>
#include "catch.hpp"
#include "../cell.h"
#include "../grid.h"
#include "../point.h"

TEST_CASE("Point") {
  Point point;
  REQUIRE( point.x == 0);
  REQUIRE( point.y == 0);
  Point point2{3, 4};
  REQUIRE( point2.x == 3);
  REQUIRE( point2.y == 4);
}

TEST_CASE("Cell") {
  Point point;
  bool alive{false};
  Cell cell(alive, point);
  REQUIRE( cell.is_alive() == false);
  REQUIRE( cell.get_x() == 0);
  REQUIRE( cell.get_y() == 0);
}

TEST_CASE("Grid") {
  Grid grid{10,20};
  REQUIRE( grid.get_width() == 10 );
  REQUIRE( grid.get_height() == 20);
  for(int i = 0; i < grid.get_height(); ++i)
    for(int j = 0; j < grid.get_width(); ++j)
      REQUIRE( grid.cells[i][j].is_alive() == false );  
}

TEST_CASE("Grid from file") {
  Grid grid{"tests/file_test.txt"};
  REQUIRE( grid.get_width() == 6 );
  REQUIRE( grid.get_height() == 6);
  REQUIRE( grid.cells[2][2].is_alive() == true);
  REQUIRE( grid.cells[2][2].get_x() == 2);
  REQUIRE( grid.cells[2][2].get_y() == 2);
  REQUIRE( grid.cells[2][5].is_alive() == false);
  REQUIRE( grid.cells[2][5].is_alive() == false);
  REQUIRE( grid.get_cell_alive_neighbors(grid.cells[2][2]) == 4);
  REQUIRE( grid.get_cell_alive_neighbors(grid.cells[0][0]) == 0);
  REQUIRE( grid.get_cell_alive_neighbors(grid.cells[5][5]) == 0);
  grid.update_cell(grid.cells[3][1]);
  grid.update_cell(grid.cells[3][2]);
  //std::cout << "alive?: " << grid.cells[3][1].is_alive() << " Live Neigh: " << grid.get_cell_alive_neighbors(grid.cells[3][1]) << '\n';
  //std::cout << "alive?: " << grid.successor_cells[3][1].is_alive() << '\n';
  REQUIRE( grid.successor_cells[3][1].is_alive() == true);
  REQUIRE( grid.successor_cells[3][2].is_alive() == false);
  REQUIRE( grid.cells[3][1].is_alive() == true);
  REQUIRE( grid.cells[3][2].is_alive() == true);
  grid.update_grid();
  REQUIRE( grid.cells[3][1].is_alive() == true);
  REQUIRE( grid.cells[3][2].is_alive() == false);
  grid.update_grid();
  REQUIRE( grid.cells[3][1].is_alive() == true);
  REQUIRE( grid.cells[3][2].is_alive() == true);
}
