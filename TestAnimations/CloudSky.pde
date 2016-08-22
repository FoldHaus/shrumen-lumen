class CloudSky {
  int x;
  CloudSky() {
    x = 0;
    noStroke();
  }
  
  void display() {
    background(color(135, 206, 250));

    x = (x+5) % width;

    for (int i = 0; i < width; i++) {
      if (x % 5 == 0) {
        for (int j = 0; j <= 3; j++) {
          drawSky(x + 180*j, x);
        }
      }
    }
  }
  
  void drawSky(float x, float y) {
    fill(color(255, 255, 255));
    rect(x, y, 100, 35, 15, 15, 15, 15);
  }
}