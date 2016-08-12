class Green {
  
  Green() {}
  
  void display() {
    fill(0, 0, 255);
    rect(0, 0, width/2, height);
    fill(0, 255, 0);
    rect(width/2, 0, width, height); 
  }
  
}