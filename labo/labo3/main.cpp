#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <vector>

int makeNumber(std::vector<int> &v, std::string &s) {
    int res = 1;
    for (char c : s) {
        res *= v[(c - 'a')];
    }
    return res;
}

int binairZoeken(std::vector<std::pair<std::string, std::string>> &v, std::string s){
    int l = 0, r = v.size();
    while( l < r -1){
        int m = l + (r-l)/2;
        if(s < v[m].first){
            r = m;
        }else{
            l = m;
        }
    }
    return s == v[l].first ? l : -1;
}

int main() {
    std::vector<std::pair<std::string, std::string>> map;

    std::ifstream f("woordenlijst.txt");
    std::string line;
    while (getline(f, line)) {
        std::string original = line;
        std::sort(line.begin(), line.end());
        map.push_back(std::make_pair(line, original));
    }

    std::sort(map.begin(), map.end());

    int index_max = 0;
    int index_vorige = 0;
    int max_aantal = 0;
    int aantal = 0;
    int max_lengte_van_woord = map[0].first.size();
    int index_langste_woord = 0;

    std::string vorige = map[0].first;
    for (int i = 1; i < map.size(); i++) {
        if (map[i].first == vorige) {
            aantal++;
            if (aantal >= 2 && max_lengte_van_woord < map[i].first.size()) {
                max_lengte_van_woord = map[i].first.size();
                index_langste_woord = i;
            }
        } else {
            if (aantal > max_aantal) {
                max_aantal = aantal;
                index_max = index_vorige;
            }
            aantal = 1;
            index_vorige = i;
        }
        vorige = map[i].first;
    }

    std::cout << "Grootste groep annagrammen: \n";
    for (int i = index_max; i < (index_max + max_aantal); i++) {
        std::cout << map[i].second << " ";
    }
    std::cout << std::endl;

    std::cout << "\nLengte paar annagrammen: \n";
    std::cout << max_lengte_van_woord << std::endl;
    for(int i = index_langste_woord; i > (index_langste_woord - max_aantal) ;
    i--){ if(map[i].second.size() == max_lengte_van_woord){ std::cout <<
    map[i].second << std::endl;
        }
    }

    std::ifstream f2("komedie.txt");
    std::ofstream result("result.txt");
    std::string woord;
    while (f2 >> woord) {

        std::string original = woord;
        std::sort(woord.begin(), woord.end());

        int begin_index = -1;
        int aantal = 0;

        begin_index = binairZoeken(map, woord);

        if(begin_index>=0){
            std::cout << original << " " << map[begin_index].second << std::endl;
        }

        if (begin_index >= 0) {
            result << map[begin_index ].second << " ";
        }else{
            result << woord  << " ";
        }
    }

    return 0;
}