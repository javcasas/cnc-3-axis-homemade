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
