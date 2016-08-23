class Gradient {
  //instantiate the array of colors
  int[][] colorArr = {
      //blue to green
      {color(0, 0, 255), color(0, 255, 0)},
      //green to red
      {color(0, 255, 0), color(255, 0, 0)},
       //red to pink
      {color(255, 0, 0), color(255, 102, 255)},
      //pink to orange
      {color(255, 102, 255), color(255, 165, 0)},
      //orange to red
      {color(255, 165, 0), color(255, 0, 0)},
      //red to blue
      {color(255, 0, 0), color(0, 0, 255)}
    };
    
    //A variable to keep track of which color range we are in.
    int colorCount;
  
  Gradient() {
     colorCount = 0;
  }
  
  void display() {
    //Determine position in the lerp
    float amt = (frameCount%10000)*0.0001;
    
    //if framecount is zero, increment.
    //This increments on start
    if(amt == 0) {
      colorCount++;
    }
    
    //Set the start and end colors
    color startColor = colorArr[colorCount % colorArr.length][0];
    color endColor = colorArr[colorCount % colorArr.length][1];
    
    //Fimd the correct color in range to show
    color c = lerpColor(startColor, endColor, amt);
    
    //Set the color on the canvas
    fill(c);
    rect(0, 0, width, height);
  }
  
}