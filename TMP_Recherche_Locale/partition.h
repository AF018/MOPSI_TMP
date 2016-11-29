#pragma once

#include <ctime>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <limits>
using namespace std;

#include "math.h"

class Partition
{
    int n;
    vector< vector<int> > vect;
public:
    Partition();
    Partition(const vector<vector<int> >& init_vect);
    Partition(const char* filename);
    Partition(const int& wagons_nb, const int& groups_nb);
    ~Partition();
    vector< vector<int> > get_vect() const;
    int size() const;
    bool operator==(const Partition& part) const;
    void show() const;
    Partition swap(const int& i,const int& j) const;
    Partition block_swap(const int& i,const int& j,const int& k) const;
    vector<Partition> neighbors() const;
    bool find_min_elem(int& next_elem, const int& k, const int& inf_bound) const;
    int fill(const int &comparison_type, const bool& show) const;
};
