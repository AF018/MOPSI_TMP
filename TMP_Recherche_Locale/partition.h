#pragma once

#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
using namespace std;

#include <assert.h>

class Partition
{
    vector< vector<int> > vect;
public:
    Partition();
    Partition(const vector<vector<int> >& init_vect);
    ~Partition();
    vector< vector<int> > get_vect() const;
    int size() const;
    bool operator==(const Partition& part) const;
    void show() const;
    Partition swap(int i, int j) const;
    bool find_min_elem(int& next_elem, const int& k, const int& inf_bound) const;
    int fill(const bool& show) const;
};
