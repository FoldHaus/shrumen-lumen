class Pulse {
  int black = color(0, 0, 0);
  int c = 0;
  int[] colorArr = {
    color(7,249,162),
    color(231, 76, 60),
    color(230, 126, 34),
    color(243, 243, 21),
    color(0, 51, 204)
  };
  
  void display() {
    noStroke();
    fill(black);
    rect(0, 0, width, height);
    
    float amt = (frameCount%1000)*0.01;
    
    // loop back once the gradient has cleared the full width of the screen
    int xOffset = ((int)(amt * width) % (2 * width));
    setGradient(xOffset - width, 0, width, height, black, colorArr[c%colorArr.length]);
    if (xOffset == 0) {
      c++; 
    }
  }
  
  void setGradient(int x, int y, float w, float h, color c1, color c2) {
    noFill();
    // https://processing.org/examples/lineargradient.html
    for (int i = x; i <= x+w; i++) {
      float inter = map(i, x, x+w, 0, 1);
      color c = lerpColor(c1, c2, inter);
      stroke(c);
      line(i, y, i, y+h);
    }
  }
}