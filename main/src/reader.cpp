#include "header.h"


rea::Reader::Reader(std::string arg_path):path(arg_path)
{

}
rea::Reader::~Reader()=default;

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
    int i=0;
    while(getline(infile,line)  && i<4   ){
        
        vec.push_back(line);
        line.clear();
        i++;
    }
}

std::vector<std::string>* rea::Reader::GetDate()
{
    return &vec;
}

void rea::Reader::write()
{   int i=0;
    while (i<4)
    {
            std::cout<<vec[i]<<std::endl;
        i++;
    }
    std::cout<<'\n';
 
}