
class LoopingGif {
  Gif loopingGif;
  
  LoopingGif(TestAnimations applet) {
    //Put the file name of the gif as the second argument.
    loopingGif = new Gif(applet, "rainbow.gif");
    loopingGif.loop();
  }
  
  void display() {
    //Set the background color   
    background(0);
    
    //Change the GIF to fit inside the image
    loopingGif.resize(width, height);
    
    //Position the image
    image(loopingGif, 0, 0);
  }
  
}