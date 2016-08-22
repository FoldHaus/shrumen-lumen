class ColorWipe {
  int[] colorArr = {
    //Dark red to blue
    color(255, 55, 5),
    color(0, 120, 255),
    //Blue to green
    color(142, 14, 204),
    color(17, 120, 69),
    // Green to purple
    color(0, 255, 255),
    color(255, 255, 0),
    //color(241, 196, 15)
  };
  
  int x;
  int colorCount;
  ColorWipe() {
   x = 0;
   colorCount = 0;
  }
  
  void display() {
    //float amt = (frameCount%1000)*0.001;
    
   
    x = (x+5) % width;
    
    if(x == 0) {
      colorCount++;
    }
    
    color c = colorArr[colorCount % colorArr.length];
    fill(c);
    rect(0, 0, x, height);
  }
  
}