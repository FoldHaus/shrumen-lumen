class Pulse {
  int black = color(0, 0, 0);
  int c1 = 0;
  int c2 = 1;
  int[] colorArr = {
    color(7,249,162),
    color(231, 76, 60),
    color(230, 126, 34),
    color(243, 243, 21),
    color(0, 51, 204)
  };
  int xOffset1;
  int xOffset2;
  
  void display() {
    noStroke();
    fill(black);
    rect(0, 0, width, height);
    
    float amt = (frameCount%1000)*0.01;
    xOffset1 = ((int)(amt * width) % (2*width));
    xOffset2 = (xOffset1 + width) % (2*width);
    setGradient(xOffset1 - width, 0, width, height, black, colorArr[c1%colorArr.length], 20.);
    setGradient(xOffset2 - width, 0, width, height, black, colorArr[c2%colorArr.length], 20.);
    if (xOffset1 == 0) {
      c1++; 
    }
    
    if (xOffset2 == 0) {
      c2++; 
    }
  }
  
  void setGradient(int x, int y, float w, float h, color c1, color c2, float segments) {
    noFill();
    for (float i = 0.; i < segments; i++) {
      float ratio = i/segments;
      color c = lerpColor(c1, c2, ratio);
      fill(c);
      rect(int(ratio * w)+x, y, w/segments, h);
    }
  }
}