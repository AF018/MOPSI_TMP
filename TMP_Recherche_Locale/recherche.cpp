#include "recherche.h"

bool find(queue<Partition> part_queue, const Partition& part)
{
    // Cherche un element dans une queue : renvoie true si l'element est trouve
    // et false dans le cas contraire
    Partition test;
    int size = part_queue.size();
    for (int i=0; i<size; i++)
    {
        test = part_queue.front();
        if (test==part)
        {
            return true;
        }
        part_queue.pop();
    }
    return false;
}

int recherche_naive(Partition part, const int& n, const int& comparison_type)
{
    // On regarde si on trouve un meilleur candidat que la partition parmi ses voisins par swap
    // Si c'est le cas, le meilleur candidat devient la nouvelle partition, sinon on s'arrête (grace a min_local)
    // On itere ce procede n fois au plus
    int k=0;
    bool min_local = false;
    int score = part.fill(comparison_type,false);
    Partition best_part;
    // Vecteur des voisins de la partition consideree
    vector<Partition> swap_neighbors;
    while(k<n and not min_local)
    {
        // Si on ne trouve pas de meilleur score, min_local gardera la valeur true
        min_local = true;
        // Recherche parmi les voisins (par operation de swap)
        swap_neighbors = part.neighbors();
        for (int i=0; i<swap_neighbors.size(); i++)
        {
                if (swap_neighbors[i].fill(comparison_type,false) < score)
                {
                    best_part = swap_neighbors[i];
                    score = best_part.fill(comparison_type,false);
                    min_local = false;
                }
        }
        part = best_part;
        k++;
    }
    if (min_local)
    {
        cout << "Un minimum local a ete atteint a l'iteration " << k << endl;
    }
    cout << "La repartition finale trouvee par recherche locale naive est :" << endl;
    part.show();
    part.fill(comparison_type,true);
    return score;
}

int methode_tabou(Partition part, const int& l, const int& n, const int &comparison_type)
{
    queue<Partition> part_queue;
    for (int i=0; i<l; i++)
    {
        part_queue.push(part);
    }
    int k=0;
    // Partition et score associe au meilleur element trouve jusqu'ici
    Partition opt_part;
    int opt_score = std::numeric_limits<int>::max();
    // Partition et score associe au meilleur voisin de l'element considere
    Partition best_part;
    int best_score;
    // Vecteur des voisins de la partition consideree
    vector<Partition> swap_neighbors;
    while(k<n)
    {
        // On pose best_score égal au départ à la valeur maximale d'un entier en C++
        // car sinon l'algorithme peut ne pas quitter les minima locaux entourés
        // de scores égaux à part.size()
        best_score = std::numeric_limits<int>::max();
        // Recherche parmi les voisins (par operation de swap)
        swap_neighbors = part.neighbors();
        for (int i=0; i<swap_neighbors.size(); i++)
        {
            // Test sur le score de la partition "swappee" et sa non-appartenance
            // a la liste tabou (la deuxieme condition est vraie dans ce cas)
            if (swap_neighbors[i].fill(comparison_type,false) < best_score and
                not find(part_queue,swap_neighbors[i]))
            {
                best_part = swap_neighbors[i];
                best_score = best_part.fill(comparison_type,false);
            }
        }
        part = best_part;
        // On ajoute le voisin de score minimal a la liste tabou
        part_queue.pop();
        part_queue.push(best_part);
        // On remplace l'optimum si le voisin de score minimal a un score inferieur
        if (best_score < opt_score)
        {
            opt_part = best_part;
            opt_score = best_score;
        }
        k++;
    }
    cout << "La repartition optimale trouvee par methode tabou " <<comparison_type<<" est :" << endl;
    cout << endl;
    opt_part.show();
    opt_part.fill(comparison_type,true);
    return opt_score;
}

int methode_recuit(Partition part, float alpha, const int &comparison_type){
    int n=part.size(); //Taille
    Partition best_part=part;
    Partition opt_part=part;
    float temperature=10.0;
    float proba=0;
    float ener=0;
    float score=0;
    int k=0;
    //on regarde les voisins
    int best_score = std::numeric_limits<int>::max();
    while (temperature > 1){
        for (int i=0;i<n-1;i++){
            for (int j=i+1;j<n;j++){
                score=best_part.swap(i,j).fill(comparison_type,false);
                part=part.swap(i,j);
                //si on a trouvé un meilleur voisin
                if (score<best_score){
                    best_part = best_part.swap(i,j);
                    best_score = score;
                    opt_part=best_part;
                }
                else{
                    ener=float(exp(-1*(score-best_score)/temperature));
                    proba=rand()*1.0/RAND_MAX;
                    if(proba<ener){
                        best_part = best_part.swap(i,j);
                    }
                }

            }

        }
        temperature=temperature*1.0/(1+alpha*k);
        k=k+1;
    }
    opt_part.show();
    opt_part.fill(comparison_type,true);
    cout<<"Nombre d'iterations "<<k<<endl;
    cout<<"Le meilleur score par la methode de recuit "<<comparison_type<<" est "<<best_score<<endl;
    return best_score;
}


