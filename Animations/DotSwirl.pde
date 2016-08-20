
class DotSwirl {
  Gif dotSwirl;
  
  DotSwirl(Animations applet) {
    //Put the file name of the gif as the second argument.
    dotSwirl = new Gif(applet, "dotswirl-resized.gif");
    dotSwirl.loop();
  }
  
  void display() {
    //Set the background color   
    background(0);
    
    //Change the GIF to fit inside the image
    dotSwirl.resize(width, height);
    
    //Position the image
    image(dotSwirl, 0, 0);
  }
  
}