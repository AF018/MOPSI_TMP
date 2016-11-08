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

    cout << "Recherche naive" << endl;
    cout << endl;
    recherche_naive(part1,10,1);
    recherche_naive(part1,10,2);

    cout << "Recherche par methode tabou" << endl;
    cout << endl;
    methode_tabou(part1,1000,10000,1);
    methode_tabou(part1,1000,10000,2);

    // La recherche parmi les voisins dans la methode tabou
    // n'est pas uniforme car on parcourt toujours les voisins dans le
    // meme ordre (swaps toujours faits dans le meme ordre)
    // idem pour la recherche locale naive

    return 0;
}
