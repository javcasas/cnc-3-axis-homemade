/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
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

int z1 = 2;
int z2 = 3;
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

signed long x_pos = 0;
signed long y_pos = 0;
signed long z_pos = 0;

signed long target_x_pos = 0;
signed long target_y_pos = 0;
signed long target_z_pos = 0;

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
  if        ((p1 == 0) && (p2 == 0) && (c1 == 0) && (c2 == 1)) {
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
  x_pos = x_pos + dir;
  prev_x1 = digitalRead(xstep1);
  prev_x2 = digitalRead(xstep2);
}

void update_y() {
  int dir = calc_direction(prev_y1, prev_y2, digitalRead(ystep1), digitalRead(ystep2));
  y_pos = y_pos + dir;
  prev_y1 = digitalRead(ystep1);
  prev_y2 = digitalRead(ystep2);
}

void update_z() {
  int dir = calc_direction(prev_z1, prev_z2, digitalRead(zstep1), digitalRead(zstep2));
  z_pos = z_pos + dir;
  prev_z1 = digitalRead(zstep1);
  prev_z2 = digitalRead(zstep2);
}

#define MODE_HOME_Y 1
#define MODE_HOME_Y_RETURN 6
#define MODE_END 10

int mode = MODE_HOME_Y;
int counter = 0;


// the loop routine runs over and over again forever:
void loop() {
  counter = counter + 1;
  if (counter > 9) {
    counter = 0;
  }
  update_x();
  update_y();
  update_z();

  if (mode == MODE_HOME_Y) {
    digitalWrite(led, counter % 2);
    if (digitalRead(ymin)) {
      move_y(1);
    } else {
      move_y(0);
      mode = MODE_HOME_Y_RETURN;
    }
  } else if (mode == MODE_HOME_Y_RETURN) {
    digitalWrite(led, counter % 2);
    if (!digitalRead(ymin)) {
      move_y(-1);
    } else {
      move_y(0);
      mode = MODE_END;
    }

  }
  else if (mode == MODE_END) {
    digitalWrite(led, true);
    halt();
  }

  delay(100);
}
