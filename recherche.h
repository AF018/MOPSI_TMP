#pragma once

#include "partition.h"

bool find(queue<Partition> part_queue, const Partition& part);

int recherche_naive(Partition part, const int &n, const int &comparison_type);
int methode_tabou(Partition part, const int &l, const int &iteration_nb, const int& comparison_type);
int methode_recuit(Partition part, float alpha, const int &comparison_type);
