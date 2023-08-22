#include "header.h"

std::string tab="/proc/stat";
buf::buffer <std::string> Obj_BuferRedAna;
buf::buffer <long> Obj_BuferAnaPrin;
std::mutex ra_mut;
std::condition_variable ra_prod;
std::condition_variable ra_cons;
size_t numThr=3;
std::mutex ap_mut;
std::condition_variable ap_prod;
std::condition_variable ap_cons;


wat::Watchdog* Ptr_Watchdog=wat::Watchdog::GetInstanceS(numThr);
  
      

void RunReader(){

    int i=30;
   rea::Reader Obj_Reader(tab);
   Obj_Reader.OpenSourceFile();
   Ptr_Watchdog->SetId(std::this_thread::get_id(),"Reader",1);

    while (i)
    {
        Obj_Reader.ReadSourceFile();
        //Obj_Reader.write();

        {
        std::unique_lock<std::mutex> Prod_Read(ra_mut);
        ra_prod.wait(Prod_Read,[] () { return Obj_BuferRedAna.GetValueUseBuf()<10;});

        Obj_BuferRedAna.bufferSetValue(Obj_Reader.GetDate());

        ra_cons.notify_one();
        }    


        Obj_Reader.ReOpenSourceFile();
        Ptr_Watchdog->SetTime(std::this_thread::get_id());
        i--;
       sleep(1);
    }
    


    Obj_Reader.CloseSourceFile();

 
}


void RunAnalizer(){

 int i=30;
   ana::Analizer Obj_Analizer(4);
   Ptr_Watchdog->SetId(std::this_thread::get_id(),"Analizer",2);

 while (i)
    {   
       std::vector<std::string> temp{};
        {

        std::unique_lock<std::mutex> Cons_Ana(ra_mut);
        ra_cons.wait(Cons_Ana,[] () { return Obj_BuferRedAna.GetValueUseBuf()>0;});

        //temp=(Obj_BuferRedAna.bufferGetValue());
        Obj_Analizer.SetRawData(Obj_BuferRedAna.bufferGetValue());

        ra_prod.notify_one();
        }  
        

        Obj_Analizer.CountRate();
        Obj_Analizer.changePtr();


        {
        std::unique_lock<std::mutex> Prod_Ana(ap_mut);
        ap_prod.wait(Prod_Ana,[] () { return Obj_BuferAnaPrin.GetValueUseBuf()<10;});

        Obj_BuferAnaPrin.bufferSetValue(Obj_Analizer.GetDate());

        ap_cons.notify_one();
        }   
        
        Ptr_Watchdog->SetTime(std::this_thread::get_id());
         i--;
       sleep(1);
    }

}
 
void RunPrinter(){

 int i=30;
   pri::Printer Obj_Printer(4);
    Ptr_Watchdog->SetId(std::this_thread::get_id(),"Printer",3);
  
 while (i)
    {   
      
        {

        std::unique_lock<std::mutex> Cons_Pri(ap_mut);
        ap_cons.wait(Cons_Pri,[] () { return Obj_BuferAnaPrin.GetValueUseBuf()>0;});

      
        Obj_Printer.SetprecentDate(Obj_BuferAnaPrin.bufferGetValue());

        ap_cons.notify_one();
        }  

        Obj_Printer.PrintDate();
        Ptr_Watchdog->SetTime(std::this_thread::get_id());
        i--;
       sleep(1);

    }  
}

void RunWatchdog(){
  int i=30;
 while (i)
    { 
        Ptr_Watchdog->CheckTime();
         i--;
       sleep(1);

    }  
}

void thr::runThread(){

    std::thread ReaderThread(RunReader);
    std::thread AnalizerThread(RunAnalizer);
    std::thread PrinterThread(RunPrinter);
    std::thread WatchdogThread(RunWatchdog);

    ReaderThread.join();
    AnalizerThread.join();
    PrinterThread.join();
    WatchdogThread.join();

}

