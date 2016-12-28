#pragma once

#include <Imagine/Graphics.h>
using namespace Imagine;

#include "partition.h"

void time_test();

int constante(float n,float m);
int calcul(int n,int nbwag,int nbdirec, float alpha);
void bound_test(const int& sim_nb, const int& nb_wag, const float &alpha);

bool find(queue<Partition> part_queue, const Partition& part);

int recherche_naive(Partition part, const int &n, const int &comparison_type);
int methode_tabou(Partition part, const int &l, const int &iteration_nb, const int& comparison_type, const bool& show_results);
int methode_recuit(Partition part, float alpha, const int &comparison_type, const bool& show_results);
