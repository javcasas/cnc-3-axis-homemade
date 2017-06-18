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

int calc_direction (int x1, int x2, int prevx1, int prevx2) {
  if ((x1 == prevx1) && (x2 == prevx2)) {
    return 0
  }
}
void update_x() {
}

void update_y() {
}

void update_z() {
}

// the loop routine runs over and over again forever:
void loop() {
//  digitalWrite(led, digitalRead(9));   // turn the LED on (HIGH is the voltage level)
  //digitalWrite(led, HIGH);    // turn the LED off by making the voltage LOW
  //delay(50);               // wait for a second
  //digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  //delay(50);  // wait for a second
  digitalWrite(led, digitalRead(ystep1));
  //if (digitalRead(ystep1)) {
  //  
  //}
  /*if (digitalRead(ymin)) {
    move_y(1);
    delay(300);
  } else {
    halt();
    delay(100);
    move_y(-1);
    delay(10000);
  }*/
  //int limit = digitalRead(ymin);
  //digitalWrite(led, limit);
  //if (!limit) {
   // move_y(1);
    //move_x(-1);
  //  delay(1000);
  //  halt();
  //  delay(100);
  //  move_y(-1);
  //  delay(100);
  //}
  //halt();
  //delay(100);

}
