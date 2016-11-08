#include "recherche.h"
#include <ctime>
int main()
{
    srand(time(0));

    Partition part1("D:/Github/MOPSI/TMP_Recherche_Locale/data1.txt");
    part1.show();
    Partition part2("D:/Github/MOPSI/TMP_Recherche_Locale/data2.txt");
    part2.show();
    Partition part3("D:/Github/MOPSI/TMP_Recherche_Locale/data3.txt");
    part3.show();

    /*

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

    */

    Partition P("D:/Ecole des Ponts/Cours 2A/Projet MOPSI/Recherche locale/data.txt");
    methode_tabou(part2,1000,1000,1);
    methode_tabou(part2,1000,1000,2);
    //methode_tabou2(part2,100,100);

    // La recherche parmi les voisins dans la methode tabou
    // n'est pas uniforme car on parcourt toujours les voisins dans le
    // meme ordre (swaps toujours faits dans le meme ordre)
    // idem pour la recherche locale naive

    return 0;
}
