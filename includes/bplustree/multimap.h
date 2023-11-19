#ifndef MMAP_H 
#define MMAP_H 

#include "../../includes/bplustree/mpair.h"
#include <vector>

template <typename K, typename V>
class MMap
{
public:
    typedef BPlusTree<MPair<K, V> > map_base;
    class Iterator{
    public:
        friend class MMap;
        Iterator(){

        }
        Iterator(typename map_base::Iterator it){
            _it = it; 
        }
        Iterator operator ++(int unused){
            Iterator temp; 
            return temp; 
        }
        Iterator operator ++(){
            Iterator temp; 
            return temp; 
        }
        MPair<K, V> operator *(){
            MPair<K,V> someMap; 
            return someMap; 
        }
        friend bool operator ==(const Iterator& lhs, const Iterator& rhs){
            return true; 
        }
        friend bool operator !=(const Iterator& lhs, const Iterator& rhs){
            return true; 
        }

    private:
        typename map_base::Iterator _it;
    };

    MMap(){

    }

//  Iterators
    Iterator begin(){
        Iterator temp; 
        return temp;
    }
    Iterator end(){
        Iterator temp; 
        return temp;
    }

//  Capacity
    int size() const{
        return 0; 
    }
    bool empty() const{
        return true; 
    }

//  Element Access
    const vector<V>& operator[](const K& key) const{
        vector<V>* someVec = new vector<V>; 
        return *someVec; 
    }
    vector<V>& operator[](const K& key){
         vector<V>* someVec = new vector<V>; 
        return *someVec; 
    }

//  Modifiers
    void insert(const K& k, const V& v){

    }

    void erase(const K& key){

    }
    void clear(){

    }

//  Operations:
    bool contains(const K& key) const{
        return true; 
    }

    vector<V> &get(const K& key){
        vector<V> someVec = new vector<V>; 
        return someVec; 
    }

    Iterator find(const K& key){
        Iterator temp; 
        return temp; 
    }

    
    int count(const K& key){
        return 0; 
    }
    // I have not writtent hese yet, but we will need them:
    //    int count(const K& key);
    //    lower_bound
    //    upper_bound
    //    equal_range:

    
    Iterator lower_bound(const K& key){
        Iterator temp; 
        return temp; 
    }

    Iterator upper_bound(const K& key){
        Iterator temp; 
        return temp; 
    }

    

    //    upper_bound
    //    equal_range:


    const V& at(const K& key) const{
        V someObj = new V; 
        return someObj; 
    } 

    bool is_valid(){
        return true;
    }

    friend ostream& operator<<(ostream& outs, const MMap<K, V>& print_me){
        outs<<print_me.mmap<<endl;
        return outs;
    }

private:
    BPlusTree<MPair<K, V> > mmap;
};

#endif 