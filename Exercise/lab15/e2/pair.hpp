#ifndef L15E2_PAIR_HPP
#define L15E2_PAIR_HPP

#include <iostream>

template<class T1, class T2>
class Pair {
public:
    T1 key;
    T2 value;

    Pair(T1 k, T2 v) : key(k), value(v) {};

    // bool operator<(const Pair<T1, T2> &p) const;

    // // template<typename U1, typename U2>
    // friend std::ostream &operator<<(std::ostream &os, const Pair<T1, T2> &p);

    bool operator<(const Pair<T1, T2> &p) const {
        return key < p.key;
    }

    // template<typename U1, typename U2>
    friend std::ostream &operator<<(std::ostream &os, const Pair<T1, T2> &p){
        os << p.key << " " << p.value << std::endl;
        return os;
    }
};

#endif // L15E2_PAIR_HPP