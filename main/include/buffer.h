#ifndef BUFFER_H
#define BUFFER_H

namespace buf{

    template <typename T>
    class buffer
    {
        private:
       std::list<std::vector<T>> bufList;
        
        uint8_t curentFillBuffer{0};
        typename std::list<std::vector<T>>::iterator head;
        typename std::list<std::vector<T>>::iterator tail;
        uint8_t maxSize{};
    
        public:
        buffer();
        ~buffer();
        void bufferSetValue(std::vector<T>* reciveValue);
        std::vector<T> bufferGetValue();
        uint8_t GetValueUseBuf();
        
    };
    
    template <typename T>
    buffer<T>::buffer():bufList(10,std::vector<T>(1,(""))),maxSize{10}
    {
        head=bufList.begin();
        tail=bufList.begin();
    }

    template <typename T>
    void buffer<T>::bufferSetValue(std::vector<T>* reciveValue){

        *head=*reciveValue;
        head++;
        curentFillBuffer++;
        if(head==bufList.end()){
            head=bufList.begin();
        }
   
            
    }
    
    template <typename T>
    std::vector<T> buffer<T>::bufferGetValue(){

        auto temp=*tail;
        curentFillBuffer--;
        tail++;
        if(tail==bufList.end()){
            tail=bufList.begin();
        }
        return temp;
    }

    template <typename T>
    uint8_t buffer<T>::GetValueUseBuf(){

        return curentFillBuffer;
    }

     template <typename T>
    buffer<T>::~buffer()
    {
        
    }

}



#endif