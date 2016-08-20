class ColorWipe {
  int[] colorArr = {
    color(22, 160, 133),
    color(26, 188, 156),
    color(46, 204, 113),
    color(231, 76, 60),
    color(230, 126, 34),
    color(243, 156, 18),
    color(241, 196, 15)
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