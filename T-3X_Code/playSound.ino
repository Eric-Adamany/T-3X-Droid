void phrase1() {
  int k = random(500, 800);
  for (int i = 0; i <= random(100, 700); i++) {
    tone(speakerPin, k + (-i));
    delay(random(.9, 2));
  }
  for (int i = 0; i <= random(100, 500); i++) {
    tone(speakerPin, k + (i));
    delay(random(.9, 2));
  }
}

void phrase2() {
  int k = random(500, 800);
  for (int i = 0; i <= random(100, 700); i++) {
    tone(speakerPin, k + (i));
    delay(random(.9, 2));
  }
  for (int i = 0; i <= random(100, 500); i++) {
    tone(speakerPin, k + (-i));
    delay(random(.9, 2));
  }
}

void playSound() {
  int K = 700;
  switch (random(1, 7)) {
    case 1: phrase1(); break;
    case 2: phrase2(); break;
    case 3: phrase1(); phrase2(); break;
    case 4: phrase2(); phrase1(); phrase2(); break;
  }
  for (int i = 0; i <= random(3, 9); i++) {
    tone(speakerPin, K + random(-800, 100));
    delay(random(70, 170));
    noTone(speakerPin);
    delay(random(0, 30));
  }
  noTone(speakerPin);
}
