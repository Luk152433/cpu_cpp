#ifndef READER_H
#define READER_H

namespace rea{

    class Reader
    {
        private:
            std::string path;
            std::ifstream infile;
            std::vector<std::string> vec{};


        public:
            Reader(std::string arg_path);
            ~Reader();
            void OpenSourceFile();
            void ReOpenSourceFile();
            void CloseSourceFile();
            void ReadSourceFile();
            void write();
    };
    
 
}


#endif