#include "header.h"
std::string tab="/proc/stat";
buf::buffer <std::string> Obj_BuferRedAna;
buf::buffer <long> Obj_BuferAnaPrin;
std::mutex ra_mut;
std::condition_variable ra_prod;
std::condition_variable ra_cons;

std::mutex ap_mut;
std::condition_variable ap_prod;
std::condition_variable ap_cons;

void RunReader(){

    int i=30;
   rea::Reader Obj_Reader(tab);
   Obj_Reader.OpenSourceFile();

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
        i--;
       sleep(1);
    }
    


    Obj_Reader.CloseSourceFile();

 
}


void RunAnalizer(){

 int i=30;
   ana::Analizer Obj_Analizer(4);

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
        
        // std::cout<<temp[0];
//         std::cout<<temp[1];
     //      for (const std::string& str : temp) {
      // std::cout << str << std::endl;
       //  }
        Obj_Analizer.CountRate();
        //Obj_Analizer.write();
        Obj_Analizer.changePtr();


         {
        std::unique_lock<std::mutex> Prod_Ana(ap_mut);
        ap_prod.wait(Prod_Ana,[] () { return Obj_BuferAnaPrin.GetValueUseBuf()<10;});

        Obj_BuferAnaPrin.bufferSetValue(Obj_Analizer.GetDate());

        ap_cons.notify_one();
         }   
        

         i--;
       sleep(1);
    }

}
 
void RunPrinter(){

 int i=30;
   pri::Printer Obj_Printer(4);

 while (i)
    {   
      
        {

        std::unique_lock<std::mutex> Cons_Pri(ap_mut);
        ap_cons.wait(Cons_Pri,[] () { return Obj_BuferAnaPrin.GetValueUseBuf()>0;});

        //temp=(Obj_BuferRedAna.bufferGetValue());
        Obj_Printer.SetprecentDate(Obj_BuferAnaPrin.bufferGetValue());

        ap_cons.notify_one();
        }  

        Obj_Printer.PrintDate();
  
        i--;
       sleep(1);

    }  
}

void thr::runThread(){

    std::thread ReaderThread(RunReader);
    std::thread AnalizerThread(RunAnalizer);
    std::thread PrinterThread(RunPrinter);

    ReaderThread.join();
    AnalizerThread.join();
    PrinterThread.join();

}
