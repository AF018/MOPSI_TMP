#include "recherche.h"
#include <ctime>
int main()
{   srand(time(0));
    vector< vector<int> > vect1;
    vect1.push_back(vector<int>());
    vect1.push_back(vector<int>());
    vect1.push_back(vector<int>());
    vect1.push_back(vector<int>());
    vect1[0].push_back(1);
    vect1[1].push_back(2);
    vect1[2].push_back(3);
    vect1[1].push_back(4);
    vect1[3].push_back(5);
    vect1[0].push_back(6);
    vect1[2].push_back(8);
    vect1[3].push_back(9);
    vect1[1].push_back(10);
    vect1[3].push_back(11);
    vect1[0].push_back(12);
    vect1[1].push_back(13);
    Partition part1(vect1);
    part1.show();

    vector< vector<int> > vect2;
    vect2.push_back(vector<int>());
    vect2.push_back(vector<int>());
    vect2.push_back(vector<int>());
    vect2.push_back(vector<int>());
    vect2.push_back(vector<int>());
    vect2.push_back(vector<int>());
    vect2.push_back(vector<int>());
    vect2.push_back(vector<int>());
    vect2.push_back(vector<int>());
    vect2.push_back(vector<int>());
    vect2.push_back(vector<int>());
    vect2.push_back(vector<int>());
    vect2.push_back(vector<int>());
    vect2.push_back(vector<int>());
    vect2[0].push_back(14);
    vect2[1].push_back(13);
    vect2[2].push_back(12);
    vect2[3].push_back(11);
    vect2[4].push_back(10);
    vect2[5].push_back(9);
    vect2[6].push_back(8);
    vect2[7].push_back(7);
    vect2[8].push_back(6);
    vect2[9].push_back(5);
    vect2[10].push_back(4);
    vect2[11].push_back(3);
    vect2[12].push_back(2);
    vect2[13].push_back(1);
    Partition part2(vect2);
    //part2.show();
    //part2.fill(true);

    cout << "Recherche naive" << endl;
    cout << endl;
    //recherche_naive(part1,2);
    //recherche_naive(part2,10);

    cout << "Recherche par methode tabou2" << endl;
    cout << endl;
    //methode_tabou2(part1,10,10);
    //methode_tabou(part1,10,10);
    part1.swap(0,2).show();
    part1.swap(0,2).fill(true);
    part1.swap(0,1).show();
    part1.swap(0,1).fill(true);
    cout<<compare(part1.swap(0,1),part1.swap(0,2),2)<<endl;
    //Partition part3=part1.swap(1,2);
    //part3.show();
    //part3.fill(true);
    //part1.show();
    //part1.fill(true);
    //bool a=compare(part1,part3,2);
    //cout<<a<<endl;
    // La recherche parmi les voisins dans la methode tabou
    // n'est pas uniforme car on parcourt toujours les voisins dans le
    // meme ordre (swaps toujours faits dans le meme ordre)
    // idem pour la recherche locale naive

    return 0;
}
