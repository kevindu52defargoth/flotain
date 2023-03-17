void turn(float degree, float sens) {
  setMotor1ByTension(sens*3);
  setMotor2ByTension(sens*3);
  delay(1860*degree/90);
  setMotor1ByTension(0);
  setMotor2ByTension(0);
}
