
void stringParse(String str){
  if (str.charAt(0) == '#'){
    int charPos = str.indexOf(":");
    println(charPos);
    String name = str.substring(1,charPos);
    println(name);
    if (name.equals("States")){
      String data = str.substring(charPos+2);
      println(data);
      parseStateString(data);
    }
  }
}

void parseStateString(String str){
  String list[] = str.split(",");
  println(list[0]);
  println(list[1]);
}
