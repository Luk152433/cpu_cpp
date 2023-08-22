#ifndef PRINTER_H
#define PRINTER_H

namespace pri{

    class Printer
    {
        private:
            std::vector<long> precentDate{};

        public:
            Printer(int nr);
            Printer();
            ~Printer();
            void SetprecentDate(std::vector<long>);
            void PrintDate();

    };

}

#endif
