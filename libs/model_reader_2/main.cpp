//
// Created by Mark Plagge on 2018-09-21.
//
#include "include/tn_json_parser.hh"
#include <cstdio>
#include "lib/CLI11.hh"
#include "lib/rang.hh"

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

  CLI11_PARSE(app,argc,argv);



  return 0;
}