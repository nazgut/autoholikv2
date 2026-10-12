// check if the touched position is in the map for 800x480 display
int positionTouch(int x1Button, int y1Button, int x2Button, int y2Button, TSPoint p) {
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  //because TFT control pins
  digitalWrite(A3, HIGH);
  digitalWrite(A2, HIGH);

  int x = map(p.y, TS_MAXX, TS_MINX, 0, 800);  // Map to 800px width
  int y = map(p.x, TS_MAXY, TS_MINY, 0, 480);  // Map to 480px height

  if (x >= x1Button && x <= x2Button && y >= y1Button && y <= y2Button)return (1);
  else return (0);
}

void waitForTouch()
{
  TSPoint p = ts.getPoint();
  while (p.z < ts.pressureThreshhold) p = ts.getPoint();
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
}
