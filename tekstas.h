//
// Created by eveli on 1/6/2021.
//

#ifndef PAPILDOMA_UZDUOTIS_TEKSTAS_H
#define PAPILDOMA_UZDUOTIS_TEKSTAS_H

#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <regex>

using std::string;
using std::multimap;
using std::left;
using std::setfill;
using std::setw;
using std::endl;
using std::cout;


class Tekstas
{
private:
    std::multimap <string, int> visi_zodziai;
    std::map <string, int> dublicate;
    std::set <string> url;

    int zodzio_nr;
    int eilutes_nr;

public:
    Tekstas():
            zodzio_nr(0) {};

    std::multimap <string,int>::iterator it;

    void itraukti_zodi(int lineNR, string zodis)
    {

        if (std::regex_match (zodis, std::regex("^(https?:\\/\\/)?([\\da-z\\.-]+)\\.([a-z\\.]{2,6})([\\/\\w \\.-]*)*\\/?$") ))
            url.insert(zodis);
        else
        {

            if (zodis != "—" && zodis != "(" && zodis != ")" && zodis != "-" && zodis != "," && zodis != "." && zodis != "/"
                && zodis != "/" && zodis != "@" && zodis != "!" && zodis != "{" && zodis != "}" && zodis != ":" && zodis != ";"
                && zodis != "+" && zodis != "#" && zodis != "?" && zodis != "|" && zodis != "]" && zodis != "[" && zodis != "%"
                && zodis != "^" && zodis != " ")
            {
                isvalyti_string(zodis);
                sumazinti(zodis);
                visi_zodziai.insert(std::pair <string, int> (zodis,lineNR));
                dublicate[zodis]++;
            }
        }
    }

    void isvalyti_string(string &zodis)
    {
        char chars[] = "—()-,./?~`!@#$^&*()_+][}{|:;“„";
        for (int i = 0; i < strlen(chars); ++i ) {
            zodis.erase( remove(zodis.begin(), zodis.end(), chars[i]), zodis.end() );
        }
    }

    void eilutes_numeris(int n)
    {
        eilutes_nr = n;
    }

    void sumazinti(string& zodis)
    {
        if(isupper(zodis[0]))
        {
            zodis[0] = tolower(zodis[0]);
        }

    }

    void isvesti_URL()
    {
        std::ofstream out("url.txt");
        for(auto it = url.begin(); it != url.end(); ++it)
        {
            out << *(it) << std::endl;
        }
        std::cout << "Isvesti visi url faile: " << "'url.txt'" << endl;
    }

    void isvesti_pasikartojancius()
    {

        std::ofstream output("Pasikartojantys.txt");


        output << left << setfill(' ')  << setw(25)  <<"Žodis";
        output << left << setfill(' ')  << setw(25) <<"Pasikartojimų sk.";
        output << left << "Eilutės numeris";


        const std::string bruksnys(60,'_');
        output << endl;
        output << bruksnys << endl;

        for(auto it = dublicate.begin(); it != dublicate.end(); it++)
        {
            if (it->second > 1)
            {
                output << setfill(' ')  << setw(25)  << it->first;
                output << setfill(' ')  << setw(25)  << it->second;
                for (auto it2 = visi_zodziai.begin(); it2 != visi_zodziai.end(); it2++)
                {
                    if (it->first == it2->first)
                    {
                        output << it2->second << " ";
                    }
                }
                output << std::endl;
            }
        }
        cout << "Isvesti visi pasikartojantys zodziai faile: " << "'Pasikartojantys.txt'" << endl;


    }

};

#endif //PAPILDOMA_UZDUOTIS_TEKSTAS_H
