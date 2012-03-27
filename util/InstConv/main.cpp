#include <iostream>

#include "SNDConv.h"
using namespace std;

int main()
{
    char file[256], conv;
    cout << "Path to file for convert: ";
    cin >> file;

    SNDConv objSNDConv(file);
    objSNDConv.ConvertFile();
    //cout << "Conversao do arquivo " << file << " concluida!";
    return 0;
}
