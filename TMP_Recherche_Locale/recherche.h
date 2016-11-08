#pragma once

#include "partition.h"

bool find(queue<Partition> part_queue, const Partition& part);

int recherche_naive(Partition part, const int &n, const int &comparison_type);
int methode_tabou(Partition part, const int &l, const int &n, const int& comparison_type);
//avec la comparaison plus fine des rails
int methode_tabou2(Partition part, const int &l, const int &n);
bool compare(Partition bestpart, Partition part1, int indicemax);
int methode_recuit(Partition part, float temp);
