#include "partition.h"

Partition::Partition()
{
}

Partition::Partition(const vector<vector<int> >& init_vect)
{
    // Copie de vecteur : pas de problème de mémoire
    vect = init_vect;
    n = 0;
    // Tri des elements dans chaque ensemble pour une manipulation plus aisee
    // au moment du remplissage dans les rails (besoin d'uns structure de type pile
    // Complexité totale en O(n*log(n))
    vector< vector<int> >::iterator it = vect.begin();
    for (; it != vect.end(); it++)
    {
        sort((*it).begin(),(*it).end());
        n+=((*it).size());
    }
}

Partition::Partition(const char* filename)
{
    // Construit une partition à partir d'un fichier txt (utiliser un chemin absolu)
    // les éléments sont tous immédiatement suivis d'une virgule,
    // les ensembles sont séparés par des retours à la ligne
    n = 0;
    ifstream file(filename);
    string line;
    int ind=0;
    int len;
    int start_pos;
    while (getline(file,line))
    {
        vect.push_back(vector<int>());
        start_pos = 0;
        len = line.find(',',0);
        vect[ind].push_back(atoi(line.substr(start_pos,len).c_str()));
        n++;
        while(start_pos+len<(line.size()-2))
        {
            // Recherche de la position du prochain nombre
            start_pos += len+1;
            len = line.find(',',start_pos)-start_pos;
            vect[ind].push_back(atoi(line.substr(start_pos,len).c_str()));
            n++;
        }
        ind++;
    }
    file.close();
    vector< vector<int> >::iterator it = vect.begin();
    for (; it != vect.end(); it++)
    {
        sort((*it).begin(),(*it).end());
    }
}

Partition::Partition(const int& wagons_nb, const int& groups_nb)
{
    n=wagons_nb;
    vector<int> wagons;
    for (int i=1; i<wagons_nb+1; i++)
    {
        wagons.push_back(i);
    }
    random_shuffle(wagons.begin(),wagons.end());
    for (int i=0; i<groups_nb; i++)
    {
        vect.push_back(vector<int>());
        vect[i].push_back(wagons.back());
        wagons.pop_back();
    }
    int index;
    while(wagons.size()>0)
    {
        index=(rand()%(groups_nb));
        vect[index].push_back(wagons.back());
        wagons.pop_back();
    }
    vector< vector<int> >::iterator it = vect.begin();
    for (; it != vect.end(); it++)
    {
        sort((*it).begin(),(*it).end());
    }
}

Partition::~Partition()
{
}

vector< vector<int> > Partition::get_vect() const
{
    return vect;
}

int Partition::size() const
{
    return vect.size();
}

bool Partition::operator==(const Partition& part) const
{
    return (vect==part.get_vect());
}

void Partition::show() const
{
    cout << "( ";
    vector< vector<int> >::const_iterator it1 = vect.begin();
    for (; it1 != vect.end(); it1++)
    {
        cout << "{";
        for (vector<int>::const_iterator it2 = (*it1).begin(); it2 != (*it1).end(); it2++)
        {
            cout << " " << *it2 << " ";
            if (it2+1 != (*it1).end())
            {
                cout << ",";
            }
        }
        cout << "} ";
        if (it1+1 != vect.end())
        {
            cout << ", ";
        }
    }
    cout << ")" << endl;
    cout << endl;
}

Partition Partition::swap(const int &i, const int &j) const
{
    // Echange les ensembles de la partition de coordonnées i et j
    vector< vector<int> > vect_swap = vect;
    vect_swap[i] = vect[j];
    vect_swap[j] = vect[i];
    return Partition(vect_swap);
}

Partition Partition::block_swap(const int &i, const int &j, const int &k) const
{
    // Echange les blocs d'ensembles de la partition de coordonnées i à i+k-1
    // et j à j+k-1 (donc de même taille)
    vector< vector<int> > vect_swap = vect;
    for (int l=0; l<k; l++)
    {
        vect_swap[i+l]=vect[j+l];
        vect_swap[j+l]=vect[i+l];
    }
    return vect_swap;
}

vector<Partition> Partition::neighbors() const
{
    // Complexité en O(vect.size()^4) a cause de l'echange de blocs
    vector<Partition> swap_neighbors;
    // On range les voisins de l'element par swap de blocs dans le vecteur
    for (int k=1; k<1+vect.size()/2; k++)
    {
        for (int i=0; i<vect.size()-2*k+1; i++)
        {
            for (int j=i+k; j<vect.size()-k+1; j++)
            {
                swap_neighbors.push_back(block_swap(i,j,k));
            }
        }
    }
    // On mélange l'ordre des éléments avec random_shuffle
    random_shuffle(swap_neighbors.begin(),swap_neighbors.end());
    return swap_neighbors;
}

bool Partition::find_min_elem(int& next_elem, const int& k, const int& inf_bound) const
{
    // On cherche l'element minimum du k-ieme ensemble de la partition strictement supérieur à inf_bound
    // Si il existe, la methode renvoie True et donne la valeur associee à element
    // Sinon la methode renvoie False
    // Les ensembles sont des vecteurs ordonnes : on peut s'arreter des qu'on trouve le bon element
    int ind = 0;
    while(vect[k][ind]<=inf_bound and ind<vect[k].size())
    {
        ind++;
    }
    // si ind est egal a la taille du vecteur, on n'a pas trouve d'element qui correspond
    // sinon ind correspond a l'indice de l'element voulu
    if (ind == vect[k].size())
    {
        return false;
    }
    else
    {
        next_elem = vect[k][ind];
        return true;
    }
}

int Partition::fill(const int& comparison_type, const bool& show) const
{
    // On utilise à nouveau des vecteurs : la structure de pile suffit car il faut
    // juste rentrer des éléments dans les conteneurs et regarder leurs tailles
    vector< vector<int> > rails;
    rails.push_back(vector<int>());
    int rail_ind = 0;
    int inf_bound = 0;
    int next_elem;
    int elements_filled;
    // On remplit les rails avec les ensembles de la partition, dans l'ordre donne
    for (int k=0; k<vect.size(); k++)
    {
        // Deux cas possibles : l'ensemble va se repartir sur un ou deux rails
        // On ne peut pas replacer un element avant d'avoir place tous les autres
        // elements de l'ensemble, il suffit donc dans tous les cas de compter le nombre
        // d'elements rentres et de s'arreter lorsqu'on atteint la taille de l'ensemble
        elements_filled = 0;
        while(elements_filled <vect[k].size())
        {
            if (find_min_elem(next_elem,k,inf_bound))
            {
                rails[rail_ind].push_back(next_elem);
                inf_bound = next_elem;
                elements_filled++;
            }
            else
            {
                rails.push_back(vector<int>());
                rail_ind++;
                inf_bound = 0;
            }
        }
    }
    for (int i=0; i<rails.size();i++)
    {
        reverse(rails[i].begin(),rails[i].end());
    }
    if (show)
    {
        for (int i=0; i<rails.size();i++)
        {
            for (int j=0; j<rails[i].size(); j++)
            {
                cout << rails[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    if (comparison_type == 1)
    {
        // On retourne comme valeur a comparer le nombre de rails utilises
        return rails.size();
    }
    else if (comparison_type == 2)
    {
        // On retourne comme valeur a comparer la "position absolue"
        // du dernier wagon dans la representation de Knudth
        return (rails.size()-1)*n+rails.back().front();
    }
}
