
class PastelCircles {
  Gif pastelCircles;
  
  PastelCircles(Animations applet) {
    //Put the file name of the gif as the second argument.
    pastelCircles = new Gif(applet, "pastelcircles.gif");
    pastelCircles.loop();
  }
  
  void display() {
    //Set the background color   
    background(0);
    
    //Change the GIF to fit inside the image
    pastelCircles.resize(width, height);
    
    //Position the image
    image(pastelCircles, 0, 0);
  }
  
}