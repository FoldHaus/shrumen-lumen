class BlackWhiteCircle {
  Gif gif;
  
  BlackWhiteCircle(Animations applet) {
    gif = new Gif(applet, "bwcircle.gif");
    gif.loop();
  }
  
  void display() {
    background(0);
    gif.resize(width, height);
    image(gif, 0, 0);
  }
  
}