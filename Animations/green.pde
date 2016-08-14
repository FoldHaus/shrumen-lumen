class Green {
  
  Green() {
    int[][] colorArr = {
      //blue to green
      {color(0, 255, 0), color(0, 0, 255)},
      //green to red
      {color(0, 0, 255), color(255, 0, 0)},
      //red to blue
      {color(255, 0, 0), color(0, 0, 255)}
    };
    
    int colorCount = 0;
  }
  
  void display() {
    int sections = 1000;
    int rangeCount = frameCount % sections;
    int colorCount = (int)(Math.floor(frameCount / sections));

    
    color startColor = color(0, 255, 0);
    color endColor = color(0, 0, 255);
    float amt = (frameCount%1000)*0.001;
    //println("Amount for Lerp: " + amt);
    color c = lerpColor(startColor, endColor, amt);
    fill(c);
    rect(0, 0, width, height);
  }
  
}