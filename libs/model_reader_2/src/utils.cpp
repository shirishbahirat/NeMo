//
// Created by Mark Plagge on 2018-09-21.
//

#include "utils.hh"

std::string load_file_into_memory(std::string filename){
  std::fstream json_file(filename);
  //    char x[40];
  //    json_file.read(x,30);
  //    cout << x;

  std::string json_str((std::istreambuf_iterator<char>(json_file)),
                       std::istreambuf_iterator<char>());
  return json_str;
}