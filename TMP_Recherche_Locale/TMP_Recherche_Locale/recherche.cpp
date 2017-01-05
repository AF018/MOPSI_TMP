#include "recherche.h"

void time_test()
{
    // Teste le temps de résolution pour une même instance

    // Reste à insérer le nombre de wagons et à choisir comment évoluent les paramètres
    Partition part_test(100,0,false);
    double timer=(double)(clock());
    methode_tabou(part_test,100,50,2,true);
    timer = ((double)(clock())-timer)/CLOCKS_PER_SEC;
    cout << timer << " s" << endl;
    timer=(double)(clock());
    methode_recuit(part_test,0.01,2,true);
    timer = ((double)(clock())-timer)/CLOCKS_PER_SEC;
    cout << timer << " s" << endl;
}

int constante(float n,float m)
{   int d=floor(n/m);
    int val= ceil((m-1)*d*d/n+1/m);
    cout<<"La constante de la conjecture vaut "<<val<<endl;
    return val;
}

int calcul(int n,int nbwag,int nbdirec, float alpha){
    //effectue n tests selon la méthode recuit (au paramètre alpha) pour des instances générées aléatoirement
    //comportant nbwag wagons et nbdirec directions.
    int nb=nbwag;
    int a=nbwag;
    int cons;
    for (int i=0;i<n;i++){
        Partition part(nbwag,nbdirec,false);
        cons=constante(part.nbelem(),part.mincardi());

        cout<<"Mini cardi "<<part.mincardi()<<endl;
        a=methode_recuit(part,alpha,2,false);
        cout<<"Methode recuit "<<a<<endl;
        if (a<nb){
            nb=a;
        }
        if(cons<a){
            cout<<"XXXXXXXXXXXXXXXXXXXXXXXXXXXX"<<endl;
            cout<<"La constante vaut "<<cons<<endl;
            part.show();
            return (1111111111);
        }
    }
    cout<<"Le minimum est "<<nb<<endl;
    return 0;
}

void bound_test(const int& sim_nb,const int& nb_wag, const float& alpha)
{
    // Effectue sim_nb simulations de répartitions de trains de nb_wag wagons générés aléatoirement
    // Affiche les résultats dans un graphique (points bleus) avec la borne supérieure de l'article
    // représentée par une barre rouge et la conjecture par un point vert.
    // Les simulations sont effectuées par recuit simulé pour l'instant
    int bound = ceil(nb_wag/4+0.5);
    cout << bound << endl;

    vector<int> results;
    vector<int> conje;
    for (int i=0;i<sim_nb;i++)
    {
        Partition part(nb_wag,0,false);
        int conj=constante(part.nbelem(),part.mincardi());
        results.push_back(methode_recuit(part,alpha,2,true));
        conje.push_back(conj);
    }
    Window window = openWindow(30+sim_nb*6,512);
    drawLine(0,502,30+sim_nb*6,502,BLACK);
    drawLine(10,0,10,512,BLACK);
    drawLine(10,512-(10+10*bound),(30+sim_nb*6),512-(10+10*bound),RED);
    click();
    for (int i=0;i<sim_nb;i++)
    {
        fillCircle(12+i*6,512-(10+10*results[i]),2,BLUE);
        fillCircle(12+i*6,512-(10+10*conje[i]),2,GREEN);
    }
    click();
    cout << bound << endl;
}

bool find(queue<Partition> part_queue, const Partition& part)
{
    // Cherche un element dans une queue : renvoie true si l'element est trouve
    // et false dans le cas contraire
    Partition test;
    // On utilise size car la longueur de la file est modifiee
    // au fil des opérations
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

int methode_tabou(Partition part, const int& l, const int& iteration_nb, const int &comparison_type, const bool& show_results)
{
    // Algorithme de recherche locale utilisant la méthode tabou
    // Complexité en O(iteration_nb*vect.size()^3*n²*(l+n))
    // Rappel : n est le nombre de wagons
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
    while(k<iteration_nb)
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
    if(not show_results)
    {
        cout << "La repartition optimale trouvee par methode tabou " <<comparison_type<<" est :" << endl;
        cout << endl;
        opt_part.show();
        opt_part.fill(comparison_type,true);
    }
    return opt_score;
}

int methode_recuit(Partition part, float alpha, const int &comparison_type, const bool &show_results){
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
    if (not show_results)
    {
        opt_part.show();
        opt_part.fill(comparison_type,true);
        cout<<"Nombre d'iterations "<<k<<endl;
    }
    if (comparison_type==1){
        cout<<"Le meilleur score par la methode de recuit "<<comparison_type<<" est "<<best_score<<endl;
        if (not show_results)
        {
            return best_score;
        }
    }
    else{
            int n2=part.nbelem();
            if (not show_results)
            {
                cout<<"Le meilleur score par la methode de recuit "<<comparison_type<<" est "<<ceil(1.0*best_score/n2*1.0)<<endl;
            }
            return ceil(1.0*best_score/n2*1.0);
    }
}


