#pragma once

#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <limits>
using namespace std;

#include "math.h"
#include <assert.h>

class Partition
{
    int n;
    vector< vector<int> > vect;
public:
    Partition();
    Partition(const vector<vector<int> >& init_vect);
    Partition(const char* filename);
    ~Partition();
    vector< vector<int> > get_vect() const;
    int size() const;
    bool operator==(const Partition& part) const;
    void show() const;
    Partition swap(int i, int j) const;
    bool find_min_elem(int& next_elem, const int& k, const int& inf_bound) const;
    int fill(const int &comparison_type, const bool& show) const;
};
