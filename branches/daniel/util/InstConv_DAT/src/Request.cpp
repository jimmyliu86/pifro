#include "Request.h"

Request::Request()
{
    //ctor
}

Request::~Request()
{
    //dtor
}

string Request::getSrc()
{
    return Src;
}

string Request::getDst()
{
    return Dst;
}

int Request::getIsrc()
{
    return Isrc;
}

int Request::getIdst()
{
    return Idst;
}

double Request::getQt()
{
    return Qt;
}

void Request::setSrc(string src)
{
    Src = src;
}

void Request::setDst(string dst)
{
    Dst = dst;
}

void Request::setIsrc(int isrc)
{
    Isrc = isrc;
}

void Request::setIdst(int idst)
{
    Idst = idst;
}

void Request::setQt(double qt)
{
    Qt = qt;
}
