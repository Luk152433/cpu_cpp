#include "header.h"


    ana::Analizer::Analizer(int nr):ptrCurrentDate(new AssignDateS[nr]),ptrPrevDate(new AssignDateS[nr])
{
    AllPercentValue.resize(nr);
}

ana::Analizer::Analizer()=default;
ana::Analizer::~Analizer()=default;

 void ana::Analizer::SetRawData(std::vector<std::string> buferDate)
 {  
    int i=0;

    while(i<4)
    {   
        std::string parsBuff{};
        std::stringstream stringToStrim(buferDate[i]);

        std::vector<std::string> chopString{};

        while(stringToStrim >> parsBuff)
        {
            chopString.push_back(parsBuff);
        }

        ptrCurrentDate[i].cpuName   =   chopString[0];
        ptrCurrentDate[i].user      =   std::stol(chopString[1],nullptr,10);
        ptrCurrentDate[i].nice      =   std::stol(chopString[2],nullptr,10);
        ptrCurrentDate[i].system    =   std::stol(chopString[3],nullptr,10);
        ptrCurrentDate[i].idle      =   std::stol(chopString[4],nullptr,10);
        ptrCurrentDate[i].iowait    =   std::stol(chopString[5],nullptr,10);
        ptrCurrentDate[i].irq       =   std::stol(chopString[6],nullptr,10);
        ptrCurrentDate[i].softirq   =   std::stol(chopString[7],nullptr,10);
        ptrCurrentDate[i].steal     =   std::stol(chopString[8],nullptr,10);
        ptrCurrentDate[i].guest     =   std::stol(chopString[9],nullptr,10);
        ptrCurrentDate[i].guestNice =   std::stol(chopString[10],nullptr,10);
      
        // std::cout <<ptrCurrentDate[i].cpuName<<" ";
        // std::cout <<ptrCurrentDate[i].user<<" ";
        // std::cout <<ptrCurrentDate[i].nice<<" ";
        // std::cout <<ptrCurrentDate[i].system<<" ";
        // std::cout <<ptrCurrentDate[i].idle<<" ";
        // std::cout <<ptrCurrentDate[i].iowait<<" ";
        // std::cout <<ptrCurrentDate[i].irq<<" ";
        // std::cout <<ptrCurrentDate[i].softirq<<" ";
        // std::cout <<ptrCurrentDate[i].steal<<" ";
        // std::cout <<ptrCurrentDate[i].guest<<" ";
        // std::cout <<ptrCurrentDate[i].guestNice<<std::endl;

        i++;
    }

    return;
 }

void ana::Analizer::CountRate()
{
    for(uint8_t i=0;i<4;i++)
    {
        long PrevIdle = ptrPrevDate[i].idle + ptrPrevDate[i].iowait;
        long Idle = ptrCurrentDate[i].idle +  ptrCurrentDate[i].iowait;

        long PrevNonIdle = ptrPrevDate[i].user + ptrPrevDate[i].nice + ptrPrevDate[i].system + ptrPrevDate[i].irq + ptrPrevDate[i].softirq + ptrPrevDate[i].steal;  
        long NonIdle = ptrCurrentDate[i].user + ptrCurrentDate[i].nice + ptrCurrentDate[i].system + ptrCurrentDate[i].irq + ptrCurrentDate[i].softirq + ptrCurrentDate[i].steal;

        long PrevTotal = PrevIdle + PrevNonIdle;
        long Total = Idle + NonIdle;

        double totald = (double)Total - (double)PrevTotal;
        double idled = (double)Idle - (double)PrevIdle;
        
 
        AllPercentValue[i]=(1000*(totald - idled)/totald+1)/10;

    }

    return;

}

void ana::Analizer::write()
{
    for(int i=0;i<4;i++)
    {
        std::cout<<AllPercentValue[i]<<std::endl;
    }
    std::cout<<std::endl;
}

void ana::Analizer::changePtr()
{
    TempPtr=std::move(ptrPrevDate);
    ptrPrevDate=std::move(ptrCurrentDate);
    ptrCurrentDate=std::move(TempPtr);

    return;
}

std::vector<long>* ana::Analizer::GetDate()
{
    return &AllPercentValue;
}