class Sweep {
  int black = color(0, 0, 0);
  int[][] colorArr = {
    //red to pink
    {color(255, 0, 0), color(233, 0, 50)},
    //pink to purple
    {color(233, 0, 50), color(233, 0, 255)},
    //purple to blue
    {color(233, 0, 255), color(0, 0, 255)},
    //blue to purple 
    {color(0, 0, 255), color(233, 0, 255)},
    //pruple to pink
    {color(233, 0, 255), color(233, 0, 50)},
    //pink to red
    {color(233, 0, 50), color(255, 0, 0)},
  };
  int colorCount = 0;
  float incrementAmt = 0.1;
  float y, yOld;
  
  void display() {
    noStroke();
    fill(black);
    rect(0, 0, width, height);
    
    float amt = (y/float(height));

    color startColor = colorArr[colorCount % colorArr.length][0];
    color endColor = colorArr[colorCount % colorArr.length][1];
    color c = lerpColor(startColor, endColor, amt);
    
    
    float yCoord = y - height;
    setGradient(0, yCoord, width, height, lerpColor(c, black, .5), c);
    if (yCoord < height/2) {
      setGradient(0, yCoord + height, width, height, lerpColor(c, black, .5), c);
    }
    
    if (yCoord > height) {
      setGradient(0, yCoord - height, width, height, lerpColor(c, black, .5), c);
    }
    yOld = y;
    y = (((y+incrementAmt)) % height);
    
    if(abs(y - yOld) > incrementAmt * 2) {
      colorCount++;
    }
  }
  
  void setGradient(int x, float y, float w, float h, color c1, color c2) {
    noFill();
    // https://processing.org/examples/lineargradient.html
    for (int i = floor(y); i <= y+h; i++) {
      float inter = map(i, y, y+h, 0, 1);
      color c = lerpColor(c1, c2, inter);
      stroke(c);
      line(x, i, x+w, i);
    }
  }
}