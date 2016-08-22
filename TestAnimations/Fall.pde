class Fall {
  int black = color(0, 0, 0);
  GradientRect[] gradientList = new GradientRect[5];
  Random rand = new Random();
  
  Fall() {
    
  }
  
  void display() {
    noStroke();
    fill(black);
    rect(0, 0, width, height);
    
    for (int i = 0; i < gradientList.length; i++) {
      GradientRect g = gradientList[i];
      if (g != null) {
         
      } else {
        gradientList[i] = new GradientRect(width, 0, width, 20, color(255, 0, 0), black, 20);
        setGradient(width, 0, 20, height, color(255, 0, 0), black, 20);
      }
      
    }
    setGradient(width, 0, width, 20, color(255, 0, 0), black, 20);
    
  }
  
  
  void setGradient(int x, int y, float w, float h, color c1, color c2, float segments) {
    noFill();
    for (float i = 0.; i < segments; i++) {
      float ratio = i/segments;
      color c = lerpColor(c1, c2, ratio);
      fill(c);
      rect(int(ratio * x), y, w/segments, h);
    }
  }
}

class GradientRect {
  int xOffset;
  int yOffset;
  int startColor;
  int endColor;
  int speed;
  
  GradientRect(int x, int y, int w, int h, int c1, int c2, int s) {
    xOffset = x;
    yOffset = y;
    startColor = c1;
    endColor = c2;
    speed = s;
  }
}