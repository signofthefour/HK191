/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : processData.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : Declaration of main features in the assignment
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#ifndef DSA191_A1_PROCESSDATA_H
#define DSA191_A1_PROCESSDATA_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include <cassert>

#include "dbLib.h"
using namespace std;
/// Prototype declaration
void Initialization();
void Finalization();

void ProcessRequest(const char* pRequest, void* pData, void* &pOutput, int &);

template <typename T>
void PrintReqOutput(const char* pRequest, T* pOutput, int N) {
    cout << pRequest << ":";
    if (pOutput == nullptr) {
        cout << " error\n";
        return;
    }
    for (int i = 0; i < N; ++i) {
        cout << ' ' << *pOutput++;
    }
    cout << '\n';
}

void CountLine(L1List<TLine>*LineList, void*& pOutput, int&);
void CountLineOfGivenCity(string city_name, TDataset*& DataTable, void*& pOutput, int& N);
void ListStationWithCityName(string city_name, TDataset*& DataTable, void*& pOutput, int& N);
void ListLineWithCityName(string city_name, TDataset*& DataTable, void*& pOutput, int& N);
void ListStationWithLineID(string city_name, TDataset*& DataTable, void*& pOutput, int& N);
void FindCity(string city_name, TDataset*& DataTable, void*& pOutput, int& N);
void FindStation(string info, TDataset*& DataTable, void*& pOutput, int& N);
void StationLocationPosition(string info, TDataset*& DataTable, void*& pOutput, int& N);
void InsertStation(string info, TDataset*& DataTable, void*& pOutput, int& N);
void RemoveStation(string info, TDataset*& DataTable, void*& pOutput, int& N);
void UpdateStation(string info, TDataset*& DataTable, void*& pOutput, int& N);
void InsertStationLine(string info, TDataset*& DataTable, void*& pOutput, int& N);
void RemoveStationFromLine(string info, TDataset*& DataTable, void*& pOutput, int& N);
#endif //DSA191_A1_PROCESSDATA_H
