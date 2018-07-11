
void stringParse(String str){
  if (str.charAt(0) == '#'){
    int charPos = str.indexOf(":");
    String name = str.substring(1,charPos);
    if (name.equals("States")){
      String data = str.substring(charPos+2);
      parseStateString(data);
    }
    else if (name.equals("Orient")){
      String data = str.substring(charPos+2);
      parseOrientationString(data);
    }
    else if (name.equals("Dron")){
      String data = str.substring(charPos+2);
      parseDronString(data);
    }
    else if (name.equals("Temp")){
      String data = str.substring(charPos+2);
      parseTempString(data);
    }
    else if (name.equals("Alarms")){
      String data = str.substring(charPos+2);
      parseAlarmString(data);
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
void parseDronString(String str){
  String list[] = str.split(",");
  dron.id = int(list[0]);
  dron.vel = float(list[1]);
  dron.dist = float(list[2]);
  dron.ang = float(list[3]);
  dron.intensidad = float(list[4]);
}
void parseTempString(String str){
  String list[] = str.split(",");
  tempM1 = float(list[0]);
  tempM2 = float(list[1]);
}
void parseAlarmString(String str){
  println(str);
  String list[] = str.split(",");
  for(int i = 0; i < 9; i++){
    alarmas.estadoAlarma[i] = int(list[i]);
  }
}
