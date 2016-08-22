import java.util.*;
import gifAnimation.*;

// Make a variable for your class here.
Grass gr;

void setup() {
  colorMode(RGB, 255);
  size(750, 100);
  frameRate(100);
  
  //Instantiate your class object here
  gr = new Grass();
  
  //An example of how to add a Gif class
  //loopingGif = new LoopingGif(this);
}

void draw() {
  
  //Call your display function here
  gr.display();
  
  //An example of using a GIF
  //loopingGif.display();
}