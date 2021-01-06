#include <iostream>
#include <string>
#include <sstream>
#include "tekstas.h"

using std::cout;
using std::string;
using std::endl;

int main()
{

    std::ifstream myfile("tekstas.txt");
    Tekstas tekstas;

    if (myfile.is_open()) {

        std::string eilute;
        int eilutes_numeris = 0;

        while (getline(myfile, eilute)) {
            eilutes_numeris++;

            std::istringstream in(eilute);
            std::string zodis;

            while (in >> zodis) {
                tekstas.itraukti_zodi(eilutes_numeris, zodis);
            }
        }

        tekstas.eilutes_numeris(eilutes_numeris);
        tekstas.isvesti_URL();
        tekstas.isvesti_pasikartojancius();
    }
    else cout << "Failas nerastas";
    myfile.close();
}