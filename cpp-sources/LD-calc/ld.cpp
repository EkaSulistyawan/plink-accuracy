#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <numeric>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

/**
 * 6 Col
 * 1: Number ID
 * 2: Individual ID
 * 3: Paternal ID
 * 4: Maternal ID
 * 5: Sex (1: Male, 2: Female)
 * 6: Phenotype (1: Unaffected, 2: Affected, 0/-9: missing)
 * */

vector<vector<string> > extractor(string filePath){
    fstream FileInstance;
    vector<vector<string> > matGenotype;
    FileInstance.open(filePath,ios::in);
    if(FileInstance.is_open()){
        string line;
        //  extract per line
        int tperson = 0;
        while(getline(FileInstance,line)){
            // remove space and assign to vector
            stringstream ss(line);
            istream_iterator<string> begin(ss);
            istream_iterator<string> end;
            vector<string> person(begin,end);
            // remove first 6 col
            person.erase(person.begin(),person.begin()+6);
            matGenotype.push_back(person);
        }
        FileInstance.close();
    }
    return matGenotype;
}

int nt(string a){
    if(a=="A") return 0;
    else if(a=="C") return 1;
    else if(a=="G") return 2;
    else if(a=="T") return 3;
    else return 4; // missing
}

string revnt(int a){
    if(a==0) return "A";
    else if(a==1) return "C";
    else if(a==2) return "G";
    else if(a==3) return "T";
    else return "N";
}

int main(int argc, char* argv[]){
    //  read file
    vector<vector<string> > inp = extractor("test.ped");

    //  marker of interest
    int pos1 = stoi(argv[1]); // marker ke-n
    pos1 *= 2;
    int pos2 = stoi(argv[2]); // marker ke-n
    pos2 *= 2;

    int npop = inp.size();
    int nGent = npop*2;

    vector<int> pool(5,0);

    //   calculate frequency of marker
    for(int i = 0;i<npop;i++){
        pool[nt(inp[i][pos1])]++;
        pool[nt(inp[i][pos1+1])]++;
    }

    //   
    nGent -= pool[4]; // miss excluded
    for(int i =0;i<4;i++){
        cout << revnt(i) << " : " << (double)pool[i] / (double) (nGent) << endl;
    }

    string hap1 = argv[3];
    string hap2 = argv[4];

    int hapfreq = 0;
    int nHapMiss = 0;
    for(int i = 0;i<npop;i++){
        bool bHap1 = inp[i][pos1]==hap1 || inp[i][pos1+1]==hap1;
        bool bHap2 = inp[i][pos2]==hap2 || inp[i][pos2+1]==hap2;
        if(bHap1 && bHap2){
            hapfreq++;
        }
        if(inp[i][pos1]=="0" || inp[i][pos2]=="0") nHapMiss++;
    }
    int nHapTot = inp.size() - nHapMiss; 
    cout << nHapTot << endl;
    cout << "Freq " << hap1 << hap2 << " : " << (double) hapfreq / (double) nHapTot;
}