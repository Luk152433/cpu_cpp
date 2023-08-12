#ifndef BUFFER_H
#define BUFFER_H

namespace buf{

    template <typename T>
    class buffer
    {
        private:
        std::vector<T> vec{};

        public:
        buffer(/* args */);
        ~buffer();
        void bufferSetValue(std::vector<T>* reciveValue);
        T bufferGetValue();

    };
    
    template <typename T>
    void buffer<T>::bufferSetValue(std::vector<T>* reciveValue){

        vec.insert(reciveValue->begin,reciveValue->end);

    }
    


}



#endif