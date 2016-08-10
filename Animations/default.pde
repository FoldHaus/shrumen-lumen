class Default {
  
  Default() {}
  
  void display() {
    fill(255, 0, 0);
    rect(0, 0, 100, 100); 
  }
  
}




//for (int stripNo = 0; stripNo < numStrips; stripNo++) {
//    fill(c+(stripNo*2), 100, 100);
//    rect(0, stripNo * (height/numStrips), width/2, (stripNo+1) * (height/numStrips)); 
//    fill(c+((numStrips - stripNo)*2), 100, 100);
//    rect(width/2, stripNo * (height/numStrips), width, (stripNo+1) * (height/numStrips));
//}    


//int yscale = height / strips.size();
//for(Strip strip : strips) {
//  int xscale = width / strip.getLength();
//  for (int stripx = 0; stripx < strip.getLength(); stripx++) {
//      x = stripx*xscale + 1;
//      y = stripy*yscale + 1; 
//      color c = get(x, y);
      
//      strip.setPixel(c, stripx);
//   }
//  stripy++;
//}