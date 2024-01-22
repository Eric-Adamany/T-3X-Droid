//Head Control -----------------------------------------------------------------------------------------------
#define SERVOMINR 240
#define SERVOMAXR 550
#define SERVOMINL 140
#define SERVOMAXL 435

//Servo setup
int tiltF;
int tiltB;
int tiltL;
int tiltR;
int pulselengthL;
int pulselengthR;
int pulselengthL_prev = 287;
int pulselengthR_prev = 395;

int fL;
int bR;

void headTilt(int xLVal, int yLVal) {
  if (xLVal < 530 && xLVal > 440) {
    tiltL = 1;
    tiltR = 1;
  } else {
    tiltL = map(xLVal, 0, 1023, -70, 70);
    tiltR = tiltL;
  }

  if (yLVal < 565 && yLVal > 470) {
    tiltF = 1;
    tiltB = 1;
  } else {
    tiltF = map(yLVal, 1023, 0, -100, 100);
    tiltB = tiltF;
  }

  fL = constrain((tiltF + tiltL), -100, 100);
  bR = constrain((tiltB - tiltR), -100, 100);

  pulselengthL = map(fL, -100, 100, SERVOMAXL, SERVOMINL) * 0.05 + pulselengthL_prev * 0.95;
  pulselengthR = map(bR, -100, 100, SERVOMINR, SERVOMAXR) * 0.05 + pulselengthR_prev * 0.95;

  pulselengthL_prev = pulselengthL;
  pulselengthR_prev = pulselengthR;

  myServo.setPWM(13, 0, pulselengthL);
  myServo.setPWM(12, 0, pulselengthR);

  return;
}