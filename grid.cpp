#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include <thread>
#include <chrono>
#include "cell.h"
#include "grid.h"


Grid::Grid (int init_width, int init_height) {
  width = init_width;
  height = init_height;
  iteration = 0;
  cells = new Cell*[height];
  for(int i = 0; i < height; ++i) {
    cells[i] = new Cell[width];
  }
  successor_cells = new Cell*[height];
  for(int i = 0; i < height; ++i)
    successor_cells[i] = new Cell[width];
  
}

Grid::Grid (std::string input_file_name) {
  iteration = 0;
  std::ifstream file(input_file_name);
  if (file.is_open()) {
    std::string line;
    getline(file, line);
    width = std::stoi(line);
    getline(file, line);
    height = std::stoi(line);
    cells = new Cell*[height];
    for(int i = 0; i < height; ++i)
      cells[i] = new Cell[width];
    successor_cells = new Cell*[height];
    for(int i = 0; i < height; ++i)
      successor_cells[i] = new Cell[width];
    int row = 0;
    while (getline(file, line)) {
      for (int col = 0; col < width; ++col) {
	cells[row][col].set_coordinates(Point(col, row));
	if (line[col] == '+') {
	  cells[row][col].born();
	}
      }
      row = row + 1;
    }
    file.close();
  } else {
    std::cout << "File " << input_file_name << " does not exist.";
  }
  
}

Grid::~Grid() {
  for(int i = 0; i < height; ++i) {
    delete[] cells[i];
    delete[] successor_cells[i];
  }
  delete[] cells;
  delete[] successor_cells;
}

int Grid::get_height() {
  return height;
}

int Grid::get_width() {
  return width;
}

int Grid::get_cell_alive_neighbors(Cell& my_cell) {
  int result = 0;
  for(int row=-1; row<2; ++row) {
    for(int col=-1; col<2; ++col) {
      if (row != 0 || col != 0) {
	int x_coord = my_cell.get_x()+col;
	int y_coord = my_cell.get_y()+row;
	Point check_point = Point(x_coord, y_coord);
	if (_is_valid_coordinate(check_point) && cells[y_coord][x_coord].is_alive() == true){
	  result++;
	}
      }
    }
  }
  return result;
}

bool Grid::_is_valid_coordinate(Point& point) {
  int x_coord = point.x;
  int y_coord = point.y;
  return x_coord >= 0 && y_coord >= 0 && x_coord < width && y_coord < height;
}

void Grid::update_cell(Cell& my_cell) {
  int live_neighbors = get_cell_alive_neighbors(my_cell);
  int x_coord = my_cell.get_x();
  int y_coord = my_cell.get_y();
  Cell& successor_cell = successor_cells[y_coord][x_coord];
  successor_cell.set_coordinates(Point(x_coord, y_coord));
  if (my_cell.is_alive()) {
    successor_cell.born();
    if (live_neighbors < 2) {
      successor_cell.die();
    } else if (live_neighbors > 3) {
      successor_cell.die();
    } else {
      successor_cell.born();
    }
  } else {
    successor_cell.die();
    if (live_neighbors == 3) {
      successor_cell.born();
    }
  }
}

void Grid::update_grid() {
  for(int row = 0; row < height; ++row) {
    for(int col = 0; col < width; ++col) {
      update_cell(cells[row][col]);
    }
  }
  // Making the data in the successor array the primary data
  std::swap(cells, successor_cells);
  ++iteration;
}

void Grid::print_grid() {
  std::cout << "Iteration: " << iteration << '\n';
  for(int row = 0; row < height; ++row) {
    for(int col = 0; col < width; ++col) {
      if (cells[row][col].is_alive() == true) {
	std::cout << '+';
      } else {
	std::cout << '.';
      }
    }
    std::cout << '\n';
  }
}

void Grid::play(float refresh_frequency_hz) {
  int sleep_time_ms = 1/refresh_frequency_hz*1000;
  while (true) {
    system("clear");
    print_grid();
    update_grid();
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time_ms));
  }
}
