#include "stdio.h"
#include "traverse.c"

void print_coord(struct Coord c) {
    printf("(%ld, %ld, %ld)", c.x, c.y, c.z);
}

int run_test(char * name, int test()) {
    printf("\n>>>> Executing %s\n", name);
    int result = test();
    printf("\n>>>> Result %s: %s\n", name, result ? "ERROR" : "Success");
    return result;
}

int test_traverse_1() {
    source.x = 5;
    source.y = 2;
    source.z = 3;

    target.x = -10;
    target.y = 6;
    target.z = -1;

    pos = source;
    int expected_steps = abs(target.x - pos.x);
    printf("Expected steps: %d\n", expected_steps);
    int steps = 0;
    struct Coord increment;
    while ((pos.x != target.x) || (pos.y != target.y) || (pos.z != target.z))
    {
        //printf("Position: ");
        //print_coord(pos);
        increment = traverse_along_x();
        //printf("Increment: ");
        //print_coord(increment);
        pos.x += increment.x;
        pos.y += increment.y;
        pos.z += increment.z;
        steps += 1;
        
    }
    printf("Done in %d steps.", steps);
    return expected_steps != steps;
}

int test_traverse_2() {
    source.x = -5;
    source.y = 2;
    source.z = 3;

    target.x = 10;
    target.y = 6;
    target.z = -1;

    pos = source;
    int expected_steps = abs(target.x - pos.x);
    printf("Expected steps: %d\n", expected_steps);
    int steps = 0;
    struct Coord increment;
    while ((pos.x != target.x) || (pos.y != target.y) || (pos.z != target.z))
    {
        //printf("Position: ");
        //print_coord(pos);
        increment = traverse_along_x();
        //printf("Increment: ");
        //print_coord(increment);
        pos.x += increment.x;
        pos.y += increment.y;
        pos.z += increment.z;
        steps += 1;
        
    }
    printf("Done in %d steps.", steps);
    return expected_steps != steps;
}


int main() {
    run_test("test_traverse_1", test_traverse_1);
    run_test("test_traverse_2", test_traverse_2);
    return 0;
}
