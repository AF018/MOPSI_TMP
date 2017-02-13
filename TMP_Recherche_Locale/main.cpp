#include "recherche.h"

int main()
{
    srand(time(0));
/*
    Partition part1("D:/Github/MOPSI/TMP_Recherche_Locale/data1.txt");
    part1.show();
    Partition part2("D:/Github/MOPSI/TMP_Recherche_Locale/data2.txt");
    part2.show();
    Partition part3("D:/Github/MOPSI/TMP_Recherche_Locale/data3.txt");
    part3.show();
    Partition random_part(120,20,false);
    cout<<random_part.moyenne()<<endl;
    random_part.show();

    cout << "Recherche naive" << endl;
    cout << endl;
    recherche_naive(part1,10,1);
    recherche_naive(part1,10,2);

    cout << "Recherche par methode tabou" << endl;
    cout << endl;
    methode_tabou(part1,100,100,1);
    methode_tabou(part1,100,100,2);

    cout<< "Recherche par methode de recuit"<<endl;
    methode_recuit(part1,0.01,1);

    methode_recuit(random_part,0.01,2);
 */

    //cout<<calcul(50,120,2,0.01)<<endl;

    //bound_test(80,100,0.01);

    time_test();
    return 0;
}
