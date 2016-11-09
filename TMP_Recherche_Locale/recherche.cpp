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
    while(k<n and not min_local)
    {
        // Si on ne trouve pas de meilleur score, min_local gardera la valeur true
        min_local = true;
        // Recherche parmi les voisins (par operation de swap)
        for (int i=0; i<part.size()-1; i++)
        {
            for (int j=i+1; j<part.size(); j++)
            {
                if (part.swap(i,j).fill(comparison_type,false) < score)
                {
                    best_part = part.swap(i,j);
                    score = best_part.fill(comparison_type,false);
                    min_local = false;
                }
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
    while(k<n)
    {
        // On pose best_score égal au départ à la valeur maximale d'un entier en C++
        // car sinon l'algorithme peut ne pas quitter les minima locaux entourés
        // de scores égaux à part.size()
        best_score = std::numeric_limits<int>::max();
        // Recherche parmi les voisins (par operation de swap)
        for (int i=0; i<part.size()-1; i++)
        {
            for (int j=i+1; j<part.size(); j++)
            {
                // Test sur le score de la partition "swappee" et sa non-appartenance
                // a la liste tabou (la deuxieme condition est vraie dans ce cas)
                if (part.swap(i,j).fill(comparison_type,false) < best_score and
                    not find(part_queue,part.swap(i,j)))
                {
                    best_part = part.swap(i,j);
                    best_score = best_part.fill(comparison_type,false);
                }
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
    cout << "La repartition optimale trouvee par methode tabou est :" << endl;
    cout << endl;
    opt_part.show();
    opt_part.fill(comparison_type,true);
    return opt_score;
}

/*

int methode_tabou2(Partition part, const int& l, const int& n)
{
    queue<Partition> part_queue;
    for (int i=0; i<l; i++)
    {
        part_queue.push(part);
    }
    int k=0;
    // Partition et score associe au meilleur element trouve jusqu'ici
    Partition opt_part;
    // Partition et score associe au meilleur voisin de l'element considere
    Partition best_part;
    best_part=part;
    opt_part=part;
    while(k<n)
    {
        // On rajoute 1 car sinon l'algorithme ne peut quitter les minima locaux entourés
        // de scores égaux à part.size()


        // Recherche parmi les voisins (par operation de swap)
        for (int i=0; i<part.size()-1; i++)
        {
            for (int j=i+1; j<part.size(); j++)
            {
                // Test sur le score de la partition "swappee" et sa non-appartenance
                // a la liste tabou (la deuxieme condition est vraie dans ce cas)

                if ((not find(part_queue,part.swap(i,j)))){
                    cout<<"test"<<endl;
                    if(compare(best_part, part.swap(i,j),j)==1){
                        cout<<compare(best_part, part.swap(i,j),j)<<endl;
                        best_part = part.swap(i,j);
                    }
                }
            }
        }
        part = best_part;
        // On ajoute le voisin de score minimal a la liste tabou
        part_queue.pop();
        part_queue.push(best_part);
        // On remplace l'optimum si le voisin de score minimal a un score inferieur
        if (compare(opt_part,best_part,part.size()-1)==1)
        {
            opt_part = best_part;
        }
        k++;
    }
    cout << "La repartition optimale trouvee par methode tabou est :" << endl;
    cout << endl;
    opt_part.show();
    opt_part.fill(1,true);
    return 0;
}
//indicemax est l'indice du plus haut ensemble swappe
//true si part1 est meilleure que bestpart au sens suivant :
//si le dernier élément de l'ensemble swappé (part1) et de celui de référence (best part) sont sur le même rail :
//celui de plus haut rang est le meilleur
//sinon, c'est celui avec le moins de rails
bool compare(Partition bestpart, Partition part1,int indicemax){
    bestpart.show();
    part1.show();
    int nouvbestmini=0;
    int bestmini=0;
    int nouvmini1=0;
    int mini1=0;
    bool bestnouvrail;
    bool nouvrail1;
    int nbbestrail=0;
    int nbrail1=0;
    //std::cout<<"test"<<std::endl;
    //on compare indicemax ensemble pour aller jusqu'à celui swappé
    for (int indice=0;indice<=indicemax;indice++){
        //std::cout<<"indicemax "<<indicemax<<std::endl;

        //on calcule le dernier élément de l'ensemble
        bestnouvrail=bestpart.find_min_elem(nouvbestmini,indice,bestmini);
        cout<<"a t on changé de rail best "<<bestnouvrail<<endl;
        nouvrail1=part1.find_min_elem(nouvmini1,indice,mini1);
        cout<<"a t on changé de rail part "<<nouvrail1<<endl;

        //si on a changé de rail, on compte un rail de plus et on retient le plus dernier élément
            if (bestnouvrail){
                nbbestrail+=1;
                bestmini=nouvbestmini;
            }
            //sinon, le dernier élément est le plus petit
            else{
                bestpart.find_min_elem(bestmini,indice,0);
            }
            //de même pour l'autre liste
            if (nouvrail1){
                nbrail1+=1;
                mini1=nouvmini1;
            }
            else{
                bestpart.find_min_elem(mini1,indice,0);
            }
            std::cout<<"dernier indice bestpart "<<bestmini<<std::endl;
            std::cout<<"dernier indice part1 "<<mini1<<std::endl;
            cout<<"nombre rails best "<<nbbestrail<<endl;
            cout<<"nb rails 1 "<<nbrail1<<endl;
            std::cout<<"indice "<<indice<<std::endl;

    }
    //si best a moins de rail, nouvpart n'est pas le meilleur
    if (nbbestrail<nbrail1){
        //cout<<false<<endl;
        return false;
    }
    if (nbbestrail>nbrail1){
        cout<<true<<endl;
        return true;
    }
    //si il y a autant de rail
    else{
        //nouvpart est le meilleur si le dernier élément du k eme ensemble est le plus élevé
        if(bestmini<mini1){
            //cout<<true<<endl;
            return true;
        }
        //cout<<false<<endl;
        return false;
    }

}
*/

int methode_recuit(Partition part, float alpha, const int &comparison_type){
    int n=part.size(); //Taille
    Partition opt_part;
    Partition best_part;
    float temperature=10.0;
    float proba=0;
    float ener=0;
    float score=0;
    int k=0;
    //on regarde les voisins
    int best_score = part.size()+1;
    int opt_score=best_score;
    while (temperature > 1){
        for (int i=0;i<n-1;i++){
            for (int j=i+1;j<n;j++){
                score=part.swap(i,j).fill(comparison_type,false);
                //si on a trouvé un meilleur voisin
                if (score< best_score){
                    best_part = part.swap(i,j);
                    best_score = score;
                }
            }

        }
        if (best_score<opt_score){
            opt_part=best_part;
            opt_score=best_score;
        }
        else{
            ener=float(exp(-1*(best_score-opt_score)/temperature));
            proba=rand()*1.0/RAND_MAX;
            if(proba<ener){
                opt_part = best_part;
            }
        }
        temperature=temperature*1.0/(1+alpha*k);
        k=k+1;
    }
    opt_part.show();
    opt_part.fill(comparison_type,true);
    cout<<"Nombre d'itérations "<<k<<endl;
    cout<<"Le meilleur score par la méthode de recuit est "<<opt_score<<endl;
    return opt_score;
}


