class BubblesGold {
  int[][] colorArr = {
    //green to dark green
    {color(255, 30, 5), color(255, 55, 5)},
    {color(255, 55, 5), color(255, 30, 5)},
    //dark green to black
    //{color(0,14,250), color(0,14,255)}
    //black to green
    //{color(13,25,43), color(7,249,162)}
  };
  
  int colorCount;
  int emptyEllipses;
  
  Bubble bubble = new Bubble(50, 50, 70, 70, color(10,10,10), 1, 50);
   
  BubblesGold() {
    colorCount = 0; 
  }
  
  void display() {
    noStroke();
    float amt = (frameCount%1000)*0.001;
    
    if(amt == 0) {
      colorCount++;
    }
    
    color startColor = colorArr[colorCount % colorArr.length][0];
    color endColor = colorArr[colorCount % colorArr.length][1];
    
    color c = lerpColor(startColor, endColor, amt);
    
    //Set the color on the canvas
    fill(c);
    rect(0, 0, width, height);
    
    //color ellipseStartColor = colorArr[(colorCount + 1) % colorArr.length][0];
    color ellipseStartColor = color(10,10,10);
    //color ellipseEndColor = colorArr[(colorCount + 1) % colorArr.length][1];
    color ellipseEndColor = color(20,20,20);
    //color ellipseColor = lerpColor(ellipseStartColor, ellipseEndColor, amt);
    color ellipseColor = color(255,255,255);
    
    fill(ellipseColor);
     
    int xOffset = bubble.getX() % width;
    int yOffset = bubble.getY() % height;
    
    ellipse(xOffset, yOffset, bubble.getWidth(), bubble.getHeight());

    if (yOffset < bubble.getWidth()) {
      ellipse(xOffset, yOffset + height, bubble.getWidth(), bubble.getHeight());
    }
    
    if (yOffset > height - bubble.getWidth()) {
      ellipse(xOffset, yOffset - height, bubble.getWidth(), bubble.getHeight());
    }
  }
}