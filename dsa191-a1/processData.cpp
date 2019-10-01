/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : processData.cpp
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : Implementation of main features in the assignment
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#include "processData.h"

/* TODO: You can implement methods, functions that support your data structures here.
 * */
using namespace std;

void Initialization() {
    // If you use global variables, please initialize them explicitly in this function.
}

void Finalization() {
    // Release your data before exiting
}

void ProcessRequest(const char* pRequest, void* pData, void* &pOutput, int &N) {
    // TODO: Implement this function for processing a request
    // NOTE: You can add other functions to support this main process.
    //       pData is a pointer to a data structure that manages the dataset
    //       pOutput is a pointer reference. It is set to nullptr and student must allocate data for it in order to save the required output
    //       N is the size of output, must be a non-negative number
	TDataset* DataTable = new TDataset;
	DataTable = (TDataset*)pData;
	string request = "";
	string param1 = "";
	string param2 = "";
	stringstream ss(pRequest);
	ss >> request;
	if (ss.good()) {
		ss.get();
		getline(ss, param1, '\n');
	}
	ss.flush();
	if (request == "CL" && param1 == "") CountLine(DataTable->LineData, pOutput, N);
	if (request == "CL" && param1 != "") CountLineOfGivenCity(param1, DataTable, pOutput, N);
	if (request == "LSC")	ListStationWithCityName(param1, DataTable, pOutput, N);
	if (request == "LLC")	ListLineWithCityName(param1, DataTable, pOutput, N);
	if (request == "LSL")	ListStationWithLineID(param1, DataTable, pOutput, N);
	if (request == "FC")	FindCity(param1, DataTable, pOutput, N);
	if (request == "FS")	FindStation(param1, DataTable, pOutput, N);
	if (request == "SLP")	StationLocationPosition(param1, DataTable, pOutput, N);
	if (request == "IS")	InsertStation(param1, DataTable, pOutput, N);
	if (request == "RS")	RemoveStation(param1, DataTable, pOutput, N);
	if (request == "US")	UpdateStation(param1, DataTable, pOutput, N);
	if (request == "ISL")	InsertStationLine(param1, DataTable, pOutput, N);
	if (request == "RSL")	RemoveStationFromLine(param1, DataTable, pOutput, N);
}
/** Func: CountLine
 * CL	
 * integer	Count the number of lines in the dataset.
*/
void CountLine(L1List<TLine>* LineList, void*& pOutput, int&N) {
	N = 1;
	int* data = new int;
	*data = LineList->getSize();
	pOutput = (void*)data;
}
/**
 * CL <city_name>	
 * integer	Count the number of lines in the given city. 
 * If the city does not exist, return -1.
*/
void CountLineOfGivenCity(string city_name, TDataset*& DataTable, void*& pOutput, int& N) {
	char* cityName = (char*)city_name.c_str();
	void (*compareName)(TCity&, void*) = (void (*)(TCity&, void*))CompareName<TCity>;
	DataTable->CityData->traverse(compareName, (void*&)cityName);
	L1List<TCity>* cityList = (L1List<TCity>*)cityName;
	if (cityList == NULL) {
		N = 1;
		int* data = new int;
		*data = -1;
		pOutput = (void*)data;
		return;
	}
	else {
		int cityID = cityList->getHead()->data.getID();
		int* pData = new int;
		*pData = cityID;
		void (*op)(TLine&, void*) = (void (*)(TLine&, void*))CompareCityID<TLine>;
		DataTable->LineData->traverse(op, (void*&)pData);
		L1List<TLine>* resultList = (L1List<TLine>*)pData;
		if (resultList->isEmpty()) throw DSAException(1004, "Line not found");
		int* numOfLine = new int(resultList->getSize());
		pOutput = (void*)numOfLine;
		N = 1;
	}
}
/**
 * CL <city_name>	
 * integer	
 * Count the number of lines in the given city. 
 * If the city does not exist, return -1.
*/
void ListStationWithCityName(string city_name, TDataset*& DataTable, void*& pOutput, int& N) {
	char* cityName = (char*)city_name.c_str();
	void (*compareName)(TCity&, void*) = (void (*)(TCity&, void*))CompareName<TCity>;
	DataTable->CityData->traverse(compareName, (void*&)cityName);
	L1List<TCity>* cityList = (L1List<TCity>*)cityName;
	if (cityList == NULL) {
		N = 1;
		int* data = new int;
		*data = -1;
		pOutput = (void*)data;
		return;
	}
	else {
		int cityID = cityList->getHead()->data.getID();
		int* pData = new int;
		*pData = cityID;
		void (*op)(TStation&, void*) = (void (*)(TStation&, void*))CompareCityID<TStation>;
		DataTable->StationData->traverse(op, (void*&)pData);
		L1List<TStation>* resultList = (L1List<TStation>*)pData;
		if (resultList->isEmpty()) throw DSAException(1004, "Station not found");
		N = resultList->getSize();
		int* pListStation = new int[N];
		L1Item<TStation>* pCurr = resultList->getHead();
		for (int i = 0; i < N; i++) {
			pListStation[i] = pCurr->data.getID();
			pCurr = pCurr->pNext;
		}
		pOutput = (void*)pListStation;
	}
}
/**
 * LLC <city_name>	
 * integer array	
 * List lines (line_id) of a city (given <city_name>). 
 * The order of this list is given in lines.csv.
*/
void ListLineWithCityName(string city_name, TDataset*& DataTable, void*& pOutput, int& N) {
	char* cityName = (char*)city_name.c_str();
	void (*compareName)(TCity&, void*) = (void (*)(TCity&, void*))CompareName<TCity>;
	DataTable->CityData->traverse(compareName, (void*&)cityName);
	L1List<TCity>* cityList = (L1List<TCity>*)cityName;
	if (cityList == NULL) {
		N = 1;
		int* data = new int;
		*data = -1;
		pOutput = (void*)data;
		return;
	}
	else {
		int cityID = cityList->getHead()->data.getID();
		int* pData = new int;
		*pData = cityID;
		void (*op)(TLine&, void*) = (void (*)(TLine&, void*))CompareCityID<TLine>;
		DataTable->LineData->traverse(op, (void*&)pData);
		L1List<TLine>* resultList = (L1List<TLine>*)pData;
		if (resultList->isEmpty()) throw DSAException(1004, "Line not found");
		N = resultList->getSize();
		cout << "N = " << N << endl;
		int* pListStation = new int[N];
		L1Item<TLine>* pCurr = resultList->getHead();
		for (int i = 0; i < N; i++) {
			pListStation[i] = pCurr->data.getID();
			pCurr = pCurr->pNext;
		}
		pOutput = (void*)pListStation;
	}
}
/**
 * LSL <line_id>	
 * integer array	
 * List stations (station_id) of a line with <line_id>. 
 * The order of station is determined by its appearance in station_lines.csv.
*/
void ListStationWithLineID(string line_id, TDataset*& DataTable, void*& pOutput, int& N) {
	int lineID;
	stringstream ss(line_id);
	ss >> lineID;
	ss.flush();

	int* pData = new int;
	*pData = lineID;
	void (*op)(TStationLine&, void*) = (void (*)(TStationLine&, void*))CompareLineID<TStationLine>;
	DataTable->StationLineData->traverse(op, (void*&)pData);
	L1List<TStationLine>* resultList = (L1List<TStationLine> * )pData;
	if (resultList == NULL) {
		N = 0;
		pOutput = new int;
		pOutput = NULL;
		return;
	}
	N = resultList->getSize();
	int* pListStation = new int[N];
	L1Item<TStationLine>* pCurr = resultList->getHead();
	for (int i = 0; i < N; i++) {
		pListStation[i] = pCurr->data.getID();
		pCurr = pCurr->pNext;
	}
	pOutput = (void*)pListStation;
}
/**
 * Func: FindCity()
 * FC <city_name>	
 * integer	
 * Find a city with the given name. 
 * Return the first city_id if found, -1 otherwise.
*/
void FindCity(string city_name, TDataset*& DataTable, void*& pOutput, int& N) {
	char* cityName = (char*)city_name.c_str();
	void (*compareName)(TCity&, void*) = (void (*)(TCity&, void*))CompareName<TCity>;
	DataTable->CityData->traverse(compareName, (void*&)cityName);
	L1List<TCity>* cityList = (L1List<TCity>*)cityName;
	if (cityList == NULL) {
		N = 1;
		int* data = new int;
		*data = -1;
		pOutput = (void*)data;
		return;
	}
	else {
		int cityID = cityList->getHead()->data.getID();
		int* pData = new int;
		*pData = cityID;
		pOutput = pData;
		N = 1;
	}
}
/**
 * Func: FindStation()
 * FS <station_name>	
 * integer	
 * Find a station with the given name. 
 * Return the first station_id if found, -1 otherwise.
*/
void FindStation(string city_name, TDataset*& DataTable, void*& pOutput, int& N) {
	char* stationName = (char*)city_name.c_str();
	void (*compareName)(TStation&, void*) = (void (*)(TStation&, void*))CompareName<TStation>;
	DataTable->StationData->traverse(compareName, (void*&)stationName);
	L1List<TStation>* stationList = (L1List<TStation>*)stationName;
	if (stationList == NULL) {
		N = 1;
		int* data = new int;
		*data = -1;
		pOutput = (void*)data;
		return;
	}
	else {
		int cityID = stationList->getHead()->data.getID();
		int* pData = new int;
		*pData = cityID;
		pOutput = pData;
		N = 1;
	}
}
/**
 * Func(): 
 * SLP <station_id> <track_id>	
 * integer	
 * Find the position of a station in a track. 
 * Return the index of that station if found, -1 otherwise. The order of station is determined by LINESTRING in tracks.csv.
*/
void StationLocationPosition(string param, TDataset*& DataTable, void*& pOutput, int& N) {
	stringstream ss(param);
	int stationID;
	int trackID;
	ss >> stationID;
	ss >> trackID;

	int* pStationID = &stationID;
	void (*compareStationID)(TStation&, void*) = (void (*)(TStation&, void*))CompareID<TStation>;
	DataTable->StationData->traverse(compareStationID, (void*&)pStationID);
	L1List<TStation>* stationList = (L1List<TStation>*)pStationID;
	if (stationList == NULL) {
		N = 1;
		int* data = new int;
		*data = -1;
		pOutput = (void*)data;
		return;
	}

	int* pTrackID = &trackID;
	void (*compareTrackID)(TTrack&, void*) = (void (*)(TTrack&, void*))CompareID<TTrack>;
	DataTable->TrackData->traverse(compareTrackID, (void*&)pTrackID);
	L1List<TTrack>* trackList = (L1List<TTrack>*)pTrackID;
	if (trackList == NULL) {
		N = 1;
		int* data = new int;
		*data = -1;
		pOutput = (void*)data;
		return;
	}

	L1Item<TStation>*	pStation = stationList->getHead();
	L1Item<TTrack>*		pTrack	 = trackList->getHead();
	ss = stringstream(pStation->data.getGeometry());
	string stationLocation;
	getline(ss, stationLocation, '(');
	getline(ss, stationLocation, ')');
	ss.flush();
	
	ss = stringstream(pTrack->data.getGeometry());
	string lineString;
	getline(ss, lineString, '(');
	getline(ss, lineString, ')');
	ss.flush();
	ss = stringstream(lineString);
	string locationInLine;
	int idx = 0;
	int* pData = new int;
	*pData = -1;
	while (ss.good()) {
		getline(ss, locationInLine, ',');
		if (locationInLine == stationLocation) {
			*pData = idx;
			break;
		}
		idx++;
	}
	N = 1;
	pOutput = (void*)pData;
}
/**
 * IS <csv_description>	
 * integer
 * Insert a station into the dataset. 
 * The information of the station is given in csv_description, 
 * which includes everything you see in stations.csv except the id and city_id. 
 * If this operation success, we have to receive station id as the return value. 
 * Note that we keep track the maximum id of every entities in the dataset so that when you insert a new instance, 
 * the allocated id should be the id_max + 1
*/
void InsertStation(string info, TDataset*& DataTable, void*& pOutput, int& N) {
	int idmax = TStation::idmax;
	int idx = DataTable->StationData->getSize();
	int     _id;
	string _name;
	string  _geometry;
	int     _buildstart;
	int     _opening;
	int     _closure;
	int     _city_id;
	stringstream ss(info);
	_id = idmax + 1;
	getline(ss, _name, ',');
	getline(ss, _geometry, ',');
	ss.get();
	ss >> _buildstart;
	ss.get();
	ss >> _opening;
	ss.get();
	ss >> _closure;
	_city_id = 0;
	TStation* newCity = new TStation(_id, _name, _geometry, _buildstart, _opening, _closure, _city_id, idx);
	DataTable->StationData->push_back(*newCity);
	int* pData = new int;
	*pData = _id;
	N = 1;
	pOutput = (void*)pData;
}
/**
 * RS <station_id>	
 * integer	Remove a station from the dataset. 
 * As a consequence, every records related to the station must be removed. 
 * Return 0 if success, return -1 if the station does not exist or can not be removed.
*/
void RemoveStation(string info, TDataset*& DataTable, void*& pOutput, int& N) {
	int stationID;
	stringstream ss(info);
	ss >> stationID;

	int* pStationID = new int;
	*pStationID = stationID;
	void (*compareStationID)(TStationLine&, void*) = (void (*)(TStationLine&, void*))CompareStationID<TStationLine>;
	DataTable->StationLineData->traverse(compareStationID, (void*&)pStationID);
	L1List<TStationLine>* stationLineList = (L1List<TStationLine>*)pStationID;
	if (stationLineList == NULL) {
		int* pOut = new int;
		*pOut = -1;
		pOutput = pOut;
		N = 1;
		return;
	}
	if (stationLineList != NULL) {
		L1Item<TStationLine>* pCurrSL = stationLineList->getHead();
		int idxSL = 0;
		while (pCurrSL != NULL) {
			idxSL = pCurrSL->data.idxInFile;	
			DataTable->StationLineData->remove(idxSL);
			pCurrSL = pCurrSL->pNext;
		}
	}

	delete pStationID;
	pStationID = NULL;
	pStationID = new int;
	*pStationID = stationID;
	// Remove station
	void (*compareID)(TStation&, void*) = (void (*)(TStation&, void*))CompareID<TStation>;
	DataTable->StationData->traverse(compareID, (void*&)pStationID);
	L1List<TStation>* stationList = (L1List<TStation>*)pStationID;
	if (stationList == NULL) {
		N = 1;
		int* data = new int;
		*data = -1;
		pOutput = (void*)data;
		return;
	}
	L1Item<TStation>* pCurr = stationList->getHead();
	int idx = 0;
	while (pCurr != NULL) {
		idx = pCurr->data.idxInFile;
		DataTable->StationData->remove(idx);
		string geometry = pCurr->data.getGeometry();
		stringstream gm(geometry);
		getline(gm, geometry, '(');
		getline(gm, geometry, ')');
		L1Item<TTrack>* pCurrTrack = DataTable->TrackData->getHead();
		string trackGeometry = "";
		stringstream ss(trackGeometry);
		string point = "";
		bool check = false;
		while (pCurrTrack != NULL) {
			trackGeometry = pCurrTrack->data.getGeometry();
			ss = stringstream(trackGeometry);
			getline(ss, trackGeometry, '(');
			getline(ss, trackGeometry, ')');
			ss = stringstream(trackGeometry);
			trackGeometry = "\"LINESTRING(";
			while (ss.good()) {
				getline(ss, point, ',');
				if (point != geometry) {
					trackGeometry += point;
					if (ss.good()) trackGeometry += ',';
					else trackGeometry += ")\"";
				}
			}
			pCurrTrack->data.geometry = trackGeometry;
			pCurrTrack = pCurrTrack->pNext;
		}
		pCurr = pCurr->pNext;
	}
	int* outValue = new int;
	*outValue = 0;
	pOutput = (void*)outValue;
	N = 1;
}
/**
 * US <station_id> <csv_description>	
 * integer	
 * Update the information of a station with id <station_id>. 
 * Return 0 if success, and -1 otherwise.
*/
void UpdateStation(string info, TDataset*& DataTable, void*& pOutput, int& N) {
	int     _id;
	string _name;
	string  _geometry;
	int     _buildstart;
	int     _opening;
	int     _closure;
	stringstream ss(info);
	ss >> _id;
	getline(ss, _name, ',');
	getline(ss, _geometry, ',');
	ss.get();
	ss >> _buildstart;
	ss.get();
	ss >> _opening;
	ss.get();
	ss >> _closure;

	int* pStationID = new int;
	*pStationID = _id;
	void (*compareID)(TStation&, void*) = (void (*)(TStation&, void*))CompareID<TStation>;
	DataTable->StationData->traverse(compareID, (void*&)pStationID);
	L1List<TStation>* stationList = (L1List<TStation>*)pStationID;
	if (stationList == NULL) {
		N = 1;
		int* data = new int;
		*data = -1;
		pOutput = (void*)data;
		return;
	}
	L1Item<TStation>* pCurr = stationList->getHead();
	pCurr->data.name = _name;
	pCurr->data.geometry = _geometry;
	pCurr->data.buildstart = _buildstart;
	pCurr->data.opening = _opening;
	pCurr->data.closure = _closure;
}
/**
 * ISL <station_id> <line_id> <pos>
 * integer	
 * Insert a station <station_id> to a line <line_id> at index . 
 * Note that the first position has index 0. 
 * Return 0 if success, and -1 otherwise.
 * NOTE: The expected result of this request is that when we request LSL, 
 * the new station must stay at position . 
 * If the station exists in the line, this operation will fail and no change should be made.
*/
void InsertStationLine(string info, TDataset*& DataTable, void*& pOutput, int& N) {
	stringstream ss(info);
	int 	station_id;
	int 	line_id;
	int 	pos;
	ss >> station_id;
	ss >> line_id;
	ss >> pos;
	//16769,16533,1603,91,2019-03-08 22:25:57.224648,2019-03-08 22:25:57.224648
	int id = TStationLine::id_max + 1;
	L1Item<TStation>* pStation = DataTable->StationData->getHead();
	while (pStation != NULL) {
		if (pStation->data.id == station_id) break;
		pStation = pStation->pNext;
	}
	int city_id = pStation->data.city_id;
	string created_at = "";
	string updated_at = "";
	TStationLine* p = new TStationLine(id, station_id, line_id, city_id, created_at, updated_at, 0); // 0 mean insert
	L1Item<TStationLine>* pNew = new L1Item<TStationLine>(*p);
	L1Item<TStationLine>* pCurr = DataTable->StationLineData->getHead();
	while (pCurr != NULL) {
		if (pos == 0) break;
		if (pCurr->data.line_id == line_id) pos--;
		pCurr = pCurr->pNext;
	}
	if (pCurr == NULL) {
		int* pOut = new int(-1);
		pOutput = (void*)pOut;
		N = 1;
		return;
	}
	if (pCurr == DataTable->StationLineData->getHead()) {
		DataTable->StationLineData->insertHead(*p);
	} else {
		pNew->pNext = pCurr->pNext;
		pCurr->pNext = pNew;
	}
	int* pOut = new int(0);
	pOutput = (void*)pOut;
	N = 1;
	return;
	ss.flush();
}
/**
 * RSL <station_id> <line_id>	
 * integer	
 * Remove a station <station_id> from a line <line_id>.
 * Return 0 if success, and -1 otherwise.
*/
void RemoveStationFromLine(string info, TDataset*& DataTable, void*& pOutput, int& N) {
	stringstream ss(info);
	int idx = 0;
	int stationID;
	int lineID;
	ss >> stationID;
	ss >> lineID;

	L1Item<TStationLine>* pCurr = DataTable->StationLineData->getHead();
	L1Item<TStationLine>* pPre	= DataTable->StationLineData->getHead();
	while (pCurr != NULL) {
		if (pCurr->data.line_id == lineID && pCurr->data.station_id == stationID) {
			if (pPre == pCurr) {
				pPre = pPre->pNext;
				DataTable->StationLineData->setHead(pCurr->pNext);
				pCurr->print();
			}
			idx++;
		}
		pPre = pCurr;
		pCurr = pCurr->pNext;
	}
	if (idx) {
		int* pOut = new int(0);
		pOutput = (void*) pOut;
		N = 1;
	} else {
		int* pOut = new int(-1);
		pOutput = (void*)pOut;
		N = 1;
	}
}