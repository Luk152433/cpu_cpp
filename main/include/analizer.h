#ifndef ANALIZER_H
#define ANALIZER_H

namespace ana{

    class Analizer
    {
    private:
        typedef struct AssignDateS
        {
            std::string cpuName{};
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

        std::unique_ptr<AssignDateS[]> ptrCurrentDate{};
        std::unique_ptr<AssignDateS[]> ptrPrevDate{};
        std::unique_ptr<AssignDateS[]> TempPtr{};
    

    public:
        Analizer();
        Analizer(int nr);
        ~Analizer();

        void SetRawData(std::vector<std::string> buferDate);

    };
    
  
    



}




#endif