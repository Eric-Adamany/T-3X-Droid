
float PWMA = 0;
float PWMB = 0;
float PWMA_prev = 0;
float PWMB_prev = 0;
float temp_fb = 0;
float temp_lr = 0;

void motorDrive(float xRVal, float yRVal) {
  //Motor Driving -----------------------------------------------------------------------------------------------
  if (yRVal > 525) {
    temp_fb = map(yRVal, 520, 1023, 11, 100);
  } else if (yRVal < 440) {
    temp_fb = map(yRVal, 445, 0, -11, -100);
  } else {
    temp_fb = 0;
  }

  if (xRVal <= 450) {
    temp_lr = map(xRVal, 0, 450, 100, 0);
  } else if (xRVal >= 500) {
    temp_lr = map(xRVal, 500, 1023, 0, -100);
  } else {
    temp_lr = 0;
  }

  PWMA = constrain((temp_fb - temp_lr), -100, 100) * 0.1 + PWMA_prev * 0.9;
  PWMB = constrain((temp_fb + temp_lr), -100, 100) * 0.1 + PWMB_prev * 0.9;

  PWMA = constrain(PWMA, -100, 100);
  PWMB = constrain(PWMB, -100, 100);

  PWMA_prev = PWMA;
  PWMB_prev = PWMB;

  driver.setMotorAPower(PWMB);
  driver.setMotorBPower(PWMA);

  return;
}