#ifndef MPAIR_H 
#define MPAIR_H 

template <typename K, typename V>
struct MPair{
    K key;
    vector<V> value_list;

    //--------------------------------------------------------------------------------
    /*      MPair CTORs:
     *  must have these CTORs:
     *  - default CTOR / CTOR with a key and no value: this will create an empty vector
     *  - CTOR with a key AND a value: pushes the value into the value_list
     *  _ CTOR with a key and a vector of values (to replace value_list)
     */
    //--------------------------------------------------------------------------------
    MPair(const K& k=K());
    MPair(const K& k, const V& v);
    MPair(const K& k, const vector<V>& vlist);
    //--------------------------------------------------------------------------------

    //You'll need to overlod << for your vector:
    friend ostream& operator <<(ostream& outs, const MPair<K, V>& print_me);
    
    friend bool operator ==(const MPair<K, V>& lhs, const MPair<K, V>& rhs);
    friend bool operator < (const MPair<K, V>& lhs, const MPair<K, V>& rhs);
    friend bool operator <= (const MPair<K, V>& lhs, const MPair<K, V>& rhs);
    friend bool operator > (const MPair<K, V>& lhs, const MPair<K, V>& rhs);
    friend MPair<K, V> operator + (const MPair<K, V>& lhs, const MPair<K, V>& rhs);
};

#endif
