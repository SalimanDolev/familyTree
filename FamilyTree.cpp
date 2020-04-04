#include "FamilyTree.hpp"
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
using namespace family;

Tree& Tree::addFather(string childName, string fatherName){
 return (*this);
}
        
Tree& Tree::addMother(string childName, string motherName){
    return (*this);
}

void Tree::display(){
    
}

string Tree::relation(string name){
    string a ="asd";
    return a;
}

string Tree::find(string name){
    string a = "asd";
    if (name == "uncale"){
        throw out_of_range("The tree cannot handle the 'uncle' relation");
    }
    return a;
}

void Tree::remove (string name){

}