class Circles {
  int[][] colorArr = {
    //green to dark green
    {color(7,249,162), color(10,137,103)},
    //dark green to black
    {color(10,137,103), color(13,25,43)},
    //black to green
    {color(13,25,43), color(7,249,162)}
  };
  
  Circle[] ellipseArr = new Circle[20];
  
  int colorCount;
  int emptyEllipses;
  Random rand = new Random();
  
  Circles() {
    colorCount = 0; 
    emptyEllipses = ellipseArr.length;
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
    
    color ellipseStartColor = colorArr[(colorCount + 1) % colorArr.length][0];
    color ellipseEndColor = colorArr[(colorCount + 1) % colorArr.length][1];
    color ellipseColor = lerpColor(ellipseStartColor, ellipseEndColor, amt);
    
    int r = rand.nextInt(100);
    
    // 1% chance per frame of rendering a new circle
    if (r == 1) {
      if (emptyEllipses > 0) {
        // if we still have unused slots in our array, use one of those
        ellipseArr[ellipseArr.length - emptyEllipses] = new Circle(rand.nextInt(width), rand.nextInt(height), 50, 50, ellipseColor);
      } else {
        // otherwise, write over an existing element
        ellipseArr[abs(emptyEllipses) % ellipseArr.length] = new Circle(rand.nextInt(width), rand.nextInt(height), 50, 50, ellipseColor);
      }
      
      emptyEllipses--;
    }
    
    // iterate over array and render every ellipse
    for (int i = 0; i < ellipseArr.length; i++) {
      if (ellipseArr[i] != null) {
        Circle circle = ellipseArr[i];
        fill(circle.getColor(), 100);
        ellipse(circle.getX(), circle.getY(), circle.getWidth(), circle.getHeight());
        if (circle.getY() < circle.getWidth()) {
          ellipse(circle.getX(), circle.getY() + height, circle.getWidth(), circle.getHeight());
        }
        
        if (circle.getY() > height - circle.getWidth()) {
          ellipse(circle.getX(), circle.getY() - height, circle.getWidth(), circle.getHeight());
        }
      }
    }
  }
}

class Circle {
  int xOffset;
  int yOffset;
  int width;
  int height;
  int col;
  
  Circle(int x, int y, int w, int h, int c) {
    xOffset = x;
    yOffset = y;
    width = w;
    height = h;
    col = c;
  }
  
  int getX() {
    return this.xOffset; 
  }
  
  int getY() {
    return this.yOffset; 
  }
  
  int getWidth() {
    return this.width; 
  }
  
  int getHeight() {
    return this.height; 
  }
  
  int getColor() {
    return this.col; 
  }
}