#ifndef SLICE_H
#define SLICE_H

#include <iostream>
#include <vector>

using namespace std;

template <class T>
class slice {
    private:
        std::vector<T>* v;
        std::size_t offset;
        std::size_t count;
        std::size_t vector_size;

    public:
        slice(vector<T>* vec, int o, int c = 0) : v(vec), offset(o), count(c) {
            vector_size = v->size();
            if (count == 0 || count > vector_size - offset) {
                count = vector_size - offset;
            };
        };

    T& operator[](int index) {
        return at(index);
    };

    T& at(int index) {
        return v->at(offset + index);
    };    

    constexpr int size() {
        return count;
    }
};

#endif