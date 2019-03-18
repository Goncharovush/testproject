#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;
#include "test.h"
#include <thread>

int mid[1000],vwap[1000];
int begin=2;int end=::begin+1000;
int main() {

    auto Quote  = [](Inthread& Qt,ifstream& quote) -> void {
        int begin=::begin;
        while(!quote.eof()){
            int end=begin+1000;
            string **data = new string *[end - begin];
            for (int i = 0; i < (end - begin); i++) {
                data[i] = new string[5];
            }
            data= Qt.Reader(quote,begin,end,5);
            mid[begin-::begin]=Qt.Mid(data,(end-begin-1));
            if (begin==::end) break;
            begin++;
            delete data;
        }

    };

    auto Trade = [](Inthread& Tr,ifstream& trade) -> void {
        int begin=::begin;
        while(!trade.eof()){
            int end=begin+1000;
            string **data = new string *[end - begin];
            for (int i = 0; i < (end - begin); i++) {
                data[i] = new string[3];
            }
            data = Tr.Reader(trade,begin,end,3);
            vwap[begin-::begin]= Tr.VWAP(data,begin,end);
            if (begin==::end) break;
            begin++;
            delete data;
        }

    };
    ifstream quote("HSI.Quote.csv");
    Inthread Qt(quote);
    ifstream trade("HSI.Trade.csv");
    Inthread Tr(trade);
    thread threadFirst( Quote,ref(Qt), ref(quote) );
    thread threadSecond( Trade,ref(Tr), ref(trade) );

    threadFirst.join();
    threadSecond.join();
    ofstream file("text.txt");
    for ( int i=0;i<1000;i++){
        int dis=mid[i]-vwap[i];
        file<< dis<<endl;
    }
    quote.close();
    trade.close();
    file.close();

    return 0;
}