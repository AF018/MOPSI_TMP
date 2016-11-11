#include "recherche.h"

int main()
{
    srand(time(0));

    Partition part1("D:/Github/MOPSI/TMP_Recherche_Locale/data1.txt");
    part1.show();
    Partition part2("D:/Github/MOPSI/TMP_Recherche_Locale/data2.txt");
    part2.show();
    Partition part3("D:/Github/MOPSI/TMP_Recherche_Locale/data3.txt");
    part3.show();

    cout << "Recherche naive" << endl;
    cout << endl;
    recherche_naive(part1,10,1);
    recherche_naive(part1,10,2);

    cout << "Recherche par methode tabou" << endl;
    cout << endl;
    methode_tabou(part1,10,10,1);
    methode_tabou(part1,10,10,2);

    // J'ai crée une methode neighbors qui renvoie dans un vecteur
    // les voisins dans un ordre aleatoire, comme on a dit avec le prof
    // Je te laisse l'utiliser pour la methode du recuit etant donne que
    // tu as code cette partie
    cout<< "Recherche par methode de recuit"<<endl;
    cout << "regarde le commentaire au dessus du recuit dans le main" << endl;
    methode_recuit(part2,0.01,1);

    return 0;
}
