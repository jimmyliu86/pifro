#include <iostream>

#include "SNDConv.h"
using namespace std;

int main()
{
  string instance_folder = "c:/PIFRO2/instances/";

  std::vector<string> instances;
  instances.push_back("abilene"); // n
  instances.push_back("atlanta"); // n
  instances.push_back("cost266");
  instances.push_back("dfn-bwin"); // n
  instances.push_back("dfn-gwin"); // n
  instances.push_back("di-yuan"); // n
  instances.push_back("france");
  instances.push_back("geant"); // n
  instances.push_back("germany50");
  instances.push_back("giul39");
  instances.push_back("janos-us");
  instances.push_back("janos-us-ca");
  instances.push_back("newyork"); // n
  instances.push_back("nobel-eu");
  instances.push_back("nobel-germany");
  instances.push_back("nobel-us"); // n
  instances.push_back("norway");
  instances.push_back("pdh"); // n
  instances.push_back("pioro40");
  instances.push_back("polska"); // n
  instances.push_back("sun");
  instances.push_back("ta1");
  instances.push_back("ta2");
  instances.push_back("zib54");

  for(int i = 0; i < instances.size(); i++){
      string file_tmp(instance_folder + instances[i] + "/" + instances[i]);
      char * file_name = new char[file_tmp.size() + 1];
      strcpy(file_name, file_tmp.c_str());

    SNDConv objSNDConv(file_name);
    objSNDConv.ConvertFile();
  //cout << "Conversao do arquivo " << file << " concluida!";
  }
  return 0;
}
