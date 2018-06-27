
void stringParse(String str){
  if (str.charAt(0) == '#'){
    println("YES");
    int charPos = str.indexOf(":");
    println(charPos);
    String str2 = str.substring(charPos+2);
    println(str2);
  }
}
