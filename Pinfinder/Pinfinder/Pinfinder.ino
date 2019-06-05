#define MIN_PIN 1
#define MAX_PIN 40

void setup() {
  // initialize the digital pin as an output.
  int i;
  for(i=MIN_PIN; i<=MAX_PIN; i++) {
    pinMode(i, INPUT_PULLUP);
  }
  Serial.begin(9600);
  Serial.write("PINFINDER v0.1 ready\n");
  printHeading();
}

unsigned long current;
int lines = 0;
void loop() {
  int i;
  unsigned long nbits = readBits();
  if (current != nbits) {
    if(lines > 5) { 
      printHeading();
      lines = 0;
    }
    lines = lines + 1;
    printBits(nbits);
    current = nbits;
  }
  delay(50);
}

void printBits(unsigned long bits) {
  unsigned long i;
  for(i=MIN_PIN; i<=MAX_PIN; i++) {
    printBool((((unsigned long)1 << i) & bits) != 0);
    if(i%5 == 0) {
      Serial.print(" ");
    }
  }
  Serial.print("\n");
}

unsigned long readBits() {
  unsigned long result = 0;
  unsigned long i;
  unsigned long val;
  for(i=MIN_PIN; i<=MAX_PIN; i++) {
    val = digitalRead(i) != 0; 
    result = result | (val << i);
  }
  return result;
}

void printHeading() {
  int i=0;
  Serial.print("\n");
  for(i=MIN_PIN; i<=MAX_PIN; i++) {
    if(i%5 == 0) {
      Serial.print(i);
    } else {
      Serial.print(" ");
    }
  }
  Serial.print("\n");
  for(i=MIN_PIN; i<=MAX_PIN; i++) {
    Serial.print("-");
    if(i%5 == 0) {
      Serial.print(" ");
    }

  }
  Serial.print("\n");
}

void printBool(int x) {
  if(x) {
    Serial.print("T");
  } else {
    Serial.print("F");
  }
}
