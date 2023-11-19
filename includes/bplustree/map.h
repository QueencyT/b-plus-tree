#ifndef MAP_H 
#define MAP_H 

#include "../../includes/bplustree/pair.h"
#include "../../includes/bplustree/bplustree.h"

template <typename K, typename V>
class Map
{
public:
    typedef BPlusTree<Pair<K, V> > map_base;
    class Iterator{
    public:
        friend class Map;
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

        Pair<K, V> operator *(){
            Pair<K,V> somePair; 
            return somePair; 
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

    Map(){
        key_count = 0;
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
    V& operator[](const K& key){
        V someObj; 
        return someObj; 
    }

    V& at(const K& key){
        V someObj; 
        return someObj; 
    }

    const V& at(const K& key) const{
        V someObj; 
        return someObj; 
    }


//  Modifiers
    void insert(const K& k, const V& v){
        
    }
    void erase(const K& key){

    }
    void clear(){

    }
    V get(const K& key){
        V someObj; 
        return someObj; 
    }

//  Operations:
    Iterator find(const K& key){
        Iterator temp; 
            return temp; 
    }
    bool contains(const Pair<K, V>& target) const{
        return true; 
    }

    // I have not writtent hese yet, but we will need them:
    //    int count(const K& key);
    //    lower_bound
    //    upper_bound
    //    equal_range:

    bool is_valid(){
       // return map.is_valid();
       return true; 
    }

    friend ostream& operator<<(ostream& outs, const Map<K, V>& print_me){
        outs<<print_me.map<<endl;
        return outs;
    }
private:
    int key_count;
    BPlusTree<Pair<K, V> > map;
};

#endif 

