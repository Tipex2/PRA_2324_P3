#ifndef DICT_H
#define DICT_H

#include <string>
#include <stdexcept>
#include <list>
#include <vector>

template <typename V>
class Dict {
    public:

        virtual ~Dict() {}

        virtual void insert(std::string key, V value) = 0;

        virtual V search(std::string key) = 0;

        virtual V remove(std::string key) = 0;

        virtual int entries() = 0;
};

#endif
