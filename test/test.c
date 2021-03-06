#include "stdio.h"
#include <criterion/criterion.h>
#include "../Controller/types.h"
#include "../Controller/traverse.ino"
#include "../Controller/comms_parser.ino"

Test(Main, test_traverse_1_along_x) {
    source.x = 5;
    source.y = 2;
    source.z = 3;

    target.x = -10;
    target.y = 6;
    target.z = -1;

    pos = source;
    struct Coord increment = traverse(source, target, pos);
    cr_expect(increment.x == -1, "increment x is -1");
    cr_expect(increment.y == 0, "increment y is 0");
    cr_expect(increment.z == -1, "increment z is -1");
}

Test(Main, test_traverse_1_along_x_out_of_position_1) {
    source.x = 5;
    source.y = 0;
    source.z = 0;

    target.x = -10;
    target.y = 0;
    target.z = 0;

    pos = source;
    pos.y = 2;
    struct Coord increment = traverse(source, target, pos);
    cr_expect(increment.x == 0, "increment x is 0");
    cr_expect(increment.y == -1, "increment y is -1");
    cr_expect(increment.z == 0, "increment z is 0");
}

Test(Main, test_traverse_1_along_x_out_of_position_2) {
    source.x = 5;
    source.y = 0;
    source.z = 0;

    target.x = -10;
    target.y = 0;
    target.z = 0;

    pos = source;
    pos.z = -2;
    struct Coord increment = traverse(source, target, pos);
    cr_expect(increment.x == 0, "increment x is 0");
    cr_expect(increment.y == 0, "increment y is 0");
    cr_expect(increment.z == 1, "increment z is 1");
}

Test(Main, test_traverse_2_along_y) {
    source.x = 2;
    source.y = 5;
    source.z = 3;

    target.x = 6;
    target.y = -10;
    target.z = -1;

    pos = source;
    struct Coord increment = traverse(source, target, pos);
    cr_expect(increment.x == 0, "increment x is 0");
    cr_expect(increment.y == -1, "increment y is -1");
    cr_expect(increment.z == -1, "increment z is -1");
}

Test(Main, test_traverse_3_along_z) {
    source.x = 2;
    source.y = 3;
    source.z = 5;

    target.x = 6;
    target.y = -1;
    target.z = -10;

    pos = source;
    struct Coord increment = traverse(source, target, pos);
    cr_expect(increment.x == 0, "increment x is 0");
    cr_expect(increment.z == -1, "increment z is -1");
    cr_expect(increment.y == -1, "increment y is -1");
}

Test(Main, test_traverse_x_1) {
    source.x = 5;
    source.y = 2;
    source.z = 3;

    target.x = -10;
    target.y = 6;
    target.z = -1;

    pos = source;
    struct Coord increment = traverse_along_x(source, target, pos);
    cr_expect(increment.x == -1, "increment x is -1");
    cr_expect(increment.y == 0, "increment y is 0");
    cr_expect(increment.z == -1, "increment z is -1");
}

Test(Main, test_traverse_x_multiple_1) {
    source.x = 5;
    source.y = 2;
    source.z = 3;

    target.x = -10;
    target.y = 6;
    target.z = -1;

    pos = source;
    int expected_steps = abs(target.x - pos.x);
    int steps = 0;
    struct Coord increment;
    while ((pos.x != target.x) || (pos.y != target.y) || (pos.z != target.z))
    {
        increment = traverse_along_x(source, target, pos);
        pos.x += increment.x;
        pos.y += increment.y;
        pos.z += increment.z;
        steps += 1;
        
    }
    cr_expect(expected_steps == steps, "Expected steps is the same as taken steps");
}

Test(Main, test_traverse_x_multiple_2) {
    source.x = -5;
    source.y = 2;
    source.z = 3;

    target.x = 10;
    target.y = 6;
    target.z = -1;

    pos = source;
    int expected_steps = abs(target.x - pos.x);
    int steps = 0;
    struct Coord increment;
    while ((pos.x != target.x) || (pos.y != target.y) || (pos.z != target.z))
    {
        increment = traverse_along_x(source, target, pos);
        pos.x += increment.x;
        pos.y += increment.y;
        pos.z += increment.z;
        steps += 1;
        
    }
    cr_expect(expected_steps == steps, "Expected steps is the same as taken steps");
}

Test(Main, test_parser_tst) {
  int buffer[] = {'t', 's', 't'};
  struct Action act = parseAction(buffer, 3);
  struct Action expected = { ACTION_TEST };
  cr_expect(act.type == expected.type, "tst");
}

Test(Main, test_parser_sta) {
  int buffer[] = {'s', 't', 'a'};
  struct Action act = parseAction(buffer, 3);
  struct Action expected = { ACTION_STATUS };
  cr_expect(act.type == expected.type, "sta");
}

Test(Main, test_parser_pos) {
  int buffer[] = {'p', 'o', 's'};
  struct Action act = parseAction(buffer, 3);
  struct Action expected = { ACTION_POSITION };
  cr_expect(act.type == expected.type, "pos");
}

Test(Main, test_parser_cal) {
  int buffer[] = {'c', 'a', 'l'};
  struct Action act = parseAction(buffer, 3);
  struct Action expected = { ACTION_CALIBRATE };
  cr_expect(act.type == expected.type, "cal");
}

Test(Main, test_parser_stop) {
  int buffer[] = {'s', 't', 'o', 'p'};
  struct Action act = parseAction(buffer, 4);
  struct Action expected = { ACTION_STOP };
  cr_expect(act.type == expected.type, "stop");
}

Test(Main, test_parser_unknown) {
  int buffer[] = {'a', 's', 'd', 'f'};
  struct Action act = parseAction(buffer, 4);
  struct Action expected = { ACTION_UNKNOWN };
  cr_expect(act.type == expected.type, "unknown");
}
