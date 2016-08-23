/*
* Demonstrates the use of the GifAnimation library.
* the left animation is looping, the one in the middle 
* plays once on mouse click and the one in the right
* is a PImage array. 
* the first two pause if you hit the spacebar.
*/

import gifAnimation.*;

PImage[] animation;
Gif loopingGif;
Gif nonLoopingGif;
boolean pause = false;

public void setup() {
  size(400, 200);
  frameRate(100);
  
  println("gifAnimation " + Gif.version());
  // create the GifAnimation object for playback
  loopingGif = new Gif(this, "rainbow.gif");
  loopingGif.loop();
}

void draw() {
  background(255 / (float)height * mouseY);
  image(loopingGif, 10, height / 2 - loopingGif.height / 2);
}

void mousePressed() {
  nonLoopingGif.play();
}