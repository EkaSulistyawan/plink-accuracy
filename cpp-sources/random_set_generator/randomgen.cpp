#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <numeric>
#include <algorithm>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>

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

int main (int argc, char* argv[]){
    srand((unsigned int)time(NULL));

    string filePath = argv[1];
    //  read the file
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
    
    /***
     * DE - IMPUTE
     * */

    //   de-impute per individual
    double percentSNP = stod(argv[3]); // max 1
    for(int j = 0; j < matGenotype[0].size() /*columns*/;j+=2){
        for(int i = 0;i < (int) ((double) matGenotype.size()*percentSNP) /*row*/;i++){
            // call random
            int randVal = rand() % (matGenotype.size());
            matGenotype[randVal][j] = "0";
            matGenotype[randVal][j+1] = "0";
        }
    }

    string FileOPath = argv[2];
    FileInstance.open(FileOPath,ios::out|ios::trunc);
    for (int i = 0; i < matGenotype.size();i++){
        //   SEX / PHEN
        int sex = rand() % 2 + 1;
        int phen = (i < (matGenotype.size() / 2) ? 2 : 1);
        FileInstance << to_string(i) << " ";
        FileInstance << "INDID"+to_string(i) << " ";
        FileInstance << "0 0 "; // Paternal, maternal;
        FileInstance << to_string(sex) << " ";
        FileInstance << to_string(phen) << " ";
        // OUTPUT 
        for(int j = 0; j < matGenotype[i].size();j++){
            if(j == matGenotype[i].size() -1){
                FileInstance << matGenotype[i][j] << "\n";
            }
            else{
                FileInstance << matGenotype[i][j] << " ";
            }
        }
    }
    FileInstance.close();

    return 0;
}