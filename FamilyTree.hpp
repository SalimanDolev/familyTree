#include <stdio.h>
#include <iostream>
using namespace std;


namespace family{
    struct tree_node
    {
        string name;
        tree_node *mother;
        tree_node *father;
    };
    
    class Tree{
        private:
            string m_name;
            tree_node *root;
    
        public:
        // empty constructor
      /**  Tree(){
            m_name = "emty";
            root = NULL;
        }**/
        //constructor with variables
        Tree(string childName){
            //if(root == NULL){
                tree_node *a = new tree_node;
                root = a;
                root->name = childName;
                root->mother = NULL;
                root->father = NULL;
            /**}else{
                throw out_of_range("There is allready root");
            }**/
        }
        //functions
        Tree& addFather(string childName, string fatherName);
        Tree& addMother(string childName, string motherName);
        void display();
        string relation(string name);
        string find(string name);
        void remove (string name);
    };
};