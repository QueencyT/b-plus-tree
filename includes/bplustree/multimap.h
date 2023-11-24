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
            _it = mmap.begin(); 
            //dups ok is true for mmap
        }

        Iterator(typename map_base::Iterator it){
            _it = it; 
        }

        Iterator operator ++(int unused){
            _it++
            return _it; 
        }

        Iterator operator ++(){
            _it++; 
            return _it; 
        }
        
        MPair<K, V> operator *(){
            return *_it; 
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
        return mmap.begin();
    }

    Iterator end(){
        return mmap.end(); 
    }

//  Capacity
    int size() const{
        return mmap.size(); 
    }
    bool empty() const{
        return mmap.empty(); 
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
        MPair<K,V> insertPair(k,v); 
        mmap.insert(insertPair); 
    }

    void erase(const K& key){
        
    }

    void clear(){
        mmap.clear_tree(); 
    }

//  Operations:
    bool contains(const K& key) const{
        MPair<K,V> findThis(key,0);
        return mmap.contains(findThis); 
    }

    vector<V> &get(const K& key){
        MPair<K,V> getThis(key, 0); 
        MPair<K,V> found = mmap.get(getThis); 
        return found.value_list; 
    }

    Iterator find(const K& key){
        MPair<K,V> findThis(key, 0);
        return mmap.find(findThis); 
    }

    
    int count(const K& key){ //count of what??
        return 0; 
    }
    // I have not writtent hese yet, but we will need them:
    //    int count(const K& key);
    //    lower_bound
    //    upper_bound
    //    equal_range:

    
    Iterator lower_bound(const K& key){
        return mmap.lower_bound(); 
    }

    Iterator upper_bound(const K& key){
        return mmap.upper_bound(); 
    }


    const V& at(const K& key) const{
        MPair<K,V> findThis(key, 0);
        const MPair<K,V> found = mmap.get(findThis); 
        return found.value_list; 
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