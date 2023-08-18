#include "header.h"
std::string tab="/proc/stat";
buf::buffer <std::string> Obj_BuferRedAna;
std::mutex ra_mut;
std::condition_variable ra_prod;
std::condition_variable ra_cons;

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
   ana::Analizer Obj_Analizer(2);

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

         i--;
       sleep(1);
    }

}
 


void thr::runThread(){

    std::thread ReaderThread(RunReader);
    std::thread AnalizerThread(RunAnalizer);

    ReaderThread.join();
    AnalizerThread.join();

}
