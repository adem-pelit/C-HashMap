#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashMap.h"

//Students' names
char words[80][30] = {"Adain","Nolan","Edwyn","Maneet","Zaaine","Oakley","Campbel","Modu","Robert-Gordon","Tanvir","Aria","Damian","Johannes","Benny","Mac","Carrick","Ashtyn","Finnley","Precious","Zack","Reily","Elshan","Isa","Amos","Azlan","Kalum","Fergie","Robertjohn","Callyn","Dale","Zaki","Taylor-Lee","Griffyn","Chu","Mohamad","Danniel","Fergal","Krzysztof","Christy","Leyland","Jan","Maxx","Hassan","Albie","Jacob","Myles","Karamvir","Roark","Dex","Kainin","Dugald","Amrinder","Stephen","Tieran","Dominik","Mitchell","Calum","Kiarash","Abubakar","Dilano","Joris","Ayyub","Ardal","Michat","Azedine","Walid","Dominick","Darryl","Abdulkadir","Damien","Zayd","Max","Reggie","Jayden","Shayan","Laurence","Jensyn","Emanuel","Simon","Dougal"};

//Our data will be this
typedef struct stdnt{
    char* Name;
    int Id;
    int Class;
}Student;

//a function to create Student
Student* createStudent(char* Name, int Id, int Class){
    Student* stdnt = (Student*) malloc(sizeof(Student));
    stdnt->Class = Class;
    stdnt->Id = Id;
    stdnt->Name = (char*) malloc(sizeof(Name));
    strcpy(stdnt->Name,Name);
    return stdnt;
}

//a function to print the given Student
void printS(Student* s){
    printf("Name: %s\nId: %d\nClass %d\n\n", s->Name, s->Id, s->Class);
}

int main(){
    //Creating the HashMap
    HashMap* hm = CreateHashMap(5);
    for(int i=0; i<80; i++){
        //Creating student with names that is given in words[][]
        Student* student = createStudent(words[i], rand(), rand()%4+1);
        //adding the created Student into the HashMap (key will be the name and the value is Student struct)
        add(hm, words[i], student);
    }
    for(int i=0; i<80; i++){
        //Finding a data by its key and return the node that contains the data
        NODE* node = get(hm, words[i]);
        //printing Student (data of the node is casted Student* because it defined as void*)
        printS((Student*)node->data);
    }
    printf("the size of the HashMap: %d\n", lengthHM(hm));
    //for more, read the readme.md
    //for problem or suggestion, contact me: apelit55@gmail.com
}
