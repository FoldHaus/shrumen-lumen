class BlackWhiteTriangle {
  Gif gif;
  
  BlackWhiteTriangle(TestAnimations applet) {
    gif = new Gif(applet, "bwtriangle.gif");
    gif.loop();
  }
  
  void display() {
    background(0);
    gif.resize(width, height);
    image(gif, 0, 0);
  }
  
}