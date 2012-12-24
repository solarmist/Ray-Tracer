//
//  DynArray.h
//  RayTracer
//
//  Created by Joshua Olson on 3/16/11.
//  Copyright 2011 solarmist. All rights reserved.
//
#ifndef _DYNARRAY_H_
#define _DYNARRAY_H_ 1

//A DynArray stores data in an ordered random access structure with 
//no delete operation. Items are added with append.

template <class T> class DynArray{
    DynArray();
    DynArray(int a);
    ~DynArray();
    
    bool append(T item);    //Always add to end
    bool truncate();        //Make arraySize = nData
    void clear() {nData = 0;}
    int length() const {return nData;}
    bool empty() const {return nData == 0;}
    const T &operator[](int i) const {return data[i];}
    T &operator[] (int i){return data[i];}
    
    T *data;
    int nData;
    int arraySize;
};

template <class T> DynArray<T>::DynArray(){
    nData = 0;
    arraySize = 4;
    data = new T[arraySize];
}

template <class T> DynArray<T>::DynArray(int a){
    nData = 0;
    arraySize = a;
    data = new T[arraySize];
}

template <class T> DynArray<T>::~DynArray(){
    nData = 0;
    delete [] data;
}

template <class T> bool DynArray<T>::append(T item){
    if(nData == arraySize){
        arraySize *= 2;
        T *temp = data;
        
        if(!(data = new T[arraySize])) return false;
        
        for (int i = 0; i < nData; i++)
            data[i] = temp[i];
        
        delete [] temp;
    }
    data[nData++] = item;
    return true;
}

template <class T> bool DynArray<T>:: truncate(){
    if (nData != arraySize) {
        T *temp = data;
        arraySize = nData;
        
        if(!(data = new T[arraySize])) return false;
        
        for (int i = 0; i < nData; i++)
            data[i] = temp[i];
        
        delete [] temp;
    }
}


#endif //_DYNARRAY_H_