#include <iostream>
#include <string>
#include <fstream>

std::string variableName[100000];
std::string variableValue[100000];

int searchVariable(std::string name) {
  try {
    for(int i = 0; i < 100000; i++) {
      if(variableName[i] == name) {
        return i;
      }
    }
    throw(name);
  } catch(std::string e) {
    std::cout << "ERROR: Undefined variable " << e << " ";
    return -1;
  }

}

int lexer(std::string syntax) {
  std::string command;
  bool loop = true;
  int i = 0;
  while(loop) {
    if(syntax[i] == '(' || syntax[i] == '"' || syntax[i] == ' ') {
      loop = false;
    } else {
        command = command + syntax[i];
    }
    i++;
  }
  if (command == "print") {
    syntax = syntax.substr(6);
    syntax = syntax.substr(0, syntax.length()-1);
    std::string temp;
    bool status = false;
    for(int i = 0; i < syntax.length(); i++) {
      if (syntax[i] == '"') {
        status = !(status);
      } else if(status == true) {
        std::cout << syntax[i];
      } else if (status == false) {
        if(syntax[i] != ' ') {
          temp = temp + syntax[i];
        } else {
          if(!(temp.empty())) {
            std::cout << variableValue[searchVariable(temp)];
            temp = "";
          }
        }
      }
    }
    if(!(temp.empty())) {
      std::cout << variableValue[searchVariable(temp)];
      temp = "";
    }
  } else if (command == "printl") {
    syntax = syntax.substr(7);
    syntax = syntax.substr(0, syntax.length()-1);
    std::string temp;
    bool status = false;
    for(int i = 0; i < syntax.length(); i++) {
      if (syntax[i] == '"') {
        status = !(status);
      } else if(status == true) {
        std::cout << syntax[i];
      } else if (status == false) {
        if(syntax[i] != ' ') {
          temp = temp + syntax[i];
        } else {
          if(!(temp.empty())) {
            std::cout << variableValue[searchVariable(temp)];
            temp = "";
          }
        }
      }
    }
    if(!(temp.empty())) {
      std::cout << variableValue[searchVariable(temp)];
      temp = "";
    }
    std::cout << std::endl;
  } else if (command == "var") {
    std::string temp;
    std::string tempVar[100];
    int count = 0;
    for(int i = 0; i < syntax.length(); i++) {
      if(syntax[i] != ' ') {
        temp = temp + syntax[i];
      } else {
        tempVar[count] = temp;
        count++;
        temp = "";
      }
    }
    std::string value = temp;
    count = 0;
    while(count < 100000) {
      if(variableName[count].empty()) {
        variableName[count] = tempVar[1];
        variableValue[count] = value;
        break;
      }
      count++;
    }
  }
}

int parse(std::string fileName) {
  std::ifstream reader(fileName);
  try {
    if (fileName.substr(fileName.length() - 4) == ".cmh") {
      try {
        if(!reader) {
          throw(fileName);
        } else {
          char symbol;
          std::string line;
          for(int i = 0; !(reader.eof()); i++) {
            reader.get(symbol);
            if(symbol != ';') {
              line = line + symbol;
            } else {
              std::string temp;
              for(int j = 0; j < line.length(); j++) {
                if (line[j] != ' ' && j == 0) {
                  if(line[j] != '\n') {
                    temp = temp + line[j];
                  }
                }
                if(j != 0) {
                  if(line[j-1] == ' ' && line[j] != ' ') {
                    if(line[j] != '\n') {
                      temp = temp + line[j];
                    }
                  } else if(line[j-1] != ' ' && line[j] == ' ') {
                    if(line[j] != '\n') {
                      temp = temp + line[j];
                    }
                  } else if(line[j] != ' ') {
                    if(line[j] != '\n') {
                      temp = temp + line[j];
                    }
                  }
                }
              }
              line = temp;
              lexer(line);
              line = "";
            }
          }
        }
      } catch(std::string fileName) {
        std::cout << "ERROR: " << fileName << " not found";
      }
    } else {
      throw(fileName);
    }
  } catch(std::string fileName) {
    std::cout << "ERROR: " << fileName << " is not a valid .cmh document";
  }
}

int main(int argc, const char * argv[]) {
  try {
    if (argc > 1) {
      const std::string FILENAME = argv[1];
      parse(FILENAME);
    } else {
      throw(1);
    }
  } catch(int e) {
    std::cout << "ERROR: Invalid Argument";
  }
  return 0;
}
