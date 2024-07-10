// https://www.acmicpc.net/source/56186197
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

mt19937 engine(42);
uniform_int_distribution <int> distribution(0, 200'000'000);
auto gen = bind(distribution, engine);

void swap(int & a, int & b) {
    int temp = a;
    a = b;
    b = temp;
}

inline int minimum(int a, int b) {
    return a < b ? a : b;
}

inline int maximum(int a, int b) {
    return a > b ? a : b;
}

inline int middle(vector <int> & a, int start, int mod) {
    int p = a[start + gen() % mod], q = a[start + gen() % mod], r = a[start + gen() % mod];    
    if(p >= q && q >= r) {
        return q;
    } else if(q >= r && r >= p) {
        return r;
    } else {
        return p;
    }
}

int kth(vector <int> & a, int k) {
    int start = 0, end = (int) a.size() - 1, key, begin, first, last;
    --k;
    while(start < end) {
        key = middle(a, start, end - start + 1);
        last = end;
        begin = start;
        for(int i = start; i <= end; ++i) {
            if(a[i] == key) {
                swap(a[i], a[begin]);
                ++begin;
            }
        }
        first = begin;
        while(first < last) {
            while(first < last && a[first] < key) {
                ++first;
            }
            while(first < last && a[last] > key) {
                --last;
            }
            swap(a[first], a[last]);
        }
        if(a[first] < key) {
            ++first;
        }
        for(int i = start, j = maximum(begin, first + start - begin); j < first; ++i, ++j) {
            a[i] = a[j];
            a[j] = key;
        }
        begin = first + start - begin;
        if(k < begin) {
            end = maximum(start, begin - 1);
        } else if(k >= first) {
            start = minimum(end, first);
        } else {
            return key;
        }
    }
    return a[start];
}