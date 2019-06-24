struct Action parseAction(int buffer[], int bufLength) {
  struct Action result = {ACTION_UNKNOWN, {0, 0, 0}};
  if((buffer[0] == 't') &&
     (buffer[1] == 's') &&
     (buffer[2] == 't')
  ) {
    result.type = ACTION_TEST;
  } else if((buffer[0] == 's') &&
     (buffer[1] == 't') &&
     (buffer[2] == 'a')
  ) {
    result.type = ACTION_STATUS;
  } else if((buffer[0] == 'p') &&
     (buffer[1] == 'o') &&
     (buffer[2] == 's')
  ) {
    result.type = ACTION_POSITION;
  } else if((buffer[0] == 'c') &&
     (buffer[1] == 'a') &&
     (buffer[2] == 'l')
  ) {
    result.type = ACTION_CALIBRATE;
  } else if((buffer[0] == 's') &&
     (buffer[1] == 't') &&
     (buffer[2] == 'o') &&
     (buffer[3] == 'p')
  ) {
    result.type = ACTION_STOP;
  }
  return result;
}
/*int instructionBuffer[64];
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
  } else if((instructionBuffer[0] == 't') &&
     (instructionBuffer[1] == 's') &&
     (instructionBuffer[2] == 't')
    ) {
    tstCMD();
  } else if((instructionBuffer[0] == 'c') &&
     (instructionBuffer[1] == 'a') &&
     (instructionBuffer[2] == 'l')
    ) {
    calCMD();
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
  mode = MODE_STOP;
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
  Serial.print("\n");\
  target.x = nx;
  target.y = ny;
  target.z = nz;
  mode = MODE_GO_TO_COORDS;
}

void staCMD() {
  Serial.print("MODE:");
  printMode();
  Serial.print(" LIMITS:");
  Serial.print(" X:");
  printBool(digitalRead(PIN_X_LIMIT_1));
  printBool(digitalRead(PIN_X_LIMIT_2));
  Serial.print(" Y:");
  printBool(digitalRead(PIN_Y_LIMIT_1));
  printBool(digitalRead(PIN_Y_LIMIT_2));
  Serial.print(" Z:");
  printBool(digitalRead(PIN_Z_LIMIT_1));
  printBool(digitalRead(PIN_Z_LIMIT_2));
  Serial.print("\n");
}

void calCMD() {
  Serial.print("CALIBRATE");
  mode = MODE_GO_TO_HOME_X;
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

void tstCMD() {
  Serial.print("TEST\n");
  mode = MODE_TEST;
}

void mode_test() {
  static boolean p_x_limit_1 = 0;
  static boolean p_x_limit_2 = 0;
  static boolean p_y_limit_1 = 0;
  static boolean p_y_limit_2 = 0;
  static boolean p_z_limit_1 = 0;
  static boolean p_z_limit_2 = 0;

  static boolean p_x_encoder_1 = 0;
  static boolean p_x_encoder_2 = 0;
  static boolean p_y_encoder_1 = 0;
  static boolean p_y_encoder_2 = 0;
  static boolean p_z_encoder_1 = 0;
  static boolean p_z_encoder_2 = 0;

  if (
    p_x_limit_1 != digitalRead(PIN_X_LIMIT_1) ||
    p_x_limit_2 != digitalRead(PIN_X_LIMIT_2) ||
    p_y_limit_1 != digitalRead(PIN_Y_LIMIT_1) ||
    p_y_limit_2 != digitalRead(PIN_Y_LIMIT_2) ||
    p_z_limit_1 != digitalRead(PIN_Z_LIMIT_1) ||
    p_z_limit_2 != digitalRead(PIN_Z_LIMIT_2) ||
    p_x_encoder_1 != digitalRead(PIN_X_ENCODER_1) ||
    p_x_encoder_2 != digitalRead(PIN_X_ENCODER_2) ||
    p_y_encoder_1 != digitalRead(PIN_Y_ENCODER_1) ||
    p_y_encoder_2 != digitalRead(PIN_Y_ENCODER_2) ||
    p_z_encoder_1 != digitalRead(PIN_Z_ENCODER_1) ||
    p_z_encoder_2 != digitalRead(PIN_Z_ENCODER_2)
  ) {
    Serial.print(" X-LIMITS:");
    printBool(digitalRead(PIN_X_LIMIT_1));
    printBool(digitalRead(PIN_X_LIMIT_2));
    Serial.print(" X-ENCODER:");
    printBool(digitalRead(PIN_X_ENCODER_1));
    printBool(digitalRead(PIN_X_ENCODER_2));

    Serial.print(" Y-LIMITS:");
    printBool(digitalRead(PIN_Y_LIMIT_1));
    printBool(digitalRead(PIN_Y_LIMIT_2));
    Serial.print(" Y-ENCODER:");
    printBool(digitalRead(PIN_Y_ENCODER_1));
    printBool(digitalRead(PIN_Y_ENCODER_2));

    Serial.print(" Z-LIMITS:");
    printBool(digitalRead(PIN_Z_LIMIT_1));
    printBool(digitalRead(PIN_Z_LIMIT_2));
    Serial.print(" Z-ENCODER:");
    printBool(digitalRead(PIN_Z_ENCODER_1));
    printBool(digitalRead(PIN_Z_ENCODER_2));
    Serial.print("\n");
  }
  p_x_limit_1 = digitalRead(PIN_X_LIMIT_1);
  p_x_limit_2 = digitalRead(PIN_X_LIMIT_2);
  p_y_limit_1 = digitalRead(PIN_Y_LIMIT_1);
  p_y_limit_2 = digitalRead(PIN_Y_LIMIT_2);
  p_z_limit_1 = digitalRead(PIN_Z_LIMIT_1);
  p_z_limit_2 = digitalRead(PIN_Z_LIMIT_2);

  p_x_encoder_1 = digitalRead(PIN_X_ENCODER_1);
  p_x_encoder_2 = digitalRead(PIN_X_ENCODER_2);
  p_y_encoder_1 = digitalRead(PIN_Y_ENCODER_1);
  p_y_encoder_2 = digitalRead(PIN_Y_ENCODER_2);
  p_z_encoder_1 = digitalRead(PIN_Z_ENCODER_1);
  p_z_encoder_2 = digitalRead(PIN_Z_ENCODER_2);
}*/
