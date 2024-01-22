int temp_spin = 0;

void headSpin(int tLVal) {
  //Head Spin -----------------------------------------------------------------------------------------------
  if (tLVal < 425) {
    temp_spin  = map(tLVal, 425, 0, 0, 200);
    digitalWrite(aIN1, LOW);
    analogWrite(aIN2, temp_spin);
  } else if (tLVal > 515) {
    temp_spin  = map(tLVal, 515, 1023, 0, 200);
    analogWrite(aIN1, temp_spin);
    digitalWrite(aIN2, LOW);
  } else {
    temp_spin  = 0;
    digitalWrite(aIN1, LOW);
    digitalWrite(aIN2, LOW);
  }
  return;
}


