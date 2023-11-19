#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>
using namespace std;

#include "../../includes/bplustree/bplustree.h"

bool test_copy(bool debug){
  if(debug){
    BPlusTree<int> mTree; 
    BPlusTree<int> copyTree; 

    int data[] = {10,20,30,40};
    int size = 4;  
    srand(time(0)); 
    int rando; 

    for(int i = 0; i < 25; i++){
      rando = rand() % 800 + 100;  
      mTree.insert(rando);
    }
    cout<<"curr tree struct: \n"; 
    mTree.print_tree(0, cout); //so far seems to be working 

    BPlusTree<int>* last; 
    copyTree.copy_tree(mTree, last); 

    cout<<"copied tree: \n"; 
    copyTree.print_tree(); 

    cout<<"last node: "<<last->data[1]<<endl; 
    cout<<"last: child count: "<<last->child_count<<endl; 

    string inorder1 = mTree.in_order(); 
    string inorder2 = copyTree.in_order(); 
    cout<<"orig in order: "<<inorder1<<endl; 
    cout<<"copy in order: "<<inorder2<<endl; 
    return (inorder1 == inorder2); 
  }
}

bool test_remove(bool debug){
  //removing - root case - problem 

  if(false){
    cout<<"TEST - MERGING BEGINNING CASE - REMOVE - SIMPLE\n"; 
    int data[] = {180, 200, 120, 190}; 
    BPlusTree<int> mTree(data, 4); 
    cout<<"tree before removal: "<<endl; 
    mTree.print_tree(); 

    cout<<"after removing 120\n"; 
    mTree.remove(120); 
    cout<<mTree<<endl; 
    cout<<"in order: "<<mTree.in_order()<<endl; 

  }

  if(false){
    cout<<"TEST - STEAL FROM RIGHT CASE - REMOVE - SIMPLE\n"; 
    int data[] = {180, 200, 120, 190}; 
    BPlusTree<int> mTree(data, 4); 
    cout<<"tree before removal: "<<endl; 
    mTree.print_tree(); 

    cout<<"after removing 180\n"; 
    mTree.remove(180); 
    cout<<mTree<<endl; 
    cout<<"in order: "<<mTree.in_order()<<endl; 

  }

  if(false){
    cout<<"TEST - STEAL FROM LEFT CASE - REMOVE - SIMPLE\n"; 
    int data[] = {842, 845,648, 513, 846}; 
    BPlusTree<int> mTree(data, 5); 
    cout<<"tree before removal: "<<endl; 
    mTree.remove(846); 
    mTree.print_tree(); 
    cout<<endl; 

    cout<<"after removing 842\n"; 
    mTree.remove(842); 
    cout<<mTree<<endl; 
    cout<<"in order: "<<mTree.in_order()<<endl; 
  }

  if(false){
    cout<<"TEST - REMOVE - SPECIFIC CASE\n"; 
    int data[] = {176, 289, 317, 346, 412, 466, 483, 494, 513, 592, 644}; 
    int data2[] = {318,604,695, 200, 385, 100,150, 950}; 
    BPlusTree<int> mTree(data, 11); 
    cout<<"curr tree: "<<endl; 
    cout<<mTree<<endl; 


    cout<<"removing: "<<317<<endl; 
    mTree.remove(317); 
    cout<<mTree<<endl; 
    cout<<"in order: "<<mTree.in_order()<<endl; 

  }
  if(true){
    cout<<"TEST - REMOVE - COMPLEX CASE\n"; 
    BPlusTree<int> mTree; 
    srand(time(0)); 

    for(int i = 0; i < 10; i++){
      int rando = rand() % 800 + 100; 
      mTree.insert(rando); 
    }

    cout<<"Initial tree: "<<endl; 
    cout<<mTree<<endl; 

    while(!mTree.empty()){
      int rando = rand() % 800 + 100; 
      if(mTree.contains(rando)){
        cout<<"REMOVING: "<<rando<<endl; 
        mTree.remove(rando); 
        cout<<mTree<<endl; 
        cout<<"in order: "<<mTree.in_order()<<endl; 
        cout<<"size: "<<mTree.size()<<endl; 
        cout<<"--------------------------\n"; 
        if(mTree.contains(rando)){
          cout<<"FAILED TO REMOVE: "<<rando<<endl; 
          cout<<mTree<<endl; 
          cout<<"in order: "<<mTree.in_order()<<endl; 
        }
      }  
    }
  }

  return true; 
}

bool test_stub(bool debug = false)
{
  if (debug){
    cout << "testB:: test-sub() entering test_sub" << endl;
  }
  return true;
}

TEST(TEST_STUB, TestStub) {
  
  //EXPECT_EQ(0, <your individual test functions are called here>);

  EXPECT_EQ(1, test_stub(false));
}

TEST(TEST_COPY, testCopy){
  EXPECT_EQ(1, test_copy(false)); 
}

TEST(TEST_REMOVE, testRemove){
  EXPECT_EQ(1, test_remove(true));
}



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running testB.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}

