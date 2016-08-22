class Bubbles {
  int[][] colorArr = {
    //green to dark green
    {color(255,0,255), color(120,0,255)},
    {color(120,0,255), color(255,0,255)},
    //dark green to black
    //{color(0,14,250), color(0,14,255)}
    //black to green
    //{color(13,25,43), color(7,249,162)}
  };
  
  int colorCount;
  int emptyEllipses;
  
  Bubble bubble = new Bubble(50, 50, 70, 70, color(10,10,10), 1, 50);
   
  Bubbles() {
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

class Bubble extends Circle {
  int speed;
  int lowerBound;
  int upperBound;
  int direction;
  float weight;
  Random rand = new Random();
  
  Bubble(int x, int y, int w, int h, int c, int spd, int wiggle) {
    super(x, y, w, h, c);
    speed = spd;
    lowerBound = y - wiggle/2;
    upperBound = y + wiggle/2;
    direction = 1;
  }
  
  int getY() {
    // "wiggling"
    if (this.rand.nextInt(50) == 1) {
      direction *= -1;
    }
    this.yOffset += direction;
    return floor(this.yOffset/10);
  }
  
  int getX() {
    // floating "up"
    this.xOffset += this.speed;
    return floor(this.xOffset/10);
  }
}