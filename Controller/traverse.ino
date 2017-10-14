#include "stdlib.h"
//#include "types.h"

int sign(signed long val) {
  if (val > 0) {
    return 1;
  } else if (val < 0) {
    return -1;
  } else {
    return 0;
  }
}


struct Coord pos = {0,0,0};

struct Coord source = {0,0,0};
struct Coord target = {0,0,0};

struct Coord traverse_along_x(struct Coord source, struct Coord target, struct Coord pos) {
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

  struct Coord expected_position = {
    source.x + trajectory.x * proportion,
    source.y + trajectory.y * proportion,
    source.z + trajectory.z * proportion
  };
  struct Coord error = {
    pos.x - expected_position.x,
    pos.y - expected_position.y,
    pos.z - expected_position.z
  };
  struct Coord movement = {
    next_x,
    sign(-error.y),
    sign(-error.z)
  };
  if (abs(error.y) > 1) {
    movement.x = 0;
  }
  if (abs(error.z) > 1) {
    movement.x = 0;
  }
  return movement;
}

struct Coord traverse_along_y(struct Coord source, struct Coord target, struct Coord pos) {
    struct Coord pos_ = {pos.y, pos.x, pos.z};
    struct Coord source_ = {source.y, source.x, source.z};
    struct Coord target_ = {target.y, target.x ,target.z};
    struct Coord movement_ = traverse_along_x(source_, target_, pos_);
    struct Coord movement = {movement_.y, movement_.x, movement_.z};
    return movement;
}

struct Coord traverse_along_z(struct Coord source, struct Coord target, struct Coord pos) {
    struct Coord pos_ = {pos.z, pos.y, pos.x};
    struct Coord source_ = {source.z, source.y, source.x};
    struct Coord target_ = {target.z, target.y ,target.x};
    struct Coord movement_ = traverse_along_x(source_, target_, pos_);
    struct Coord movement = {movement_.z, movement_.y, movement_.x};
    return movement;
}

struct Coord traverse(struct Coord source, struct Coord target, struct Coord pos) {
  struct Coord trajectory = {
    abs(target.x - source.x),
    abs(target.y - source.y),
    abs(target.z - source.z)
  };
  if ((trajectory.x >= trajectory.y) && (trajectory.x >= trajectory.z)) {
    return traverse_along_x(source, target, pos);
  } else if (trajectory.y >= trajectory.z) {
    return traverse_along_y(source, target, pos);
  } else {
    return traverse_along_z(source, target, pos);
  }
}

