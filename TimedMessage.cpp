#include "skilLib.h"
#include "components.h"
#include <string>
#include <iostream>

TimedMessage::TimedMessage(){
  id = COMPONENT_TIMEDMESSAGE;
  remaining = 0;
  message = "";
}

TimedMessage::TimedMessage(float t, std::string m){
  id = COMPONENT_TIMEDMESSAGE;
  remaining = t;
  message = m;
}

std::string TimedMessage::getTarget(){ return message; }
float TimedMessage::getTime(){ return remaining; }
void TimedMessage::progress(float delta){ remaining -= delta; }

Component *TimedMessage::spawn(std::string sig, std::string args){
  
  std::vector<std::string> arguments = split(args, ' ');
  arguments.erase(arguments.begin());
  if(sig.compare("fs") == 0){
    return new TimedMessage(stof(arguments[0]), arguments[1]);
  }

  return new TimedMessage();
}
