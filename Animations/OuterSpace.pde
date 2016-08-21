class OuterSpace {
  Gif gif;
  
  OuterSpace(Animations applet) {
    gif = new Gif(applet, "thruspace.gif");
    gif.loop();
  }
  
  void display() {
    background(0);
    gif.resize(width, height);
    image(gif, 0, 0);
  }
  
}