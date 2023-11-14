#ifndef BPLUS_TREE_H 
#define BPLUS_TREE_H 

#include "../../includes/btree/btree.h"
#include "../../includes/bplustree/btree_array_functions.h"

template <class T>
class BPlusTree
{
public:
    class Iterator{
    public:
        friend class BPlusTree;
        Iterator(BPlusTree<T>* _it=NULL, int _key_ptr = 0): it(_it), key_ptr(_key_ptr){}


        //return first data item in b plus tree
        T operator *(){
            //return it->data[0]; 
        }

        Iterator operator++(int un_used){//hmm?
            Iterator returnIter(it->_next, key_ptr++); 
            return returnIter; 
        }

        Iterator operator++(){//hmm?
            Iterator returnIter(it->next, key_ptr++); 
            return returnIter; 
        }

        friend bool operator ==(const Iterator& lhs, const Iterator& rhs){ //what is keyptr
            return (lhs._it == rhs._it && lhs.key_ptr == rhs.key_ptr); 
        }
        friend bool operator !=(const Iterator& lhs, const Iterator& rhs){
            return(!(lhs == rhs)); 
        }

        void print_Iterator(){
            if (it){
                cout<<"iterator: ";
                print_array(it->data, it->data_count, key_ptr);
            }
            else{
                cout<<"iterator: NULL, key_ptr: "<<key_ptr<<endl;
            }
        }

        bool is_null(){
            return !it;
        }

        void info(){
            cout<<endl<<"Iterator info:"<<endl;
            cout<<"key_ptr: "<<key_ptr<<endl;
            cout<<"it: "<<*it<<endl;
        }

    private:
        BPlusTree<T>* it;
        int key_ptr;
    };

    BPlusTree(bool dups = false);
    BPlusTree(T *a, int size, bool dups = false);

    //big three:
    BPlusTree(const BPlusTree<T>& other);
    ~BPlusTree();
    BPlusTree<T>& operator =(const BPlusTree<T>& RHS);

    void copy_tree(const BPlusTree<T>& other);  //copy other into this object
    void copy_tree(const BPlusTree<T>& other, BPlusTree<T>*& last_node);

    void insert(const T& entry);   //insert entry into the tree
    void remove(const T& entry);   //remove entry from the tree
    void clear_tree();             //clear this object (delete all nodes etc.)

    bool contains(const T& entry) const; //true if entry can be found
    T& get(const T& entry);              //return a reference to entry
    const T& get(const T& entry)const;   //return a reference to entry
    T& get_existing(const T& entry);     //return a reference to entry
    Iterator find(const T& key);         //return an iterator to this key.
                                         //     NULL if not there.
    Iterator lower_bound(const T& key);  //return first that goes NOT BEFORE
                                         // key entry or next if does not
                                         // exist: >= entry
    Iterator upper_bound(const T& key);  //return first that goes AFTER key
                                         //exist or not, the next entry  >entry

    int size() const;                    //count the number of elements

    bool empty() const;                  //true if the tree is empty

    void print_tree(int level = 0,
                    ostream &outs=cout) const;
    friend ostream& operator<<(ostream& outs, const BPlusTree<T>& print_me){
        print_me.print_tree(0, outs);
        return outs;
    }

    bool is_valid();
    string in_order();

    Iterator begin();
    Iterator end();
    ostream& list_keys(Iterator from = NULL, Iterator to = NULL){
        if (from == NULL) from = begin();
        if (to == NULL) to = end();
        for (Iterator it = from; it != to; it++)
            cout<<*it<<" ";
        return cout;

    }

    static const int MINIMUM = 1;
    static const int MAXIMUM = 2 * MINIMUM;

    bool dups_ok;                        //true if duplicate keys are allowed
    int data_count;                      //number of data elements
    T data[MAXIMUM + 1];                 //holds the keys
    int child_count;                     //number of children
    BPlusTree* subset[MAXIMUM + 2];      //subtrees
    BPlusTree* next;

private:

    /*static const int MINIMUM = 1;
    static const int MAXIMUM = 2 * MINIMUM;

    bool dups_ok;                        //true if duplicate keys are allowed
    int data_count;                      //number of data elements
    T data[MAXIMUM + 1];                 //holds the keys
    int child_count;                     //number of children
    BPlusTree* subset[MAXIMUM + 2];      //subtrees
    BPlusTree* next;*/


    bool is_leaf() const{
        return (child_count==0); //next == nullptr 
    }             //true if this is a leaf node

    T* find_ptr(const T& entry);         //return a pointer to this key.
                                         // NULL if not there.

    //insert element functions
    void loose_insert(const T& entry);   //allows MAXIMUM+1 data elements in
                                         //   the root
    void fix_excess(int i);              //fix excess in child i

    //remove element functions:
    void loose_remove(const T& entry);  //allows MINIMUM-1 data elements
                                        //  in the root

    BPlusTree<T>* fix_shortage(int i);  //fix shortage in child i
    // and return the smallest key in this subtree
    BPlusTree<T>* get_smallest_node();
    void get_smallest(T& entry);      //entry := leftmost leaf
    void get_biggest(T& entry);       //entry := rightmost leaf
    void remove_biggest(T& entry);    //remove the biggest child of tree->entry
    void transfer_left(int i);        //transfer one element LEFT from child i
    void transfer_right(int i);       //transfer one element RIGHT from child i
    BPlusTree<T> *merge_with_next_subset(int i); //merge subset i with  i+1

};

template <typename T>
BPlusTree<T>::BPlusTree(bool dups){
    next = nullptr; 
    data_count = 0; 
    child_count = 0; 
    dups_ok = dups; 
}

template <typename T>
BPlusTree<T>::BPlusTree(T *a, int size, bool dups){ //making a btree
    next = nullptr; 
    dups_ok = dups; 
    for(int i = 0; i < size; i++){
        insert(a[i]); 
    }
}

//big three:

template <typename T>
BPlusTree<T>::BPlusTree(const BPlusTree<T>& other){

}

template <typename T>
BPlusTree<T>::~BPlusTree(){

}


template <typename T>
BPlusTree<T>& BPlusTree<T>::operator =(const BPlusTree<T>& RHS){

}

template <typename T>
void BPlusTree<T>::copy_tree(const BPlusTree<T>& other){
    copy_array(data, other.data, data_count, other.data_count); //copying other data 
    child_count = other.child_count;
    for(int i = 0; i < other.child_count; i++){//if other is a leaf then there is nothing else to copy
        BPlusTree<T>* copyChild = new BPlusTree<T>; 
        subset[i] = copyChild; 
        subset[i]->copy_tree(*other.subset[i]);
    }
}//copy other into this object

template <typename T>
void BPlusTree<T>::copy_tree(const BPlusTree<T>& other, BPlusTree<T>*& last_node){ //hmm oh our last node?? that we update
    copy_array(data, other.data, data_count, other.data_count); //copying other data 
    child_count = other.child_count;
    for(int i = 0; i < other.child_count; i++){//if other is a leaf then there is nothing else to copy
        BPlusTree<T>* copyChild = new BPlusTree<T>; 
        subset[i] = copyChild;
        last_node = subset[i];  
        subset[i]->copy_tree(*other.subset[i], last_node);
    }
}


//insert element functions
template <typename T>
void BPlusTree<T>::loose_insert(const T& entry){
    int insertIndex = first_ge(data, data_count, entry);
    if(is_leaf()){ //if we finally reached leaf, insert //still want to insert in leaf, even in BPlusTree 
        ordered_insert(data, data_count, entry); //should update next in fix_excess 
        return;  
    }

    subset[insertIndex]->loose_insert(entry);
    BPlusTree<T>* fatChild = subset[insertIndex]; //possibly fat child //it has to be the subset at the insertedIndex whos fat 

    if(fatChild->data_count > MAXIMUM){//we are in excess 
        fix_excess(insertIndex); 
    }
}  //allows MAXIMUM+1 data elements in the root

template <typename T>
void BPlusTree<T>::fix_excess(int fatIndex){
    BPlusTree<T>* fat = subset[fatIndex]; 
    T attach;
    BPlusTree<T>* right = new BPlusTree<T>; 
    //attach to parent
    delete_item(fat->data, MAXIMUM/2, fat->data_count, attach); //deleting from fat 5  

    split(fat->data, fat->data_count, right->data, right->data_count);
    split(fat->subset, fat->child_count, right->subset, right->child_count); 

    ordered_insert(data, data_count, attach);  //attaching to parent 5 

    insert_item(subset, fatIndex + 1, child_count, right); //and then insert our new child into data
   
    if(fat->is_leaf()){
        ordered_insert(right->data, right->data_count, attach); //it should insert in beginning of right again //reinsrting attach to right
        right->next = fat->next; 
        fat->next = right;
    }
}             //fix excess in child i 


template <typename T>
void BPlusTree<T>::insert(const T& entry){
    if(find_ptr(entry))//not allowing dups
       return; 
  
    loose_insert(entry);

    if(data_count > MAXIMUM){//if the root is in excess, //fixing root excess 
        T attach; 
        BPlusTree<T>* copy = new BPlusTree<T>; 

        copy_array(copy->data, data, copy->data_count, data_count); //copying data into copy 
        copy_array(copy->subset, subset, copy->child_count, child_count); //copying children into copy 

        //now set ourself to 
        data_count = 0; 
        child_count = 1; 
        subset[0] = copy; 
        fix_excess(0); //0 being fat index
    }
}//insert entry into the tree



//remove element functions:
template <typename T>
void BPlusTree<T>::loose_remove(const T& entry){
    int goToIndex = first_ge(data, data_count, entry); 

    if(goToIndex < data_count && data[goToIndex] == entry && is_leaf()){//found //kee
        T temp; 
        delete_item(data, goToIndex, data_count, temp); 
        if(!is_leaf()){ //of we are not leaf
            T replaceWith; 
            //subset[goToIndex]->remove_biggest(replaceWith); //so we don't go to excess replace of this subtree we found
            //ordered_insert(data, data_count, replaceWith);
        }
    }
    else if(is_leaf()){ //leaf and not found
        return;
    }
    else{
        subset[goToIndex]->loose_remove(entry);
    }

    if(!is_leaf() && subset[goToIndex]->data_count < MINIMUM){
        fix_shortage(goToIndex); //goToIndex should be short index
    }   
}//allows MINIMUM-1 data elements
                                    //  in the root

template <typename T>
BPlusTree<T>* BPlusTree<T>::fix_shortage(int i){
    BPlusTree<T>* temp; 
    return temp; 
}  //fix shortage in child i
// and return the smallest key in this subtree

template <typename T>
BPlusTree<T>* BPlusTree<T>::get_smallest_node(){
     BPlusTree<T>* temp; 
    return temp; 
}

template <typename T>
void BPlusTree<T>::get_smallest(T& entry){
     BPlusTree<T>* temp; 
    return temp; 
}      //entry := leftmost leaf

template <typename T>
void BPlusTree<T>::get_biggest(T& entry){
     BPlusTree<T>* temp; 
    return temp; 
}       //entry := rightmost leaf

template <typename T>
void BPlusTree<T>::remove_biggest(T& entry){
     BPlusTree<T>* temp; 
    return temp; 
}   //remove the biggest child of tree->entry

template <typename T>
void BPlusTree<T>::transfer_left(int i){

} //transfer one element LEFT from child i

template <typename T>
void BPlusTree<T>::transfer_right(int i){

} //transfer one element RIGHT from child i

template <typename T>
BPlusTree<T>* BPlusTree<T>::merge_with_next_subset(int i){
     BPlusTree<T>* temp; 
    return temp; 
}//merge subset i with  i+1

template <typename T>
void BPlusTree<T>::remove(const T& entry){
    if(empty()){
        return; //nothing to remove
    }

    loose_remove(entry); 
    BPlusTree<T>* child = subset[0];  
    if(data_count == 0 && !is_leaf()){//if we ourself is short  
        child_count = 0;
        copy_array(data, child->data, data_count, child->data_count);
        copy_array(subset, child->subset, child_count, child->child_count); 

        child->data_count = 0; 
        child->child_count = 0; 
        delete child; 
        child = nullptr; 
    }
}//remove entry from the tree

template <typename T>
void BPlusTree<T>::clear_tree(){ //don't think we need to do anything to next 
    for(int i = 0; i < child_count; i++){ //meaning there is some child to clear
        if(!is_leaf())
            subset[i]->clear_tree();  //we go to child and clear it 
        delete subset[i]; 
        subset[i] = nullptr; //now setting it to null when we get out cause it was deleted. just for sanity 
    }
    data_count = 0; 
    child_count = 0;
}    
//clear this object (delete all nodes etc.)

template <typename T>
bool BPlusTree<T>::contains(const T& entry) const{
    T* found = find_ptr(entry); 
    return (found); //so found
} 

//true if entry can be found

template <typename T>
T& BPlusTree<T>::get(const T& entry){
    T* found = find_ptr(entry); 
    return *found; 
}//return a reference to entry

template <typename T>
const T& BPlusTree<T>::get(const T& entry) const{
    T* found = find_ptr(entry); 
    return *found; 
}//return a reference to entry

template <typename T>
T& BPlusTree<T>::get_existing(const T& entry){
    T* found = find_ptr(entry); 
    return *found; 
}//return a reference to entry


template <typename T>
int BPlusTree<T>::size() const{//do we include the duplicates? //curr btree code includes dups 10 in node, 10 in leafs
    int size = data_count; //count ourself
    for(int i = 0; i < child_count; i++){
        if(subset[i])
            size += subset[i]->size(); 
    }
    return size;
}        

//count the number of elements

template <typename T>
bool BPlusTree<T>::empty() const{
    return (data_count == 0 && child_count == 0); 
}
//true if the tree is empty


template <typename T>
void BPlusTree<T>::print_tree(int level, ostream &outs) const{
    for(int i = data_count; i >= 0; i--){//because start from rightmost 
        if(i!= -1 && !is_leaf())
            subset[i]->print_tree(level + 1, outs); //child will always be one more than data count  
        if(i!= 0){
            outs<<setw(6 * level)<<"["<<data[i - 1]<<"]"<<"cc: "<<child_count; 
           // if(next)
                //outs<<"next: "<<next->data[0];  
            outs<<endl; 
        }
    }
}

template <typename T>
bool BPlusTree<T>::is_valid(){

}

template <typename T>
string BPlusTree<T>::in_order(){
    string inOrder = ""; 
    for(int i = 0; i <= data_count; i++){
        if(!is_leaf())
            inOrder += subset[i]->in_order();
        if(i < data_count) 
            inOrder+= to_string(data[i]) + "|"; 
    }
    return inOrder; 
}

//PRIVATE FUNCTIONS 
template <typename T>
T* BPlusTree<T>::find_ptr(const T& entry){ //find should be fine 
    int index = first_ge(data, data_count, entry); 
    T* foundPtr = nullptr; 
  
    if(index < data_count && data[index] == entry && is_leaf()){ //go right --> else entry must be kess so we go left =
        foundPtr = (data + index); //no we don't want this 
    }
    else if(index < data_count && data[index] == entry){
       foundPtr = subset[index + 1]->find_ptr(entry); 
    }
    else if(is_leaf()){
        return nullptr; //no children and not found 
    }
    else{
       foundPtr = subset[index]->find_ptr(entry); //go left or right depending on what index
    }
    return foundPtr; 
}
//return a pointer to this key. // NULL if not there.

//update next


#endif
