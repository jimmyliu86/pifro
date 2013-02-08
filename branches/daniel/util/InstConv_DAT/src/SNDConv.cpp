#include "SNDConv.h"
#include <algorithm>

SNDConv::SNDConv()
{
  //ctor
}

SNDConv::SNDConv(char* filename)
{
  Filename = filename;
}

SNDConv::~SNDConv()
{
  //dtor
}

bool compare (Request i, Request j) {
  if(i.getIsrc() == j.getIsrc()) {
    return (i.getIdst() < j.getIdst());
  } else {
    return (i.getIsrc() < j.getIsrc());
  }
}

void SNDConv::ConvertFile()
{
  string file_tmp(Filename);
  file_tmp += ".net";
  char * file_name = new char[file_tmp.size() + 1];
  strcpy(file_name, file_tmp.c_str());

  cout << "Loading File: " << file_name << endl;
  ifstream fin(file_name);
  int qt_vertex_, qt_edge_;

  fin >> qt_vertex_;
  fin >> qt_edge_;

  cout << "Vertex: " << qt_vertex_ << " - Edges: " << qt_edge_ << endl;
  int** adj_matrix_ = new int*[qt_vertex_];
  for (int i = 0; i < qt_vertex_; i++) {
    adj_matrix_[i] = new int[qt_vertex_];
    for (int x = 0; x < qt_vertex_; x++) {
      adj_matrix_[i][x] = -1;
    }
  }

  int src = 0, dst = 0;
  float weight = 0;

  for (int i = 1; i < qt_edge_; i++) {
    fin >> src;
    fin >> dst;
    fin >> weight;
    adj_matrix_[src][dst] = weight;
    adj_matrix_[dst][src] = weight;
  }

  fin.close();

  file_tmp = Filename;
  file_tmp += ".trf";
  file_name = new char[file_tmp.size() + 1];
  strcpy(file_name, file_tmp.c_str());

  cout << "Loading file: " << file_name << endl;
  fin.open(file_name);
  int qt_request_ = 0;
  fin >> qt_request_;
  Request request;
  int qt;
  int qt_wavelength_ = 0;

  std::vector<Request> vec_request_;
  for (int i = 0; i < qt_request_; i++) {
    fin >> src;
    fin >> dst;
    fin >> qt;

    Request request;
    request.setIsrc(src);
    request.setIdst(dst);
    request.setQt(qt);
    qt_wavelength_ += qt;
    vec_request_.push_back(request);
  }

  string trffile = Filename;
  /*  trffile[strlen(Filename) - 2] = 'r';
    trffile[strlen(Filename) - 1] = 'f';


  */

  trffile += ".dat";
  ofstream fou(trffile.c_str());
  //fou.open(trffile.c_str());
  fou << "qtVertex = " << qt_vertex_ << ";\nqtEdge = " << qt_edge_ << ";\nqtRequests = " << vec_request_.size() << ";\n";
//Salvar a matriz de adjacências e terminado
  int i = 0;
  int j = 0;

  fou << "\ngraph = {\n";
  while(i < qt_vertex_)
  {
    while(j < i)
    {
      if(adj_matrix_[i][j] > 0)
      {
        fou << "< " << j << ", " << i << ", " << adj_matrix_[i][j] << ", 0 >," << endl;
      }
      j++;
    }
    i++;
    j = 0;
  }
  fou << "};\n";



  fou << "requests = {\n";
  for(i=0; i<vec_request_.size(); i++)
  {
    fou << "< " << vec_request_[i].getIsrc() << ", " << vec_request_[i].getIdst() << ", " << (int)(vec_request_[i].getQt()) << " >," << endl;
  }
  fou << "};\n";
  fou.close();
  cout << "Success file conversion";
}
