//
// Created by Mark Plagge on 2018-09-21.
//
#include "include/tn_json_parser.hh"
#include <cstdio>
#include <iostream>
#include <fstream>
#include "lib/CLI11.hh"
#include "lib/rang.hh"
#include "src/utils.hh"
#include <sys/utsname.h>
#ifdef DEBUG
Json::Value decode(std::string filename){
  using namespace Json;
  Value root;

  CharReaderBuilder builder;
  JSONCPP_STRING errs;
  //std::string file = load_file_into_memory(filename);
  std::ifstream file(filename);

  bool ok = parseFromStream(builder,file,&root,&errs);
  if(!ok){
    std::cout << "Failed to parse. \n" << "Error: " << errs << "\n";
  }
  return root;
}
void run_tests(){
  struct utsname name;
  if (uname(&name))
    exit(-1);

  std::cout << "tests running on : " << name.sysname << " " <<name.release <<"\n";
  std::string test_bc_fp       ("./tests/BootCampExample11.json");
  std::string test_th_small_fp ("./tests/th_small_test.json");
  std::string test_full_fp     ("./tests/th_corelet_net.json");

  //fist small js test
  Json::Value root_small = decode(test_th_small_fp);



}
#endif

int main(int argc, char *argv[]) {
  CLI::App app{"NeMo JSON Parser"};

  std::string filename;
  std::string save_file;
  bool do_json;
  bool do_bin;
  bool do_nfg;
  bool do_bin_file_per_core;
  app.add_flag("-j", do_json, "Save JSON file - for debug/test.");
  app.add_flag("-b", do_bin, "Save binary file. Please ensure endianness is correct!");
  app.add_flag("-n", do_nfg, "Save NeMo LUA-based config file. Uses the soon-to-be depricated NeMo lua config syntax.");
  app.add_option("-i,--input_file", filename, "Input JSON file")->required()->check(CLI::ExistingFile);
  app.add_option("-o,--output_file", save_file,"Output filename template. This program will automatically add proper "
                                               "extension(s) to the file");
  app.add_flag("-s,--split", do_bin_file_per_core,"When saving binary file, save one file per core rather than"
                                                  "one large file.");

  // Testing code //
#ifdef DEBUG
  run_tests();
#endif
  CLI11_PARSE(app,argc,argv);



  return 0;
}