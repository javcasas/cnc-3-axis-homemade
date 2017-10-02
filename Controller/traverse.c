#include "stdlib.h"

int sign(signed long val) {
  if (val > 0) {
    return 1;
  } else if (val < 0) {
    return -1;
  } else {
    return 0;
  }
}

struct Coord {
  signed long x;
  signed long y;
  signed long z;
};

struct Coord pos = {0,0,0};

struct Coord source = {0,0,0};
struct Coord target = {0,0,0};

void move_x(int dir) { }
void move_y(int dir) { }
void move_z(int dir) { }

struct Coord traverse_along_x() {
  struct Coord trajectory = {
    target.x - source.x,
    target.y - source.y,
    target.z - source.z
  };
  int next_x = sign(trajectory.x);
  if (pos.x == target.x) {
    next_x = 0;
  }
  double proportion = (double)(pos.x - source.x + next_x) / (double)trajectory.x;
  //printf(" %f ", proportion);

  struct Coord expected_position = {
    source.x + trajectory.x * proportion,
    source.y + trajectory.y * proportion,
    source.z + trajectory.z * proportion
  };
  //printf("Expected ");
  //print_coord(expected_position);
  struct Coord error = {
    pos.x - expected_position.x,
    pos.y - expected_position.y,
    pos.z - expected_position.z
  };
  move_x(sign(trajectory.x));
  move_y(sign(error.y));
  move_z(sign(error.z));
  struct Coord movement = {
    next_x,
    sign(-error.y),
    sign(-error.z)
  };
  return movement;
}

void traverse_along_y() {
  
}

void traverse_along_z() {
  
}


void traverse_to_coords() {
  struct Coord trajectory = {
    target.x - source.x,
    target.y - source.y,
    target.z - source.z
  };
  if ((abs(trajectory.x >= trajectory.y)) && (abs(trajectory.x >= trajectory.z))) {
    traverse_along_x();
  } else if (abs(trajectory.y >= trajectory.z)) {
    traverse_along_y();
  } else {
    traverse_along_z();
  }
 
}

