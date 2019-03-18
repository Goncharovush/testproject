
#ifndef TESTPROJ_TEST_H
#define TESTPROJ_TEST_H
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;
class Inthread
{
private:
    ifstream& GotoLine(ifstream& file, int begin){
        file.seekg(ios::beg);
        for(int i=0; i < begin - 1; ++i){
            file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
        return file;
    }
public:
        Inthread(ifstream& filename, int begin, int end,int n) {}

        string** Reader(ifstream& filename, int begin, int end,int n){
            GotoLine(filename, begin);
            string **data = new string *[end - begin];
            for (int i = 0; i < (end - begin); i++) {
                data[i] = new string[n];
            }
            int kol = 0;
            while (kol < (end - begin) * n) {
                if (kol % n < n - 1) {
                    getline(filename, data[kol / n][kol % n], ',');
                    kol++;
                }
                else {
                    getline(filename, data[kol / n][kol % n], '\n');
                    kol++;
                }
            }
            return data;
        }

        int VWAP(string** data,int begin,int end){
            int sum1=0,sum2=0;
            for (int j=0;j<(end-begin);j++){
               sum1 += stoi(data[j][1])*stoi(data[j][2]);
               sum2 += stoi(data[j][2]);
            }
            return sum1 / sum2;
        }


    int Mid(string** data, int num){
        return (stoi(data[num][1])* stoi(data[num][4]) + stoi(data[num][3]) * stoi(data[num][2]))/ (stoi(data[num][2]) + stoi(data[num][4]));
        }

~Inthread(){
    }
};
#endif //TESTPROJ_TEST_H





