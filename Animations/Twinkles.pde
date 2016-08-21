class Twinkles {
  int black = color(0, 0, 0);
  int[] colorArr = {
    color(7,249,162),
    color(231, 76, 60),
    color(243, 243, 21),
    color(0, 51, 204)
  };
  int maxTwinkles = 40;
  
  ArrayList<Twinkle> twinkleList = new ArrayList<Twinkle>();
  Random rand = new Random();
  
  void display() {
    noStroke();
    fill(black);
    rect(0, 0, width, height);
    
    float amt = (frameCount%1000)*0.01;
    
    if (twinkleList.size() < maxTwinkles && rand.nextInt(10) == 1) {
      twinkleList.add(new Twinkle(rand.nextInt(width), rand.nextInt(height), 50, 50, colorArr[rand.nextInt(colorArr.length)], 200));
    }
    
    for (int i = 0; i < twinkleList.size(); i++) {
      Twinkle twinkle = twinkleList.get(i);
      if (twinkle.isAlive()) {
        fill(twinkle.getColor(), twinkle.getOpacity());
        ellipse(twinkle.getX(), twinkle.getY(), twinkle.getWidth(), twinkle.getHeight());
        
        if (twinkle.getY() < twinkle.getWidth()) {
          ellipse(twinkle.getX(), twinkle.getY() + height, twinkle.getWidth(), twinkle.getHeight());
        }
        
        if (twinkle.getY() > height - twinkle.getWidth()) {
          ellipse(twinkle.getX(), twinkle.getY() - height, twinkle.getWidth(), twinkle.getHeight());
        }
        
      } else {
        twinkleList.remove(i);
      }
    }
  }
}

class Twinkle {
  int col;
  int xOffset;
  int yOffset;
  int width;
  int height;
  float lifespan;
  float age;
  
  Twinkle(int x, int y, int w, int h, int c, float life) {
    xOffset = x;
    yOffset = y;
    width = w;
    height = h;
    col = c;
    lifespan = life;
    age = 0;
  }
  
  int getX() {
    return this.xOffset; 
  }
  
  int getY() {
    return this.yOffset; 
  }
  
  int getWidth() {
    return this.width; 
  }
  
  int getHeight() {
    return this.height; 
  }
  
  boolean isAlive() {
    return this.age < this.lifespan; 
  }
  
  int getColor() {
    return this.col; 
  }
  
  int getOpacity() {
    int brightness = int(255 * (1 - abs(this.lifespan/2 - this.age)/(this.lifespan/2)));
    this.age += 1;
    return brightness;
  }
}