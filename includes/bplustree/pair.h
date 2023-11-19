#ifndef PAIR_H 
#define PAIR_H 

template <typename K, typename V>
struct Pair{
    K key;
    V value;

    Pair(const K& k=K(), const V& v=V()){
        key = k; 
        value = v; 
    }
    friend ostream& operator <<(ostream& outs, const Pair<K, V>& print_me){
        return outs; 
    }
    friend bool operator ==(const Pair<K, V>& lhs, const Pair<K, V>& rhs){
        return true; 
    }
    friend bool operator < (const Pair<K, V>& lhs, const Pair<K, V>& rhs){
        return true; 
    }
    friend bool operator > (const Pair<K, V>& lhs, const Pair<K, V>& rhs){
        return true; 
    }
    friend bool operator <= (const Pair<K, V>& lhs, const Pair<K, V>& rhs){
        return true; 
    }
    friend Pair<K, V> operator + (const Pair<K, V>& lhs, const Pair<K, V>& rhs){
        return true; 
    }
};

#endif 
