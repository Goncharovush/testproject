#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;
#include "test.h"
#include <thread>

int mid[1000],vwap[1000];

int main() {
    auto Quote  = []() -> void {
        ifstream trade("HSI.Quote.csv");
        int begin=2;//int sk=begin;
        while(!trade.eof()){
            int end=begin+1000;
            Inthread Tr(trade,begin,end,5);
            string **data = new string *[end - begin];
            for (int i = 0; i < (end - begin); i++) {
                data[i] = new string[5];
            }
            data= Tr.Reader(trade,begin,end,5);
            mid[begin-2]=Tr.Mid(data,(end-begin-1));
            if (begin==1002) break;
            begin++;
            delete data;
        }

    };
    auto Trade = []() -> void {
        ifstream trade("HSI.Trade.csv");
        int begin=2;
        while(!trade.eof()){
            int end=begin+1000;
            Inthread Tr(trade,begin,end,3);
            string **data = new string *[end - begin];
            for (int c = 0; c < (end - begin); c++) {
                data[c] = new string[3];
            }
            data = Tr.Reader(trade,begin,end,3);
            vwap[begin-2]= Tr.VWAP(data,begin,end);
            if (begin==1002) break;
            begin++;
            delete data;
        }

    };

    thread threadFirst( Quote );
    thread threadSecond( Trade );

    threadFirst.join();
    threadSecond.join();
    ofstream file("text.txt");
    for ( int i=0;i<1000;i++){
        int dis=mid[i]-vwap[i];
        file<< dis<<endl;
    }
    file.close();

    return 0;
}