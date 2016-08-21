class Sweep {
  int black = color(0, 0, 0);
  int[][] colorArr = {
    //blue to green
    {color(0, 0, 255), color(0, 255, 0)},
    //green to red
    {color(0, 255, 0), color(255, 0, 0)},
    //red to blue
    {color(255, 0, 0), color(0, 0, 255)}
  };
  int colorCount = 0;
  int y;
  
  void display() {
    noStroke();
    fill(black);
    rect(0, 0, width, height);
    
    float amt = float(y)/float(height);
    
    color startColor = colorArr[colorCount % colorArr.length][0];
    color endColor = colorArr[colorCount % colorArr.length][1];
    color c = lerpColor(startColor, endColor, amt);
    println(amt);
    
    y = (y+1) % height;
    
    if(y == 0) {
      colorCount++;
    }
    int yCoord = y - height;
    setGradient(0, yCoord, width, height, lerpColor(c, black, .5), c);
    if (yCoord < height/2) {
      setGradient(0, yCoord + height, width, height, lerpColor(c, black, .5), c);
    }
    
    if (yCoord > height) {
      setGradient(0, yCoord - height, width, height, lerpColor(c, black, .5), c);
    }
  }
  
  void setGradient(int x, int y, float w, float h, color c1, color c2) {
    noFill();
    // https://processing.org/examples/lineargradient.html
    for (int i = y; i <= y+h; i++) {
      float inter = map(i, y, y+h, 0, 1);
      color c = lerpColor(c1, c2, inter);
      stroke(c);
      line(x, i, x+w, i);
    }
  }
}