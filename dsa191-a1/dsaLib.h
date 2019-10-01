/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dsaLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#ifndef DSA191_A1_DSALIB_H
#define DSA191_A1_DSALIB_H
#include <string>
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

class DSAException {
    int     _error;
    string  _text;
public:

    DSAException() : _error(0), _text("Success") {}
    DSAException(int err) : _error(err), _text("Unknown Error") {}
    DSAException(int err, const char* text) : _error(err), _text(text) {}

    int getError() { return _error; }
    string& getErrorText() { return _text; }
};

/** Function: Compare
 * Return 0 if equal
 * Return 1 if a >  b
 * Vice versa
*/
template<class T>
int compare(T&a, T& b) {
	if (&a == NULL && &b == NULL) return 0;
    if (&a == NULL) return -1;
	if (&b == NULL) return 1;
    return a > b ? 1 : a == b ?  0 :  -1;
} 

template <class T>
struct L1Item {
    T data;
    L1Item<T> *pNext;
    L1Item() : pNext(NULL) {}
    L1Item(T &a) : data(a), pNext(NULL) {}
    bool operator==(L1Item<T>& a);
    bool operator<(L1Item<T>& a);
    bool operator>(L1Item<T>& a);
    bool operator!=(L1Item<T>& a);
    void print(void);
};

template<class T>
bool L1Item<T>::operator==(L1Item<T>& a) {
    return a.data == data;
}

template<class T>
bool L1Item<T>::operator<(L1Item<T>& a) {
    return data < a.data;
}

template<class T>
bool L1Item<T>::operator>(L1Item<T>& a) {
    return data > a.data;
}

template<class T>
bool L1Item<T>::operator!=(L1Item<T>& a) {
    return !(a.data == data); 
}

template<class T>
void L1Item<T>::print(void) {
    data.print();
}

template <class T>
class L1List {
    L1Item<T>   *_pHead;// The head pointer of linked 
    // L1Item<T>   *_pRear;
    // L1Item<T>   *_pLoc;
    size_t      _size;// number of elements in this list
public:
    L1List() : _pHead(NULL), _size(0) {}
    ~L1List();

    void    clean();
    bool    isEmpty() {
        return _pHead == NULL;
    }
    size_t  getSize() {
        return _size;
    }

    T&      at(int i);// give the reference to the element i-th in the list
    T&      operator[](int i);// give the reference to the element i-th in the list

    bool    find(T& a, int& idx);// find an element similar to a in the list. Set the found index to idx, set idx to -1 if failed. Return true if success.
    int     insert(int i, T& a);// insert an element into the list at location i. Return 0 if success, -1 otherwise
    int     remove(int i);// remove an element at position i in the list. Return 0 if success, -1 otherwise.

    int     push_back(T& a);// insert to the end of the list
    int     insertHead(T& a);// insert to the beginning of the list

    int     removeHead();// remove the beginning element of the list
    int     removeLast();// remove the last element of the list

    void    reverse();

    void    traverse(void (*op)(T&)) { 
		cout << "traverse" << endl;
    }
    void    traverse(void (*op)(T&, void*), void*& pParam) {
        // TODO: Your code goes here
		L1List<T>* resultList = new L1List<T>;
		if (isEmpty()) {
			pParam = new L1Item<T>();
			pParam = NULL;
			return;
		}
		L1Item<T>* pCurr = this->_pHead;
		bool (*logicFunc)(T&, void*) = (bool (*)(T&, void*))op;
		while (pCurr != NULL) {
			if (logicFunc(pCurr->data, pParam)) {
				resultList->push_back(pCurr->data);
			}
			pCurr = pCurr->pNext;
		}
		if (resultList->isEmpty()) {
			pParam = new L1Item<T>();
			pParam = NULL;
		}
		else {
			pParam = new L1Item<T>();
			pParam = resultList;
		}
	} 

	L1Item<T>* BinarySearch(T& value, L1Item<T>*& nearestBack);
	L1Item<T>* getHead() { return _pHead; };
    void       setHead(L1Item<T>* pNew) {_pHead = pNew;}
    bool    InsertOrdered(T&);
    void    Print();
};
// Funtion: Middle(T& start, T& last)
// return the middle T& of start and last
template<class T>
L1Item<T>* Middle(L1Item<T>* start, L1Item<T>* last, L1Item<T>*& beforeMid)
{
	if (start == NULL) {
		beforeMid = NULL;
		return NULL;
	}

	L1Item<T>* slow = start;
	L1Item<T>* fast = start->pNext;
	if (fast != last) beforeMid = start;
	while (fast != last)
	{
		fast = fast->pNext;
		if (fast != last)
		{
			beforeMid = slow;
			slow = slow->pNext;
			fast = fast->pNext;
		}
	}
	return slow;
}
// Function for implementing the Binary 
// Search on linked list 
template<class T>
L1Item<T>* L1List<T>::BinarySearch(T& value, L1Item<T>*& nearestBack)
{
	L1Item<T>* start = _pHead;
	L1Item<T>* last = NULL;
	L1Item<T>* mid = NULL;
	L1Item<T>* beforeMid = NULL;
	do
	{
		beforeMid = mid;
		// Find middle
		mid = Middle(start, last, beforeMid);
		// If middle is empty 
		if (mid == NULL)
			return NULL;
		if (compare(mid->data, value) == -1) { 
			nearestBack = mid;
		}
		// If value is present at middle 
		if (mid->data == value)
		{
			//if (nearestBack->data != value)
				return mid;
		}

		// If value is more than mid 
		else if (compare(mid->data, value) == -1) {
				start = mid->pNext;
			}

		// If the value is less than mid. 
		else {
				last = mid;
			}
	} while (last == NULL ||
		last != start);
	// value not present 
	return NULL;
}

/// Insert item to the end of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::push_back(T &a) {
    // TODO: Your code goes here
    L1Item<T> *newNode = new L1Item<T>(a);
    try {
        int idx = 0;
        if (_pHead == NULL) _pHead = newNode; // push back in empty list
        else {
            L1Item<T>  *_pRear = (L1Item<T>*)&(this->at(getSize() - 1)); // push back in unempty
            _pRear->pNext = newNode;
        }
    } catch (DSAException e) {
        cerr << "Error: " <<  e.getErrorText() << endl;
        return -1;
    }
    this->_size++;
    return 0;
}

/// Insert item to the front of the list
/// Return 0 if success, -1 otherwise
template<class T>
L1List<T>::~L1List() {
    while (_size > -1) delete &this->at(_size - 1);
}

template <class T>
int L1List<T>::insertHead(T &a) {
    // TODO: Your code goes here
    L1Item<T> *newNode = new L1Item<T>(a);
    try {
        newNode->pNext = _pHead; // assign next of a is pHead
        _pHead = newNode; // assign head of list by a
		this->_size++;
    } catch (DSAException e) {
        cerr << "Error: " <<  e.getErrorText() << endl;
        return -1;
    }
    return 0;
}

/// Remove the first item of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::removeHead() {
    // TODO: Your code goes here
    try {
        if (_pHead == NULL) throw DSAException(1003, "Cannot remove element of empty list");
        L1Item<T>     *tmp = _pHead;
        _pHead = _pHead->pNext; // if there is one element in list -> still alright
        this->_size--;
    } catch (DSAException e) {
        cerr << e.getErrorText() << endl;
        return -1;
    }
    this->_size--;
    return 0;
}

/// Remove the last item of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::removeLast() {
    // TODO: Your code goes here
    try {
        if (_pHead == NULL) throw DSAException(1003, "Cannot remove element of empty list");
        delete (L1Item<T>)&this->at(getSize() - 1);
        this->_size--;
        (L1Item<T>)(this->at(getSize() - 1)).pNext = NULL;
    } catch (DSAException e) {
        cerr << e.getErrorText() << endl;
        return -1;
    }
    this->_size--;
    return 0;
}

/// Return the reference to i-th element in the list
/// Throw excepstion if i is out of bound of array
template <class T>
T&      L1List<T>::at(int i) {
    if (i < 0 || i > this->getSize()) {
        throw DSAException(1001, "Index out of bound of list");
    }
    L1Item<T> *tmp = new L1Item<T>;
    tmp = _pHead;
    while (--i >= 0) tmp = tmp->pNext;
    return tmp->data;
}

// Return the i-th element of the list
// Return NULL 
template<class T>
T&      L1List<T>::operator[](int i) {
    return this->at(i);
}

/// find an element similar to a in the list.
/// Set the found index to idx, set idx to -1 if failed.
/// Return true if success.
template<class T>
bool    L1List<T>::find(T& a, int& idx) {
    idx = 0;
    try {
        while (!(a == this->at(idx)) && idx < getSize()) idx++;
		if (idx == getSize()) return false;
		return true;
    } catch (DSAException e) {
        cerr << e.getErrorText() << endl;
        idx = -1;
        return false;
    }
}

/// Insert an element into the list at location i.
/// Return 0 if success, -1 otherwise
template<class T>
int     L1List<T>::insert(int i, T& a) {
    L1Item<T> *newNode  = new L1Item<T>(a);
    try {
        int     idx = 0;
        bool    found = find(a, idx);
        if (i == 0) { // if we insert in the first place of the linked list
            this->insertHead(a);
        } else { // if not the first
            newNode->pNext = ((L1Item<T>*)(&this->at(i-1)))->pNext; // assign the next of a by next of the (i-1)-th item 
            ((L1Item<T>*)(&this->at(i-1)))->pNext = newNode; // assign the next of (i-1)-th item by &a;
        }
    } catch (DSAException e) {
        cerr << " Error: " << e.getErrorText() << endl;
        return -1;
    }
    this->_size++;
    return 0;
}

/// Remove an element at position i in the list.
/// Return 0 if success, -1 otherwise.
template<class T>
int     L1List<T>::remove(int i) {
    L1Item<T>* tmp = NULL;
    tmp = _pHead;
    if (i == 0) { // if we remove the head of the linked list
        this->removeHead();
    } else {
        if (i == 1) _pHead->pNext = _pHead->pNext->pNext;
        while (i > 1) {
            i--;
            tmp = tmp->pNext;
        }
        tmp->pNext = tmp->pNext->pNext;
    }
    this->_size--;
    return 0;
 }

/// reverse the list
template<class T>
void    L1List<T>::reverse() {
    L1Item<T>   *prev = NULL;
    L1Item<T>   *curr = _pHead;
    L1Item<T>   *next = NULL;
    while (curr != NULL) {
        next = curr->pNext;
        curr->pNext = prev;
        prev = curr;
        curr = next;
    }
    _pHead = prev;
}

/** Insert an element to list in order
 * If success: return true
 * Vice versa
*/
template<class T>
bool    L1List<T>::InsertOrdered(T& a) {
	if (_pHead == NULL) {
		if (insertHead(a) != -1) {
			return true;
		}
		else {
			return false;
		}
	}
	L1Item<T>* nearestBack = NULL;
	L1Item<T>	*check = BinarySearch(a, nearestBack);
	if (check != NULL) nearestBack = check;
	L1Item<T>* newElement = new L1Item<T>(a);
	if (nearestBack == NULL) {
		if (insertHead(a) != -1) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		newElement->pNext = nearestBack->pNext;
		nearestBack->pNext = newElement;
		check = NULL;
		nearestBack = NULL;
		this->_size++;
		return true;
	}
}

/**Function: Print
 * Print all the list
*/
template<class T>
void    L1List<T>::Print() {
    L1Item<T>   *curr = _pHead;
	while (curr != NULL) {
		curr->print();
		curr = curr->pNext;
	}
}
/**Function: CompareID()
* Return: true if both id are mutual equal
*/
template<class T>
bool CompareID(T& iter, void* a) {
	int* idx = (int*)a;
	return iter.getID() == *idx;
}
/**Function: CompareName()
* Return: true if name is equal to the given
*/
template<class T>
bool CompareName(T& iter, void* a) {
	char* pName = (char*)a;
	string name(pName);
	return iter.getName() == name;
}
/**Function: CompareCityID()
* Return: true if name is equal to the given
*/
template<class T>
bool CompareCityID(T& iter, void* a) {
	int* cityID = (int*)a;
	return iter.getCityID() == *cityID;
}
/**Function: CompareLineID()
* Return: true if lineID is equal to the given
* Serve the LSL function
*/
template<class T>
bool CompareLineID(T& iter, void* a) {
	int* lineID = (int*)a;
	return iter.getLineID() == *lineID;
}
/**
 * Function: CompareStationID()
* Return: true if stationID is equal to the given
* Serve the LSL function
*/
template<class T>
bool CompareStationID(T& iter, void* a) {
	int* stationID = (int*)a;
	return iter.getStationID() == *stationID;
}
#endif //DSA191_A1_DSALIB_H