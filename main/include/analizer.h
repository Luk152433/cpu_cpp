#ifndef ANALIZER_H
#define ANALIZER_H

namespace ana{

    class Analizer
    {
    private:
        typedef struct AssignDateS
        {
            std::string nname{};
            long user{};
            long nice{};
            long system{};
            long idle{};
            long iowait{};
            long irq{}; 
            long softirq{};
            long steal{};
            long guest{};
            long guestNice{};

        }AssignDate;

        std::unique_ptr<AssignDateS> ptrCurrentDate{};
        std::unique_ptr<AssignDateS> ptrPrevDate{};
    

    public:
        Analizer(uint8_t CoreNum);
        ~Analizer();
    };
    
  
    



}




#endif