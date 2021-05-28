#include<iostream>
#include<fstream>
#include<string>
#include<deque>
#include<map>
using namespace std;
int n, i, teste;
string cuvant, stareInitiala, stareFinala, stareCurenta, tranzitie;
struct valoare{
    string stare;
    char ch, dp;
};
valoare y;
map<pair<string, char>, valoare> tr;
pair<string, char> x;
deque<char> b;
deque<char> :: iterator it;
ifstream fin("date.in");
int main(){
    fin>> stareInitiala >> stareFinala;
    while(fin>> tranzitie){
        stareCurenta = "";
        i = 0;
        while(tranzitie[i] != ','){
            stareCurenta.push_back(tranzitie[i]);
            i++;
        }
        x = make_pair(stareCurenta, tranzitie[i + 1]);
        i += 3;
        stareCurenta = "";
        while(tranzitie[i] != ','){
            stareCurenta.push_back(tranzitie[i]);
            i++;
        }
        y = {stareCurenta, tranzitie[i + 1], tranzitie[i + 3]};
        tr[x] = y;
    }
    cin>> teste;
    for(; teste; teste--){
        cin>> cuvant;
        n = cuvant.length();
        b.clear();
        for(i = 0; i < n; i++){
            b.push_back(cuvant[i]);
        }
        stareCurenta = stareInitiala;
        it = b.begin();
        while(1){
            x = make_pair(stareCurenta, *it);
            if(tr.count(x) == 0){
                break;
            }
            y = tr[x];
            stareCurenta = y.stare;
            *it = y.ch;
            if(y.dp == '>'){
                it++;
                if(it == b.end()){
                    b.push_back('_');
                }
            }
            else if(y.dp == '<'){
                if(it == b.begin()){
                    b.push_front('_');
                }
                it--;
            }
        }
        if(stareCurenta == stareFinala){
            cout<<"OK\n";
        }
        else{
            cout<<"not OK\n";
        }
    }
}
