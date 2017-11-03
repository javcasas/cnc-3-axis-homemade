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
