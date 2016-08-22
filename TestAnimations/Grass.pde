class Grass {
  int x = 0;
 
  void display() {
    // sky
    background(color(30, 144, 255));
    
    float amt = (frameCount % 1000) * 0.001;
    
    if (amt == 0) {
      x += 10;
    } else if (x == width) {
      x = 0;
    }
    
    int side = 30;
    for (int i = 0; i < width; i += side*2) {
      fill(color(1, 166, 17));
      triangle(x + i, 0, x + i + side, side, x + i + side*2, 0);
    } //<>//
  }
}