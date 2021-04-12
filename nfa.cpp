#include<fstream>
#include<iostream>
#include<vector>
#include<cstring>
#include<queue>
using namespace std;

int numStates, numTr, numTests, startState, numFinal, state1, state2, i, lenWord;
char letter, word[1002];
int visited[1002][1002];
int prevState[1002][1002], wordPath[1002];
bool isFinal[1002], accepted;
vector<int> transitions[1002][256];

ifstream fin("date.in");

void getPath(int currentState, int currentPos){
    wordPath[currentPos] = currentState;
    if(currentPos != 0){
        getPath(prevState[currentState][currentPos], currentPos - 1);
    }
}

bool accept(int test){
    queue< pair<int, int> > q;
    pair<int, int> current;

    visited[startState][0] = test;
    q.push( make_pair(startState, 0) );
    while(!q.empty()){
        current = q.front();
        q.pop();
        if(current.second == lenWord){
            if(isFinal[current.first]){
                getPath(current.first, current.second);
                return true;
            }
            continue;
        }
        char nextLetter = word[current.second + 1];
        for(int i = 0; i < transitions[current.first][nextLetter].size(); i++){
            int nextState = transitions[current.first][nextLetter][i];
            if(visited[nextState][current.second + 1] != test){
                visited[nextState][current.second + 1] = test;
                prevState[nextState][current.second + 1] = current.first;
                q.push(make_pair(nextState, current.second + 1) );
            }
        }
    }
    return false;
}

int main(){
    fin>> numStates >> numTr;
    for(i = 1; i <= numTr; i++){
        fin>> state1 >> state2 >> letter;
        transitions[state1][letter].push_back(state2);
    }
    fin>> startState;
    fin>> numFinal;
    for(i = 1; i <= numFinal; i++){
        fin>> state1;
        isFinal[state1] = true;
    }
    fin>> numTests;
    for(i = 1; i <= numTests; i++){
        fin>> word + 1;
        lenWord = strlen(word + 1);
        accepted = accept(i);
        if(accepted == false){
            cout<<"NU\n";
        }
        else{
            cout<<"DA\n";
            cout<<"Traseu: ";
            for(int j = 0; j <= lenWord; j++){
                cout<< wordPath[j] <<" ";
            }
            cout<<"\n";
        }
    }
}
