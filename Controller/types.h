struct Coord {
  signed long x;
  signed long y;
  signed long z;
};

extern struct Coord pos;

extern struct Coord source;
extern struct Coord target;

int sign(signed long val);

struct Coord traverse(struct Coord source, struct Coord target, struct Coord pos);

struct Action {
  int type;
  struct Coord pos;
};

#define ACTION_STOP 0
#define ACTION_POSITION 1
#define ACTION_STATUS 2
#define ACTION_TEST 3
#define ACTION_CALIBRATE 4
#define ACTION_MOVE 5
#define ACTION_MOVE_X 6
#define ACTION_MOVE_Y 7
#define ACTION_MOVE_Z 8
#define ACTION_UNKNOWN 1000
