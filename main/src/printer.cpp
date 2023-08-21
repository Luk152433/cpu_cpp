#include "header.h"

pri::Printer::Printer(int nr)
{
    precentDate.resize(nr);
}

pri::Printer::Printer()=default;
pri::Printer::~Printer()=default;

void pri::Printer::SetprecentDate(std::vector<long> buffDate)
{
    auto itr=precentDate.begin();
    for(auto& temp:buffDate)
    {
        *itr++=temp;
    }

    return;
}

void pri::Printer::PrintDate()
{   
    bool FlagTotal=true;
    int number=0;
    for(auto& temp:precentDate)
    {   
        if(FlagTotal)
        {
            std::cout<<"Total "<<temp<<'%'<<std::endl;
            FlagTotal=!FlagTotal;
        }else {
        std::cout<<"CPU"<<number++<<' '<<temp<<'%'<<std::endl;
        }
              
    }     

    std::cout<<std::endl;

    return;
}

