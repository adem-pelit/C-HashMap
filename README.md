#düzenlenecek!
# C-HashMap
This is a HashMap implementation in C programming language. Simply speaking it is a Collection struct which uses Key(char*) and Data pairs(void*). Each Key maps to a corresponding Value. In HashMap structure, reaching a Key and Data pair is faster than a normal list because of hashing system. In this HashMap impelementation, the struct of Hashmap has an array that given size. When you add a Key and Data pair, the pair must place in the element of this array thats index is calculated by Hashing function. But pairs can have same index. To prevent this causing a problem, every element of array contains a doubly linkedList and pairs that have same index is place in same list. In short, HashMap is a list that divided little into lists to reduce the cost of procedures.(Of course there are several different approach)
# CODE
## struct NODE
It is struct that contains the data. It has key(char*), data(void*), next and previous nodes.
## struct List
List is a struct that implements doubly linkedList. It contains NODE's to store the data.
## struct HashMap
HashMap struct has an array of List and size of the array.
## List* CreateList()
Creates a List and returns.
## del()
Deletes data by a key that given as a parameter.
## DelList()
Deletes List that given as a parameter and every NODE in this List.
## NODE* Add()
Adds a NODE with given key and data as parameters.
## int dolas()
This function can be used for wander the list. Every iteration, it changes gez NODE pointer as gez's next NODE's point if ne
## NODE* find()
Finds data by a key that given as a parameter.
## HashMap* CreateHashMap()
Creates a HashMap and returns it.
## int hashing()
Calculates hash code by given size and key.
## int add()

## List* HashMapToList()

## HashMap* ListToHashMap()

## HashMap* rehash()

## NODE* get()

## int Del()

## DestroyHM

## int lengthHM()

## int UsedList()

## void Dolas()
