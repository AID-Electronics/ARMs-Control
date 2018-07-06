
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
    else if (name.equals("Orient")){
      String data = str.substring(charPos+2);
      parseOrientationString(data);
    }
  }
}

void parseStateString(String str){
  String list[] = str.split(",");
  globalState = int(list[0]);
  localState = int(list[1]);
}
void parseOrientationString(String str){
  String list[] = str.split(",");
  orientX = float(list[0]);
  orientY = float(list[1]);
  orientZ = float(list[2]);
}
