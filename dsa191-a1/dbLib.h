/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dbLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#ifndef DSA191_A1_DBLIB_H
#define DSA191_A1_DBLIB_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>
#include <sstream>
#include <math.h>

#include "dsaLib.h"

/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */
struct TCity {
    // The structure to store city information
    // Data
    int     id;
    string  name;
	string  coords;
    int     start_years;
    string  url_name;
    string  country;
    string  country_state;
	int		idxInFile;
    // Method
    TCity() : id(0), name(""), coords(""), start_years(0), url_name(""), country(""), country_state(""), idxInFile(0) {}
    TCity(int _id, string _name, string _coords, int _start_year, string _url_name, string _country, string _country_state, int _idxInFile);
    bool operator==(int& idx);
    bool operator==(TCity& T);
    bool operator<(TCity& T);
    bool operator>(TCity& T);
    bool operator!=(TCity& T);
	int getID() { return id; };
	string getName() { return name; }
    void print(void);
};
/** Struct: TLine
 * Store infomations of lines in lines.csv
*/
struct TLine {
    // The structure to store line information
    // Data
    int     id;
    int     city_id;
    string  name;
    string  url_name;
    string  color;
    int     system_id;
    int     transport_mode_id;
	int		idxInFile;
    // Method
    TLine() : id(0), city_id(0), name(""), url_name(""), color(""), system_id(0), transport_mode_id(0), idxInFile(0) {}
    TLine(int _id, int city_id, string name, string _url_name, string _color, int _system_id, int _transport_mode_id, int _idxInFile);
	bool operator==(int& idx);
	bool operator==(TLine& T);
	bool operator<(TLine& T);
	bool operator>(TLine& T);
	bool operator!=(TLine& T);
	int getID() { return id; };
	string getName() { return name; }
	int getCityID() { return city_id; }
    void print(void);
};

struct TTrack {
    // The structure to store track information
    // Data
    int     id;
    string  geometry;
    int     buildstart;
    int     opening;
    int     closure;
    int     length;
    int     city_id;
	int		idxInFile;
    TTrack() : id(0), geometry(""), buildstart(0), opening(0), closure(0), length(0), city_id(0), idxInFile(0) {}
    TTrack(int _id, string _geometry, int _buildstart, int _opening, int _closure, int _length, int _city_id, int _idxInFile);
	bool operator==(int& idx);
	bool operator==(TTrack& T);
	bool operator<(TTrack& T);
	bool operator>(TTrack& T);
	bool operator!=(TTrack& T);
	int getID() { return id; };
	int getCityID() { return city_id; }
	string getGeometry() { return geometry; }
    void print(void);
};

struct TStation {
	// The structure to store station information
	// Data
	int id;
	string	name;
	string	geometry;
	int		buildstart;
	int		opening;
	int		closure;
	int		city_id;
	int		idxInFile;
	static int		idmax;
	TStation() : id(0), name(""), geometry(""), buildstart(0), opening(0), closure(0), city_id(0), idxInFile(0) {}
	TStation(int _id, string _name, string _geometry, int _buildstart, int _opening, int _closure, int _city_id, int _idxInFile);
	bool operator==(int& idx);
	bool operator==(TStation& T);
	bool operator<(TStation& T);
	bool operator>(TStation& T);
	bool operator!=(TStation& T);
	int getID() { return id; };
	int getCityID() { return city_id; }
	string getName() { return name; }
	string getGeometry() { return geometry; }
	void print(void);
};

struct TStationLine {
	// The structure to store station information
	// Data
	int id;
	int station_id;
	int line_id;
	int city_id;
	string created_at;
	string updated_at;
	int idxInFile;
	static int id_max;
	TStationLine() : id(0), station_id(0), line_id(0), city_id(0), created_at(""), updated_at(""), idxInFile(0) {}
	TStationLine(int _id, int _station_id, int _line_id, int _city_id, string _created_at, string _updated_at, int idxInFile);
	bool operator==(int& idx);
	bool operator==(TStationLine& T);
	bool operator<(TStationLine& T);
	bool operator>(TStationLine& T);
	bool operator!=(TStationLine& T);
	int getID() { return id; };
	int getLineID() { return line_id; }
	int getStationID() { return station_id; }
	void print(void);
};

struct TDataset {
    // This class can be a container that help you manage your tables
    L1List<TCity>   *CityData;
    L1List<TLine>   *LineData;
    L1List<TTrack>  *TrackData;
    L1List<TStation>  *StationData;
	L1List<TStationLine>* StationLineData;
	TDataset() : CityData(NULL), LineData(NULL), TrackData(NULL), StationData(NULL), StationLineData(NULL) {};
};

// Please add more or modify as needed

struct CSVReader {
    // This struct to manage the process read csv
    char*   content         = nullptr;    // Content of file in ASCII text format
    int     length          = 0;     // Length of file
    int     numOfField      = 1; // Count the number of fields of csv file
    int     numOfLine       = 0;  // Not contain the header 
    char    delimiter       = ',';  // Delimiter of csv file
    char*   fileName        = nullptr;   // Name of this csv file
    // struct's method
    CSVReader(string _nameOfFile,char _delimiter);
    ~CSVReader();
};

TCity& City(string info, int idx);
TTrack& Track(string info, int idx);
TLine& Line(string info, int idx);
TStation& Station(string info, int idx);
TStationLine& StationLine(string info, int idx);

void LoadData(void* &);
void ReleaseData(void* &);

#endif //DSA191_A1_DBLIB_H
