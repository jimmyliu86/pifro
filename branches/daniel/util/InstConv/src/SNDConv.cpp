#include "SNDConv.h"

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

double SNDConv::distance(double lat1, double lon1, double lat2, double lon2, char unit)
{
    double theta, dist;
    theta = lon1 - lon2;
    dist = sin(deg2rad(lat1)) * sin(deg2rad(lat2)) + cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * cos(deg2rad(theta));
    dist = acos(dist);
    dist = rad2deg(dist);
    dist = dist * 60 * 1.1515;


    switch(unit)
    {
    case 'M':
        break;
    case 'K':
        dist = dist * 1.609344;
        break;
    case 'N':
        dist = dist * 0.8684;
        break;
    }
    return (dist);
}

double SNDConv::deg2rad(double deg)
{
    return (deg * pi / 180);
}

double SNDConv::rad2deg(double rad)
{
    return (rad * 180 / pi);
}

void SNDConv::ConvertFile()
{

    //Gerando o Vector com os dados dos Vértices
    vector<Vertex> VecVertex;
    ifstream fin(Filename);
    string name, name2;
    char tmp[100];
    float latitude, longitude;

    fin >> tmp;
    while(strcmp(tmp,"NODES"))
    {
        fin >> tmp;
    }
    fin >> tmp;
    cout.precision(5);
    while(true)
    {
        Vertex v;
        fin >> name;
        if(name.compare(")"))
        {
            fin >> tmp;
            fin >> tmp;
            longitude = atof(tmp);
            fin >> tmp;
            latitude = atof(tmp);
            v.setName(name);
            v.setLongitude(longitude);
            v.setLatitude(latitude);
            VecVertex.push_back(v);
            fin >> name;
        }
        else
        {
            break;
        }
    }

    //cout << "Distancia: " << distance(33.75, -84.3833, 34.50, -85.50,  'K') << endl;

    //Impressão do VecVertex
    int size = VecVertex.size();
    for(int i=0; i<size; i++)
    {
        cout << "Name: " << VecVertex[i].getName() << " - Longitude: " << VecVertex[i].getLongitude() << " - Latitude: " << VecVertex[i].getLatitude() << endl;
    }


    //Criando as arestas
    double adjMatrix[VecVertex.size()][VecVertex.size()];

    for(int i=0; i<VecVertex.size(); i++)
    {
        for(int x=0; x<VecVertex.size(); x++)
        {
            adjMatrix[i][x] = 0;
        }
    }

    while(strcmp(tmp,"LINKS"))
    {
        fin >> tmp;
    }
    fin >> tmp;

    int src=0, dst=0, x =0, qtEdges = 0;
    while(true)
    {
        fin >> tmp;
        if(strcmp(tmp,")"))
        {
            fin >> tmp;
            cout << "TMP1: " << tmp << endl;
            fin >> name;
            fin >> name2;
            cout << "NAME: " << name << " - NAME2: " << name2 << endl;
            src = -1;
            dst = -1;
            x = 0;
            while((src == -1) || (dst == -1) && (x < VecVertex.size()))
            {
                //cout << "VECVERTEX: " << VecVertex[x].getName() << " - Compare: " << VecVertex[x].getName().compare(name) << endl;
                if(!VecVertex[x].getName().compare(name))
                {
                    src = x;
                }

                if(!VecVertex[x].getName().compare(name2))
                {
                    dst = x;
                }
                x++;
            }
            qtEdges++;
            adjMatrix[src][dst] = distance(VecVertex[src].getLatitude(), VecVertex[src].getLongitude(), VecVertex[dst].getLatitude(), VecVertex[dst].getLongitude(), 'K');
            adjMatrix[dst][src] = distance(VecVertex[src].getLatitude(), VecVertex[src].getLongitude(), VecVertex[dst].getLatitude(), VecVertex[dst].getLongitude(), 'K');
        }
        else
        {
            break;
        }
        fin >> tmp;
        fin >> tmp;
        fin >> tmp;
        fin >> tmp;
        fin >> tmp;
        fin >> tmp;
        fin >> tmp;
        fin >> tmp;
        fin >> tmp;
        cout << "LINKS: " << tmp << " - SRC: " << src << " - DST: " << dst << endl;

    }

    //Imprimindo a Matriz de Adjacências
    for(int i=0; i<VecVertex.size(); i++)
    {
        for(int x=0; x<VecVertex.size(); x++)
        {
            cout << "Linha " << i << " - Coluna " << x << " - " << adjMatrix[i][x] << endl;
        }
    }
    cout << "TOTAL DE ARESTAS: " << qtEdges << endl;

    vector<Request> vecRequest;
    while(strcmp(tmp, "DEMANDS"))
    {
        fin >> tmp;
    }
    fin >> tmp;

    double qt;
    while(true)
    {
        fin >> tmp;
        if(strcmp(tmp, ")"))
        {
            fin >> tmp;
            fin >> name;
            fin >> name2;
            fin >> tmp;
            fin >> tmp;
            fin >> qt;

            src = -1;
            dst = -1;
            x = 0;
            while((src == -1) || (dst == -1) && (x < VecVertex.size()))
            {
                //cout << "VECVERTEX: " << VecVertex[x].getName() << " - Compare: " << VecVertex[x].getName().compare(name) << endl;
                if(!VecVertex[x].getName().compare(name))
                {
                    src = x;
                }

                if(!VecVertex[x].getName().compare(name2))
                {
                    dst = x;
                }
                x++;
            }
            Request request;
            request.setSrc(name);
            request.setDst(name2);
            request.setQt(qt);
            request.setIsrc(src);
            request.setIdst(dst);

            vecRequest.push_back(request);

            fin >> tmp;
        }
        else
        {
            break;
        }
    }
    fin.close();

    //vector<Request> vecReqRep;

    int i = 0, j = 0;
    while(i < vecRequest.size())
    {
        j=i+1;
        while(j < vecRequest.size())
        {
            if((vecRequest[i].getIsrc() == vecRequest[j].getIsrc()) && (vecRequest[i].getIdst() == vecRequest[j].getIdst())  && (i != j))
            {
                /*vecReqRep.push_back(vecRequest[i]);
                vecReqRep.push_back(vecRequest[j]);*/

                vecRequest[i].setQt(vecRequest[i].getQt() + vecRequest[j].getQt());
                vecRequest.erase(vecRequest.begin() + j);
                j=i;
            }
            j++;
        }
        i++;
    }


    i = 0, j = 0;
    while(i < vecRequest.size())
    {
        j=i+1;
        while(j < vecRequest.size())
        {
            if((vecRequest[i].getIsrc() == vecRequest[j].getIdst()) && (vecRequest[i].getIdst() == vecRequest[j].getIsrc())  && (i != j))
            {

                /*vecReqRep.push_back(vecRequest[i]);
                vecReqRep.push_back(vecRequest[j]);*/

                vecRequest[i].setQt(vecRequest[i].getQt() + vecRequest[j].getQt());
                vecRequest.erase(vecRequest.begin() + j);
                j=i;
            }
            j++;
        }
        i++;
    }

    cout.precision(10);
    for(int v=0; v<vecRequest.size(); v++)
    {
        cout << "Request " << v << " - SRC: " << vecRequest[v].getIsrc() << " - DST: " << vecRequest[v].getIdst() << " - QT: " << vecRequest[v].getQt() << endl;
    }

    /*cout << "REPETIDOS: " << endl;
    for(int v=0; v<vecReqRep.size(); v++)
    {
        cout << "REPETIDO " << v << " - SRC: " << vecReqRep[v].getIsrc() << " - DST: " << vecReqRep[v].getIdst() << endl;
    }*/

    string trffile = Filename;
    trffile[strlen(Filename) - 2] = 'r';
    trffile[strlen(Filename) - 1] = 'f';

    ofstream fou(trffile.c_str());
    fou << vecRequest.size() << endl;
    for(i=0; i<vecRequest.size(); i++)
    {
        //MBPS TO GBPS CONVERSION HERE!!!!
        //fou << vecRequest[i].getIsrc() << " " << vecRequest[i].getIdst() << " " << vecRequest[i].getQt() << endl;
        fou << vecRequest[i].getIsrc() << " " << vecRequest[i].getIdst() << " " << ceilf(vecRequest[i].getQt() / 1000) << endl;
    }
    fou.close();

    trffile[strlen(Filename) - 3] = 'n';
    trffile[strlen(Filename) - 2] = 'e';
    trffile[strlen(Filename) - 1] = 't';
    fou.open(trffile.c_str());
    fou << VecVertex.size() << " " << qtEdges << endl;
//Salvar a matriz de adjacências e terminado
    i = 0;
    j = 0;
    while(i < VecVertex.size())
    {
        while(j < i)
        {
            if(adjMatrix[i][j] > 0)
            {
                fou << i << " " << j << " " << adjMatrix[i][j] << endl;
            }
            j++;
        }
        i++;
        j = 0;
    }
    fou.close();
}
