class Concentric {
  Gif concentric;
  
  Concentric(TestAnimations applet) {
    //Put the file name of the gif as the second argument.
    concentric = new Gif(applet, "concentric-resized.gif");
    concentric.loop();
  }
  
  void display() {
    //Set the background color   
    background(0);
  
    
    //Position the image
    image(concentric, 0, 0);
  }
  
}