//
// Created by Mark Plagge on 8/8/18.
//

#include <cstdio>
#include "include/tn_parser.hh"
#include "json_dto.hh"
#include "tests/test_data.hh"
#include "extern/rang.hh"
#include "extern/CLI11.hh"
#include <csignal>
//#include "extern/argh.hh"

void signal_handler(int s){
  std::cout << std::endl << rang::style::reset << rang::fg::red << rang::style ::bold;
  std::cout << "Control-C detected, exiting..." << rang::style::reset << std::endl;
  std::exit(1); // will call the correct exit func, no unwinding of the stack though
}




int main(int argc, char *argv[]) {
  // Nice Control-C
  struct sigaction sigIntHandler;
  sigIntHandler.sa_handler = signal_handler;
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;
  sigaction(SIGINT, &sigIntHandler, nullptr);

  CLI::App app{"NeMo JSON Parser"};

  string filename;
  string save_file;
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

  if(!do_json && !do_bin && !do_nfg) {
    cout << std::endl << rang::style::reset << rang::fg::red << rang::style::bold;
    cout << "You must specifiy at least one of [-j,-b,-n]" << rang::style::reset <<std::endl;
    cout << rang::fg::blue << "Exiting...." << endl;
    exit(2);
  }
  unsigned char o = 0;
  if(do_json){
    o = o | TN_OUT_JSON;
  }
  if (do_bin){
    o = o | TN_OUT_BIN;
    if(do_bin_file_per_core){
      o = o | TN_OUT_BIN_SPLIT;
    }
  }
  if (do_nfg){
    o = o | TN_OUT_LUA;
  }



  cout << rang::style::reset << rang::fg::green <<"----Parsing JSON file " << filename << "----\n" << rang::style::reset;
  //Test crossbar logic
  //char *filename = "/Users/markplagge/dev/NeMo/scripts/model/th_corelet_net.json";
    
  TN_Main model = create_tn_data(filename);
  cout << "\n Created Model. \n";

  TN_Output out(save_file,model,o );
  cout << "\n saving json file  to " << save_file << "\n";
  out.write_data();

//#endif

return 0;
}
