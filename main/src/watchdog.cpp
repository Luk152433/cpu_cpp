#include "header.h"


std::mutex wat::Watchdog::mutexS;

wat::Watchdog* wat::Watchdog::ptrInstanceS {nullptr};


wat::Watchdog* wat::Watchdog::GetInstanceS(std::size_t& value)
 {
        std::lock_guard<std::mutex> lock(mutexS);

    if (ptrInstanceS == nullptr)
    {
        ptrInstanceS = new Watchdog(value);
    }
    return ptrInstanceS;

 }

 void wat::Watchdog::SetId(std::thread::id this_id, std::string name,int32_t num)
 {

    thr_id.insert(std::pair<std::thread::id,std::string>(this_id,name));
   thr_numMtx.insert(std::pair<std::thread::id,int32_t>(this_id,num));
    thr_state.insert(std::pair<std::thread::id,std::chrono::steady_clock::time_point>(this_id,std::chrono::steady_clock::now()));

 }

  void wat::Watchdog::SetTime(std::thread::id this_id)
  {

        //std::unique_lock<std::mutex> ReadTime();
        thr_state[this_id]=std::chrono::steady_clock::now();
         if (thr_numMtx[this_id]==1)
              { 
                std::unique_lock<std::mutex> CheckTime(WatMutexR);
                 thr_state[this_id]=std::chrono::steady_clock::now();

              }else if(thr_numMtx[this_id]==2)
              {
                std::unique_lock<std::mutex> CheckTime(WatMutexP);
               thr_state[this_id]=std::chrono::steady_clock::now();

              }
              else if(thr_numMtx[this_id]==3)
              {
                std::unique_lock<std::mutex> CheckTime(WatMutexA);
               thr_state[this_id]=std::chrono::steady_clock::now();
              }   


  }

void wat::Watchdog::CheckTime()
{
    std::chrono::duration<double> elapsed_seconds;

    for(auto& temp:thr_id)
    {   
        {
            

            
              if (thr_numMtx[temp.first]==1)
              { 
                std::unique_lock<std::mutex> CheckTime(WatMutexR);

                const auto current = std::chrono::steady_clock::now();
              elapsed_seconds = current - thr_state[temp.first];

              }else if(thr_numMtx[temp.first]==2)
              {
                std::unique_lock<std::mutex> CheckTime(WatMutexP);
                const auto current = std::chrono::steady_clock::now();
              elapsed_seconds = current - thr_state[temp.first];

              }
              else if(thr_numMtx[temp.first]==3)
              {
                std::unique_lock<std::mutex> CheckTime(WatMutexA);
                const auto current = std::chrono::steady_clock::now();
              elapsed_seconds = current - thr_state[temp.first];
              }
              
              
        }
        if(diffTime< elapsed_seconds.count() )
        {
            std::cout<<temp.second<<" moduł chwilowo przestał pracować"<<std::endl;
        }
    }

}

