#include <vector>
#include <string.h>
#include <sstream>
#include <iostream>


std::vector<std::string> split2(std::string input, char delim){
	std::stringstream stream(input);
	std::vector<std::string> tmp;
	std::string item;

	while(std::getline(stream, item, delim)){
		tmp.push_back(item);
	}
	return tmp;
}

void spawn(std::string args){
	std::string signature;
	std::vector<std::string> arguments = split2(args, ' ');

	std::vector<bool> bools;
	std::vector<std::string> strings;
	std::vector<float> floats;
	std::vector<int> ints;

	for(int x = 0; x<arguments.size(); x++){
		std::string tmp=arguments.at(x);

		if(tmp[0] == '\'' || tmp[0] == '"'){
			signature.push_back('s');
			//I'm not sure if this needs to be 2 or 3...
			strings.push_back(tmp.substr(1,tmp.size()-2));
		}else if(tmp == "true"){
			signature.push_back('b');
			bools.push_back(true);
		}else if(tmp == "false"){
			signature.push_back('b');
			bools.push_back(false);
		}else if(tmp.find('.') == std::string::npos){
			try {
				int tmpint = std::stoi(tmp);
				if(std::to_string(tmpint) == tmp){
					signature.push_back('i');
					ints.push_back(tmpint);
				}else{
					signature.push_back('s');
					strings.push_back(tmp);
				}
			}
			catch (...) {
				signature.push_back('s');
				strings.push_back(tmp);
			}
		}else{
			try {
				float tmpfloat = std::stof(tmp);
				if(std::to_string(tmpfloat).substr(0,tmp.size()) == tmp){
					signature.push_back('f');
					floats.push_back(tmpfloat);
				}else{
					signature.push_back('s');
					strings.push_back(tmp);
				}
			}
			catch (...) {
				signature.push_back('s');
				strings.push_back(tmp);
			}

		}
		std::cout<<signature<<"\n";
	}

	std::cout<<signature;
}


int main(){
	
	spawn("'vector' false trueasd 14.5vds 10.5 1");
	return 0;
}