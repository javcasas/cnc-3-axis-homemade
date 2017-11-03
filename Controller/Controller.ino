/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
#include "types.h"

int led = 13;

int x1 = 6;
int x2 = 7;
int xmin = 8;
int xmax = 9;
int xstep1 = 10;
int xstep2 = 11;

int y1 = 4;
int y2 = 5;
int ymin = 8;
int ymax = 9;
int ystep1 = 10;
int ystep2 = 11;

int z1 = 6;
int z2 = 7;
int zmin = 8;
int zmax = 9;
int zstep1 = 10;
int zstep2 = 11;

void setup_motors() {
  halt();
  pinMode(x1, OUTPUT);
  pinMode(x2, OUTPUT);

  pinMode(y1, OUTPUT);
  pinMode(y2, OUTPUT);

  pinMode(z1, OUTPUT);
  pinMode(z2, OUTPUT);
  halt();
}

void setup_sensors() {
  pinMode(xmin, INPUT_PULLUP);
  pinMode(xmax, INPUT_PULLUP);
  pinMode(xstep1, INPUT_PULLUP);
  pinMode(xstep2, INPUT_PULLUP);

  pinMode(ymin, INPUT_PULLUP);
  pinMode(ymax, INPUT_PULLUP);
  pinMode(ystep1, INPUT_PULLUP);
  pinMode(ystep2, INPUT_PULLUP);

  pinMode(zmin, INPUT_PULLUP);
  pinMode(zmax, INPUT_PULLUP);
  pinMode(zstep1, INPUT_PULLUP);
  pinMode(zstep2, INPUT_PULLUP);
}


// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  setup_sensors();
  setup_motors();
  preload_servos();
  Serial.begin(9600);
}

void move_axis(int p1, int p2, int dir) {
  if (dir > 0) {
    digitalWrite(p1, HIGH);
    digitalWrite(p2, LOW);
  } else if (dir < 0) {
    digitalWrite(p1, LOW);
    digitalWrite(p2, HIGH);
  } else {
    digitalWrite(p1, LOW);
    digitalWrite(p2, LOW);
  }
}



void move_x(int dir) {
  move_axis(x1, x2, dir);
}

void move_y(int dir) {
  move_axis(y1, y2, dir);
}

void move_z(int dir) {
  move_axis(z1, z2, dir);
}

void halt() {
  move_x(0);
  move_y(0);
  move_z(0);
}

void update_servos() {
  update_x();
  update_y();
  update_z();
}


//signed long x_pos = 0;
//signed long y_pos = 0;
//signed long z_pos = 0;

//signed long target_x_pos = 0;
//signed long target_y_pos = 0;
//signed long target_z_pos = 0;

int prev_x1 = 0;
int prev_x2 = 0;
int prev_y1 = 0;
int prev_y2 = 0;
int prev_z1 = 0;
int prev_z2 = 0;


void preload_servos () {
  prev_x1 = digitalRead(xstep1);
  prev_x2 = digitalRead(xstep2);
  prev_y1 = digitalRead(ystep1);
  prev_y2 = digitalRead(ystep2);
  prev_z1 = digitalRead(zstep1);
  prev_z2 = digitalRead(zstep2);
}

int calc_direction (int p1, int p2, int c1, int c2) {
  if ((p1 == 0) && (p2 == 0) && (c1 == 0) && (c2 == 1)) {
    return 1;
  } else if ((p1 == 0) && (p2 == 1) && (c1 == 1) && (c2 == 1)) {
    return 1;
  } else if ((p1 == 1) && (p2 == 1) && (c1 == 1) && (c2 == 0)) {
    return 1;
  } else if ((p1 == 1) && (p2 == 0) && (c1 == 0) && (c2 == 0)) {
    return 1;
  } else if ((p1 == 1) && (p2 == 0) && (c1 == 1) && (c2 == 1)) {
    return -1;
  } else if ((p1 == 1) && (p2 == 1) && (c1 == 0) && (c2 == 1)) {
    return -1;
  } else if ((p1 == 0) && (p2 == 1) && (c1 == 0) && (c2 == 0)) {
    return -1;
  } else if ((p1 == 0) && (p2 == 0) && (c1 == 1) && (c2 == 0)) {
    return -1;
  } else {
    return 0;
  }
}

void update_x() {
  int dir = calc_direction(prev_x1, prev_x2, digitalRead(xstep1), digitalRead(xstep2));
  pos.x = pos.x + dir;
  prev_x1 = digitalRead(xstep1);
  prev_x2 = digitalRead(xstep2);
}

void update_y() {
  int dir = calc_direction(prev_y1, prev_y2, digitalRead(ystep1), digitalRead(ystep2));
  pos.y = pos.y + dir;
  prev_y1 = digitalRead(ystep1);
  prev_y2 = digitalRead(ystep2);
}

void update_z() {
  int dir = calc_direction(prev_z1, prev_z2, digitalRead(zstep1), digitalRead(zstep2));
  pos.z = pos.z + dir;
  prev_z1 = digitalRead(zstep1);
  prev_z2 = digitalRead(zstep2);
}

#define MODE_GO_TO_HOME_X 10
#define MODE_GO_TO_HOME_X_RETURN 11
#define MODE_GO_TO_END_X 12

#define MODE_GO_TO_HOME_Y 20
#define MODE_GO_TO_HOME_Y_RETURN 21
#define MODE_GO_TO_END_Y 22

#define MODE_GO_TO_HOME_Z 30
#define MODE_GO_TO_HOME_Z_RETURN 31
#define MODE_GO_TO_END_Z 32

#define MODE_STOP 50
#define MODE_GO_TO_COORDS 51

int mode = MODE_STOP;
int counter = 0;
int blink_pattern = 0b1111111111111111;

void go_to_home_x() {
  // Find the X start switch
  if (digitalRead(xmin)) {
     move_x(1);
   } else {
     move_x(0);
     mode = MODE_GO_TO_HOME_X_RETURN;
   }
}

void go_to_home_x_return() {
  if (digitalRead(xmin)) {
     mode = MODE_STOP;
     move_x(0);
   } else {
     move_x(-1);
   }
}

void go_to_home_y() {
  // Find the Y start switch
  if (digitalRead(ymin)) {
     move_y(1);
   } else {
     move_y(0);
     mode = MODE_GO_TO_HOME_Y_RETURN;
   }
}

void go_to_home_y_return() {
  if (digitalRead(ymin)) {
     mode = MODE_STOP;
     move_y(0);
   } else {
     move_y(-1);
   }
}

void go_to_home_z() {
  // Find the Z start switch
  if (digitalRead(zmin)) {
     move_z(1);
   } else {
     move_z(0);
     mode = MODE_GO_TO_HOME_Z_RETURN;
   }
}

void go_to_home_z_return() {
  if (digitalRead(zmin)) {
     mode = MODE_STOP;
     move_z(0);
   } else {
     move_z(-1);
   }
}

void stop_() {
  halt();
}

void traverse_along_x() {
  struct Coord trajectory = {
    target.x - source.x,
    target.y - source.y,
    target.z - source.z
  };
  signed long position_along_trajectory = pos.x - trajectory.x;
  double proportion = position_along_trajectory / trajectory.x;

  struct Coord expected_position = {
    source.x + position_along_trajectory,
    source.y + trajectory.y * proportion,
    source.z + trajectory.z * proportion
  };
  struct Coord error = {
    pos.x - expected_position.x,
    pos.y - expected_position.y,
    pos.z - expected_position.z
  };
  move_x(sign(trajectory.x));
  move_y(sign(error.y));
  move_z(sign(error.z));
}

void traverse_along_y() {
  
}

void traverse_along_z() {
  
}

struct Coord traverse (struct Coord source, struct Coord target, struct Coord pos);

void traverse_to_coords() {
  struct Coord movement = traverse(source, target, pos);
  move_x(movement.x);
  move_y(movement.y);
  move_z(movement.z); 
}

void blink_pattern_() {
  int should_blink = 0;
  counter = counter + 1;
  if (counter > 16) {
    counter = 0;
  }
  should_blink = (1 << counter) == 0;
  digitalWrite(led, should_blink);
}

int instructionBuffer[64];
int instructionBufferPosition = 0;
void processPort() {
  int readstuff = 0;
  readstuff = Serial.read();
  while (readstuff != -1) {
    instructionBuffer[instructionBufferPosition] = readstuff;
    instructionBufferPosition += 1;
    if (instructionBufferPosition > 63) {
      instructionBufferPosition = 63;
    }
    readstuff = Serial.read();
  }
  if (instructionBuffer[instructionBufferPosition - 1] == 10) {
    tryProcessInstruction();
    instructionBufferPosition = 0;
  }
}

int processerPosition = 0;
int instructionError = 0;

long parseInteger() {
  int result = 0;
  int ok = 0;
  while ((instructionBuffer[processerPosition] >= '0') && (instructionBuffer[processerPosition] <= '9')) {
    result = result * 10;
    result = result + instructionBuffer[processerPosition] - '0';
    processerPosition += 1;
    ok = 1;
  }
  if (!ok) {
    instructionError = 1;
  }
  return result;
}

void tryProcessInstruction() {
  int counter=0;
  processerPosition = 0;
  instructionError = 0;
  for(counter=0; counter<instructionBufferPosition; counter++) {
    Serial.write(instructionBuffer[counter]);
  }
  Serial.print("> ");
  if((instructionBuffer[0] == 's') &&
     (instructionBuffer[1] == 't') &&
     (instructionBuffer[2] == 'o') &&
     (instructionBuffer[3] == 'p')
    ) {
    stopCMD();
  } else if((instructionBuffer[0] == 'p') &&
     (instructionBuffer[1] == 'o') &&
     (instructionBuffer[2] == 's')
    ) {
    posCMD();
  } else if((instructionBuffer[0] == 's') &&
     (instructionBuffer[1] == 't') &&
     (instructionBuffer[2] == 'a')
    ) {
    staCMD();
  } else if((instructionBuffer[0] == 'm') &&
     (instructionBuffer[1] == 'o') &&
     (instructionBuffer[2] == 'v')
    ) {
    if (instructionBuffer[3] != ' ') {
      return errorCMD("No space after mov");
    }
    processerPosition = 4;
    long nx = parseInteger();
    if (instructionError) {
      return errorCMD("Invalid X coordinate");
    }
    if (instructionBuffer[processerPosition] != ' ') {
      return errorCMD("No space after X coord");
    }
    processerPosition += 1;
    long ny = parseInteger();
    if (instructionError) {
      return errorCMD("Invalid Y coordinate");
    }
    if (instructionBuffer[processerPosition] != ' ') {
      return errorCMD("No space after Y coord");
    }
    processerPosition += 1;
    long nz = parseInteger();
    if (instructionError) {
      return errorCMD("Invalid Z coordinate");
    }
    movCMD(nx, ny, nz);
  } else {
    unknownCMD();
  }
}

void stopCMD() {
  Serial.print("STOP\n");
}
void posCMD() {
  Serial.print("POSITION X:");
  Serial.print(pos.x);
  Serial.print(" Y:");
  Serial.print(pos.y);
  Serial.print(" Z:");
  Serial.print(pos.z);
  Serial.print("\n");
}
void movCMD(long nx, long ny, long nz) {
  Serial.print("MOVE TO X:");
  Serial.print(nx);
  Serial.print(" Y:");
  Serial.print(ny);
  Serial.print(" Z:");
  Serial.print(nz);
  Serial.print("\n");
}
void staCMD() {
  Serial.print("MODE:");
  printMode();
  Serial.print(" LIMITS:");
  Serial.print(" X:");
  printBool(digitalRead(xmin));
  printBool(digitalRead(xmax));
  Serial.print(" Y:");
  printBool(digitalRead(ymin));
  printBool(digitalRead(ymax));
  Serial.print(" Z:");
  printBool(digitalRead(zmin));
  printBool(digitalRead(zmax));
  Serial.print("\n");
}
void printBool(int x) {
  if (x) {
    Serial.print("T");
  } else {
    Serial.print("F");
  }
}

void printMode() {
  switch(mode) {
    case MODE_GO_TO_HOME_X: 
      Serial.print("MODE_GO_TO_HOME_X");
      return;
    case MODE_GO_TO_HOME_X_RETURN:
      Serial.print("MODE_GO_TO_HOME_X_RETURN");
      return;
    case MODE_GO_TO_HOME_Y:
      Serial.print("MODE_GO_TO_HOME_Y");
      return;
    case MODE_GO_TO_HOME_Y_RETURN:
      Serial.print("MODE_GO_TO_HOME_Y_RETURN");
      return;
    case MODE_GO_TO_HOME_Z:
      Serial.print("MODE_GO_TO_HOME_Z");
      return;
    case MODE_GO_TO_HOME_Z_RETURN:
      Serial.print("MODE_GO_TO_HOME_Z_RETURN");
      return;
    case MODE_STOP:
      Serial.print("MODE_STOP");
      return;
    case MODE_GO_TO_COORDS:
      Serial.print("MODE_GO_TO_COORDS");
      return;
    default: 
      Serial.print("Unknown(");
      Serial.print(mode);
      Serial.print(")");
      return;
  }

}

void unknownCMD() {
  Serial.print("UNKNOWN COMMAND\n");
}

void errorCMD(char error[]) {
  Serial.print("ERROR IN COMMAND:");
  Serial.print(error);
  Serial.print("\n");
}



// the loop routine runs over and over again forever:
void loop() {
  blink_pattern_();
  processPort();
  update_x();
  update_y();
  update_z();

  if (mode == MODE_GO_TO_HOME_X) {
    blink_pattern = 0b1111000011110000;
    go_to_home_x();
  } else if (mode == MODE_GO_TO_HOME_X_RETURN) {
    blink_pattern = 0b1100110011000011;
    go_to_home_x_return();
  } else if (mode == MODE_GO_TO_HOME_Y) {
    blink_pattern = 0b1111000011110000;
    go_to_home_y();
  } else if (mode == MODE_GO_TO_HOME_Y_RETURN) {
    blink_pattern = 0b1100110011001100;
    go_to_home_y_return();
  } else if (mode == MODE_GO_TO_HOME_Z) {
    blink_pattern = 0b1111000011110000;
    go_to_home_z();
  } else if (mode == MODE_GO_TO_HOME_Z_RETURN) {
    blink_pattern = 0b1100110011001100;
    go_to_home_z_return();
  } else if (mode == MODE_STOP) {
    blink_pattern = 0b1111111111111110;
    stop_();
  } else if (mode == MODE_GO_TO_COORDS) {
    blink_pattern = 0b1111111100000000;
    traverse_to_coords();
  } else {
  }
  delay(100);
}
