#include "header.h"

pri::Printer::Printer(int nr)
{
    precentDate.resize(nr);
}

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
    for(auto& temp:precentDate)
    {
        std::cout<<temp<<std::endl;
    }

    std::cout<<std::endl;

    return;
}

