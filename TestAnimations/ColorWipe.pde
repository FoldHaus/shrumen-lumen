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
    color(255, 255, 0)
  };
   
  float x;
  int colorCount;
  ColorWipe() {
   x = 0;
   colorCount = 1;
  }
  
  void display() {
    
    background(colorArr[(colorCount-1) % colorArr.length]);
    //float amt = (frameCount%1000)*0.001;
    
    color c = colorArr[colorCount % colorArr.length];
    fill(c);
    rect(0, 0, x, height);
   
    x = (x+0.1) % width;
    println(colorCount);
    
    if(x < 0.1) {
      
      colorCount++;
    }
    
    
  }
  
}