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

int main (int argc, char* argv[]){
    /**
     * Arguments
     * 1 -> merged
     * 2 -> imputed
     * */
    vector<vector<string> > mergedMat = extractor((string)argv[1]);
    vector<vector<string> > imputedMat = extractor((string)argv[2]);
    int totalGenotypes = mergedMat.size() * mergedMat[0].size() / 2;
    int SeparatorRow = (int) (mergedMat.size() / 2); // half up is reference and ground-truth

    int total = 0; // store total missing
    int correct = 0;
    int keep = 0;
    for(int j = 0;j < mergedMat[0].size() /*col*/;j++){
        for(int i = 0 ;i < SeparatorRow;i++){
            string ref = mergedMat[i][j];
            string modified = mergedMat[i+SeparatorRow][j];
            string imputed = imputedMat[i+SeparatorRow][j];

            if(ref != "0" && modified == "0"){ 
                /* it means the data changed during test data creation*/
                total++;
                if(imputed == ref){
                    /* it means the data correctly imputed */
                    correct++;
                }else if(imputed == "0"){
                    /* it means the data doesnt change */
                    keep++;
                }
            }
        }
    }

    /***
     * %correct = correct imputation (based on reference) per total missing
     * %unchanged = the data that kept untyped after imputation per total missing
     * %missing = total missing per total genotypes
     * %total genotype = all of the genotype
     * */
    cout << "Correctness " << (double) correct / (double) total * 100.0 << "%" << endl;
    cout << "Unchanged " << (double) keep / (double) total * 100.0 <<"%" << endl;
    cout << "% Missing " << (double) total / (double) totalGenotypes * 100.0 << endl;
    cout << "TotalGenotype " <<  totalGenotypes << endl;
    cout << mergedMat.size() << endl;
    cout << mergedMat[0].size() << endl;

    //  output to a file
    fstream inp;
    inp.open("summary.csv",ios::app); // store in a csv
    inp << (double) correct / (double) total * 100.0 << ",";
    inp << (double) keep / (double) total * 100.0 << ",";
    inp << (double) total / (double) totalGenotypes * 100.0 << ",";
    inp << totalGenotypes << "\n";

    return 0;
}