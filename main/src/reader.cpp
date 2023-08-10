#include "header.h"


rea::Reader::Reader(std::string arg_path):path(arg_path)
{

}
rea::Reader::~Reader(){}

void rea::Reader::OpenSourceFile()
{
    infile.open(path);
    return;
}

void rea::Reader::ReOpenSourceFile()
{
    infile.close();
    infile.open(path);
    return;
}

void rea::Reader::CloseSourceFile()
{
    infile.close();
    return;
}

void rea::Reader::ReadSourceFile()
{   
    std::string line{};
    vec.clear();
    std::vector<std::string>::iterator iter=vec.begin();

    while(getline(infile,line)){
        
        vec.push_back(line);
        line.clear();

    }
}

void rea::Reader::write()
{   int i=0;
    while (i<2)
    {
            std::cout<<vec[i]<<std::endl;
        i++;
    }
    std::cout<<'\n';

}