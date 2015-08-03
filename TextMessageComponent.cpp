#include "skilLib.h"
#include "components.h"
#include <string>
#include <iostream>

TextMessage::TextMessage(){
	id = COMPONENT_TEXTMESSAGE;
	message = "Hello, World!";
	font = "monospaceWhite";
	fontSize = 32;
	padding = 5;
}

TextMessage::TextMessage(std::string msg, std::string fnt, int size){
	id = COMPONENT_TEXTMESSAGE;
	message = msg;
	font = fnt;
	fontSize = size;
	padding = 5;
}

TextMessage::TextMessage(std::string msg, std::string fnt, int size, int pad){
	id = COMPONENT_TEXTMESSAGE;
	message = msg;
	font = fnt;
	fontSize = size;
	padding = pad;
}

Component *TextMessage::spawn(std::string sig, std::string args){
  std::vector<std::string> arguments = splitForStrings(args, ' ');
  arguments.erase(arguments.begin());
  if(sig.compare("ssi") == 0){
    return new TextMessage(arguments[0], arguments[1], stoi(arguments[2]));
  }
  if(sig.compare("ssii") == 0){
    return new TextMessage(arguments[0], arguments[1], stoi(arguments[2]), stoi(arguments[3]));
  }
  return new TextMessage();
}

int TextMessage::getSize(){ return fontSize; }
int TextMessage::getPadding(){ return padding; }
std::string TextMessage::getMessage(){ return message; }
std::string TextMessage::getFont(){ return font; }

void TextMessage::setSize(int size){ if(size > 0) fontSize = size; }
void TextMessage::setPadding(int pad){ padding = pad; }
void TextMessage::setMessage(std::string msg){ message = msg; }
void TextMessage::setFont(std::string fnt){ font = fnt; }