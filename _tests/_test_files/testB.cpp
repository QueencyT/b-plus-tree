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

    //BPlusTree<int>* last; 
    //copyTree.copy_tree(mTree, last); 

    //cout<<"copied tree: \n"; 
    //copyTree.print_tree(); 

    //cout<<"last node: "<<last->data[1]<<endl; 
    //cout<<"last: child count: "<<last->child_count<<endl; 
  }
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
  EXPECT_EQ(1, test_copy(true)); 
}



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running testB.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}

