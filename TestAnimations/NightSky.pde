class NightSky {
  int x;
  NightSky() {
    x = 0;
  }
  
  void display() {
    //float amt = (frameCount%1000)*0.001;
     
    color purple = color(75, 0, 130);
  
    background(purple);

    x = (x+5) % width;
    
    for (int i = 0; i < width; i++){
      if (x %  == 0) {
        fill(color(255,255,255));
        rect(x, x, 5, 5);
        fill(color(255,255,255));
        rect(x+50, x, 5, 5);
      }
    }
  }
  
}