#include "doctest.h"
#include "FamilyTree.hpp"
#include <string>

using namespace family;
using namespace std;


/////////////////////////////////////////////////////////////////////
////////////////////////Tree checks//////////////////////////////////
/////////////////////////////////////////////////////////////////////


TEST_CASE("Test new tree build") {
    CHECK_NOTHROW(family::Tree T ("Dolev"));
    CHECK_NOTHROW(family::Tree S ("Amit"));
    CHECK_NOTHROW(family::Tree L ("Saliman Dolev"));
    // checks add new root to tree EXEPTION
    CHECK_THROWS(family::Tree L ("Nofar"));

    CHECK_NOTHROW(family::Tree W ("L"));
    CHECK_NOTHROW(family::Tree B ("1"));
    CHECK_NOTHROW(family::Tree C ("f1"));
}

TEST_CASE("Test add memners") {
    family::Tree T ("Dolev");
    CHECK_NOTHROW(T.addFather("Dolev","Eyal"));
    CHECK_NOTHROW(T.addFather("Eyal","Yaakov"));
    CHECK_NOTHROW(T.addFather("Yaakov","Avraham"));
    CHECK_NOTHROW(T.addMother("Dolev","Rimona"));
    CHECK_NOTHROW(T.addMother("Eyal","Haviva"));
    CHECK_NOTHROW(T.addMother("Yaakov","Malka"));
    family::Tree K ("Amnon");
    CHECK_NOTHROW(K.addMother("Amnon","Malka").addFather("Amnon","Ariel"));
    family::Tree P ("Tony");
    CHECK_NOTHROW(P.addFather("Tony","Yosi").addMother("Tony","Monica"));
    family::Tree O ("Amir");
    CHECK_NOTHROW(O.addFather("Amir","Joseph").addFather("Joseph","Tal"));
    family::Tree U ("Meirav");
    CHECK_NOTHROW(U.addMother("Meirav","Lital").addMother("Lital","Koral"));    
}


TEST_CASE("Unknown members") {
    family::Tree S ("Dolev");
    CHECK_THROWS(S.find("aunt"));
    CHECK_THROWS(S.find("uncale"));
    CHECK_THROWS(S.find("brother"));
    CHECK_THROWS(S.find("sister"));
    CHECK_THROWS(S.find("brother in law"));
    CHECK_THROWS(S.find("sister in law"));
    CHECK_THROWS(S.find("brother in law"));
    CHECK_THROWS(S.find("mother in law"));
    CHECK_THROWS(S.find("father in law"));
    CHECK_THROWS(S.find("step brother"));
    CHECK_THROWS(S.find("step sister"));
    CHECK_THROWS(S.find("Friend"));

    family::Tree T ("Dolev");
    T.addMother("Dolev","Ravid").addFather("Dolev","Avraham").addMother("Ravid","Or").addFather("Avraham","Meni");
    CHECK_THROWS(S.find("aunt"));
    CHECK_THROWS(S.find("uncale"));
    CHECK_THROWS(S.find("brother"));
    CHECK_THROWS(S.find("sister"));
    CHECK_THROWS(S.find("brother in law"));
    CHECK_THROWS(S.find("sister in law"));
    CHECK_THROWS(S.find("brother in law"));
    CHECK_THROWS(S.find("A"));
    CHECK_THROWS(S.find("M"));
    CHECK_THROWS(S.find("L"));
    CHECK_THROWS(S.find("S"));
    CHECK_THROWS(S.find("I"));
    CHECK_THROWS(S.find("T"));
    CHECK_THROWS(S.find("B"));


}

TEST_CASE("Test relations") {
     family::Tree T ("Dolev");
    T.addFather("Dolev","Eyal");
    CHECK(T.relation("Eyal") == "father");
    T.addMother("Dolev","Rimona");
    CHECK(T.relation("Rimona") == "mother");
    T.addMother("Rimona","Dvora");
    CHECK(T.relation("Dvora") == "grandmother");
    T.addFather("Eyal","Yaakov");
    CHECK(T.relation("Yaakov") == "grandfather");
    T.addFather("Yaakov","Avraham");
    CHECK(T.relation("Avraham") == "great-grandfather");
    T.addMother("Dvora","Ravid");
    CHECK(T.relation("Ravid") == "great-grandmother");

    //Checks relations with no upper/lower case 
    CHECK(T.relation("eyal") == "father");
    CHECK(T.relation("rimona") == "mother");
    CHECK(T.relation("dvora") == "grandmother");
    CHECK(T.relation("yaakov") == "grandfather");
    CHECK(T.relation("avraham") == "great-grandfather");
    
    //Checks unrealated exaptions
    CHECK_THROWS(T.relation("O"));
    CHECK_THROWS(T.relation("Avi"));
    CHECK_THROWS(T.relation("L"));
    CHECK_THROWS(T.relation("R"));
    CHECK_THROWS(T.relation("Eya"));
}

TEST_CASE("Test multiple adds") {
     family::Tree T ("Dolev");
    T.addMother("Dolev","Ravid").addFather("Dolev","Avraham").addMother("Ravid","Or").addFather("Avraham","Meni");
    CHECK_THROWS(T.addMother("Dolev","Sima"));
    CHECK_THROWS(T.addFather("Dolev","Eli"));
    CHECK_THROWS(T.addFather("Avraham","Pol"));
    CHECK_THROWS(T.addMother("Ravid","Liora"));
    CHECK_THROWS(T.addMother("Dolev","R"));
    CHECK_THROWS(T.addFather("Dolev","E"));
    CHECK_THROWS(T.addFather("Avraham","P"));
    CHECK_THROWS(T.addMother("Ravid","L"));
    CHECK_THROWS(T.addMother("Avraham","E"));
    CHECK_THROWS(T.addFather("Dolev","M"));
    CHECK_THROWS(T.addFather("Avraham","Q"));
    CHECK_THROWS(T.addMother("Ravid","R"));
}


TEST_CASE("Test display") {
    family::Tree T ("Dolev");
    T.addMother("Dolev","Ravid").addFather("Dolev","Avraham").addMother("Ravid","Or").addFather("Avraham","Meni");
    CHECK_NOTHROW(T.display());
    family::Tree K ("Gil");
    K.addMother("Gil","Orna").addFather("Gil","Odi").addMother("Orna","Emily").addFather("Orna","Meni")
    .addFather("Odi","Tamir").addMother("Odi","Reut");
    CHECK_THROWS(K.display());
    family::Tree D ("A");
    CHECK_NOTHROW(D.addFather("A","B").addFather("B","C").addFather("C","D").addFather("D","E"));
    family::Tree M ("A");
    CHECK_NOTHROW(M.addMother("A","B").addMother("B","C").addMother("C","D").addMother("D","E"));
}


TEST_CASE("Test find") {
    family::Tree K ("Gil");
    K.addMother("Gil","Orna").addFather("Gil","Odi").addMother("Orna","Emily").addFather("Orna","Meni")
    .addFather("Odi","Tamir").addMother("Odi","Reut");
    CHECK(K.find("mother") == "Orna");
    CHECK(K.find("father") == "Odi");
    CHECK(K.find("grand-mother") == "Emily");
    CHECK(K.find("grand-father") == "Meni");
    CHECK(K.find("great-grandfather") == "Tamir");
    CHECK(K.find("great-grandmother") == "Reut");

    //find EXEPTIONS
    CHECK_THROWS(K.find(""));
    CHECK_THROWS(K.find("A"));
    CHECK_THROWS(K.find("L"));
    CHECK_THROWS(K.find("M"));
    CHECK_THROWS(K.find("Lol"));
}

TEST_CASE("Test remove") {
    family::Tree K ("Gil");
    K.addMother("Gil","Orna").addFather("Gil","Odi").addMother("Orna","Emily").addFather("Orna","Meni")
    .addFather("Odi","Tamir").addMother("Odi","Reut");
    CHECK_NOTHROW(K.remove("Reut"));
    CHECK_NOTHROW(K.remove("Tamir"));
    CHECK_NOTHROW(K.remove("Meni"));
    CHECK_NOTHROW(K.remove("Emily"));
    CHECK_NOTHROW(K.remove("Odi"));
    CHECK_NOTHROW(K.remove("Orna"));
    CHECK_NOTHROW(K.display());

    //sopuse to print only root
    family::Tree P ("Gil");
    P.addMother("Gil","Orna").addFather("Gil","Odi").addMother("Orna","Emily").addFather("Orna","Meni")
    .addFather("Odi","Tamir").addMother("Odi","Reut");
    CHECK_NOTHROW(P.remove("Orna"));
    CHECK_NOTHROW(P.remove("Odi"));
    CHECK_NOTHROW(P.display());

    // supose to print only root
     family::Tree A ("Gil");
    A.addMother("Gil","Orna").addFather("Gil","Odi").addMother("Orna","Emily").addFather("Orna","Meni")
    .addFather("Odi","Tamir").addMother("Odi","Reut");

    // checks Exeptions
    CHECK_THROWS(A.remove("Amit"));
    CHECK_THROWS(A.remove("Uncale"));
    CHECK_THROWS(A.remove("B"));
    CHECK_THROWS(A.remove("L"));
}
