
class Button {
  //Position
  float posX;
  float posY;
  //Size
  float sizeX;
  float sizeY;
  
  PFont font;
  String text;
  
  //Color
  int r;
  int g;
  int b;
  
  float scale;
  boolean wasPressed;
  boolean mouseOver;
  
  int timesPressed;
  
  //Functions
  
  Button(float posx, float posy, float sizex, float sizey){
    this.posX = posx;
    this.posY = posy;
    this.sizeX = sizex;
    this.sizeY = sizey;
    this.text = "";
    
    this.scale = 1;
    this.wasPressed = false;
    this.mouseOver = false;
    this.timesPressed = 0;
    
    font = createFont("Arial",14,true);
  }
  
  void setColor(int red, int green, int blue){
    this.r = red;
    this.g = green;
    this.b = blue;
  }
  
  void setName(String txt){
    text = txt;
  }
  
  void draw(){
    fill(r,g,b);
    //noStroke();
    isMouseOver();
    isPressed();
    isReleased();
    rectMode(CENTER);
    rect(posX,posY,sizeX*scale,sizeY*scale, 5);
    fill(0);
    textAlign(CENTER,CENTER);
    textFont(font);
    text(text,posX, posY);
    
  }
  
  boolean isMouseOver(){
    if (mouseX > posX-sizeX/2 && mouseX < posX+sizeX/2){
      if (mouseY >posY-sizeY/2 && mouseY < posY+sizeY/2){
        //change transparency
        mouseOver = true;
        return true;
      }
    }
    mouseOver = false;
    return false;
  }
  
  boolean isPressed(){
    if (mousePressed == true && mouseOver){
      scale = 0.95;
      wasPressed = true;
      return true;
    }
    else{
      return false;
    }
  }
  
  boolean isReleased(){
    if(mousePressed == false && wasPressed){
      wasPressed = false;
      timesPressed++;
      scale = 1;
      return true;
    }
    return false;
  }
}
