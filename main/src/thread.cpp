#include "header.h"
 std::string tab="/proc/stat";


void RunReader(){

    int i=30;
   rea::Reader Obj_Reader(tab);
   Obj_Reader.OpenSourceFile();

    while (i)
    {
        Obj_Reader.ReadSourceFile();
        Obj_Reader.write();
        Obj_Reader.ReOpenSourceFile();
        i--;
       sleep(2);
    }
    


    Obj_Reader.CloseSourceFile();

 
}




void thr::runThread(){

    std::thread ReaderThread(RunReader);

    ReaderThread.join();

}
