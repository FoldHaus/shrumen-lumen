import java.util.*;

// Make a variable for your class here.
Green gr;

void setup() {
  colorMode(RGB, 255);
  size(750, 100);
  frameRate(100);
  
  //Instantiate your class object here
  gr = new Green();
}

void draw() {
  
  //Call your display function here
  gr.display();          
}