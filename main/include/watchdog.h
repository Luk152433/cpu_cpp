#ifndef WATCHDOG_H
#define WATCHDOG_H

namespace wat{

  class Watchdog
  {
    private:
      static Watchdog *ptrInstanceS;
      static std::mutex mutexS;
      std::vector<std::thread::id> thrNum{};
      double diffTime{3};
      std::size_t valueOfThread{};
      std::map<std::thread::id,std::string> thr_id{};
      std::map<std::thread::id,std::chrono::steady_clock::time_point> thr_state{};
      std::map<std::thread::id,int32_t> thr_numMtx{};
   
      ~Watchdog();

      Watchdog(std::size_t value):valueOfThread(value)
      {
        thrNum.resize(value);
      }

    public:
      Watchdog(Watchdog &temp)=delete;
      void operator=(Watchdog &temp)=delete;
      static Watchdog* GetInstanceS(std::size_t& value);
      std::mutex WatMutexR;
      std::mutex WatMutexP;
      std::mutex WatMutexA;

      void SetTime(std::thread::id this_id);
      void SetId(std::thread::id this_id, std::string name,int32_t num);
      void CheckTime();
      
  };
  

 
    






}



#endif