#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <utility>
#include <string>
#ifdef __APPLE__
#include <unistd.h>
#endif
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TH1D.h"
#include "TObjArray.h"
#include "TObjString.h"

#include "Setup.h"
#include "Calib.h"
#include "Event.h"
#include "Tile.h"
#include "HGCROC.h"
#include "Caen.h"
#include "ComparisonCalib.h"

void PrintHelp(char* exe){
  std::cout<<"Usage:"<<std::endl;
  std::cout<<exe<<" [-option (arguments)]"<<std::endl;
  std::cout<<"Options:"<<std::endl;
  std::cout<<"-i uuu   Input file list"<<std::endl;
  std::cout<<"-o vvv   Output file name (mandatory)"<<std::endl;
  std::cout<<"-O kkk   Output directory name for plots (mandatory)"<<std::endl;
  std::cout<<"-f       Force to write output if already exist"<<std::endl;
  std::cout<<"-r       Trending plots versus run #"<<std::endl;
  std::cout<<"-V       Trending plots versus Vop"<<std::endl;
  std::cout<<"-d [0-3] Debugging mode"<<std::endl;
  //std::cout<<"-t       Trending plots versus BoR time"<<std::endl;
  std::cout<<"-h       this help"<<std::endl<<std::endl;
  std::cout<<"Examples:"<<std::endl;
  std::cout<<exe<<" (-f) -o TrendingOutput.root -i input_list.txt (-f to overwrite existing output)"<<std::endl;
  std::cout<<exe<<" (-f) -o TrendingOutput.root InputName*.root InputName2.root (-f to overwrite existing output)"<<std::endl;
}
  

int main(int argc, char* argv[]){
  if(argc<4) {
    PrintHelp(argv[0]);
    return 0;
  }
  std::vector<std::string> RootRegexp;
  std::vector<std::string>::iterator it;
  for(int i=1; i<argc; i++){
    RootRegexp.push_back(argv[i]);
  }
  ComparisonCalib CompAnalysis;
  int c;
  while((c=getopt(argc,argv,"fo:O:d:i:rVth"))!=-1){
    switch(c){
    case 'f':
      std::cout<<"If output already exists it will be overwritten"<<std::endl;
      CompAnalysis.CanOverWrite(true);
      it=std::find(RootRegexp.begin(),RootRegexp.end(),"-f");
      RootRegexp.erase(it);
      break;
    case 'o':
      std::cout<<"Output to be saved in: "<<optarg<<std::endl;
      CompAnalysis.SetRootOutput(Form("%s",optarg));
      it=std::find(RootRegexp.begin(),RootRegexp.end(),"-o");
      RootRegexp.erase(it);
      it=std::find(RootRegexp.begin(),RootRegexp.end(),Form("%s",optarg));
      RootRegexp.erase(it);
      break;
    case 'O':
      std::cout<<"Outputdir plots to be saved in: "<<optarg<<std::endl;
      CompAnalysis.SetPlotOutputDir(Form("%s",optarg));
      it=std::find(RootRegexp.begin(),RootRegexp.end(),"-O");
      RootRegexp.erase(it);
      it=std::find(RootRegexp.begin(),RootRegexp.end(),Form("%s",optarg));
      RootRegexp.erase(it);
      break;
    case 'i':
      std::cout<<"Root input file is: "<<optarg<<std::endl;
      CompAnalysis.SetInputList(Form("%s",optarg));
      it=std::find(RootRegexp.begin(),RootRegexp.end(),"-i");
      RootRegexp.erase(it);
      it=std::find(RootRegexp.begin(),RootRegexp.end(),Form("%s",optarg));
      RootRegexp.erase(it);
      break;
    case 'd':
      std::cout<<"enable debug " << optarg <<std::endl;
      CompAnalysis.EnableDebug(atoi(optarg));
      it=std::find(RootRegexp.begin(),RootRegexp.end(),"-d");
      RootRegexp.erase(it);
      it=std::find(RootRegexp.begin(),RootRegexp.end(),Form("%s",optarg));
      RootRegexp.erase(it);
      break;
    case 'r':
      std::cout<<"Trending plots versus run #"<<std::endl;
      CompAnalysis.SetTrendingAxis(0);
      it=std::find(RootRegexp.begin(),RootRegexp.end(),"-r");
      RootRegexp.erase(it);
      break;
    case 'V':
      std::cout<<"Trending plots versus Vop"<<std::endl;
      CompAnalysis.SetTrendingAxis(1);
      it=std::find(RootRegexp.begin(),RootRegexp.end(),"-V");
      RootRegexp.erase(it);
      break;
    //case 't':
    //  std::cout<<"Trending plots versus BoR time"<<std::endl;
    //  CompAnalysis.SetTrendingAxis(2);
    //  it=std::find(RootRegexp.begin(),RootRegexp.end(),"-t");
    //  RootRegexp.erase(it);
    //  break;
    case '?':
      std::cout<<"Option "<<optarg <<" not supported, will be ignored "<<std::endl;
      break;
    case 'h':
      PrintHelp(argv[0]);
      return 0;
    }
  }
  std::cout<<"begin extra list"<<std::endl;
  for(it=RootRegexp.begin(); it!=RootRegexp.end(); ++it){
    std::cout<<*it<<std::endl;
    CompAnalysis.AddInputFile(*it);
  }
  std::cout<<"end extra list"<<std::endl;
  if(!CompAnalysis.CheckAndOpenIO()){
    std::cout<<"Check input and configurations, inconsistency or error with I/O detected"<<std::endl;
    PrintHelp(argv[0]);
    return -1;
  }

  CompAnalysis.Process();
  //CompAnalysis.Close();
  std::cout<<"Exiting"<<std::endl;
  
  return 0;
}
