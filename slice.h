#ifndef SLICE_H
#define SLICE_H

#include <vector>
#include <iostream>

class slice 
{
    private:
        std::vector<long int> *v;
        std::size_t offset;
        std::size_t count;

    public:
        slice(std::vector<long int> *vec, int o, int, c): v(vec), offset(o), count(c) {};

        void at(index) {
            std::cout << v->at(index + offset);
        }


}

#endif