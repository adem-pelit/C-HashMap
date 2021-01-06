# C-HashMap
This is a HashMap implementation in C programming language. Simply speaking it is a Collection struct which uses Key(char*) and Data pairs(void*). Each Key maps to a corresponding Value. In HashMap structure, reaching a Key and Data pair is faster than a normal list because of hashing system. In this HashMap impelementation, the struct of Hashmap has an array that given size. When you add a Key and Data pair, the pair must place in the element of this array thats index is calculated by Hashing function. But pairs can have same index. To prevent this causing a problem, every element of array contains a doubly linkedList and pairs that have same index place in same list. In short, HashMap is a list that divided into little lists to reduce the cost of procedures.(Of course there are several different approach)
# CODE
## struct NODE
It is struct that contains the data. It has key(char*), data(void*), next and previous nodes.
## struct List
List is a struct that implements doubly linkedList. It contains NODEs to store the data.
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
This function can be used for wander the list. Every iteration, it changes gez NODE pointer as gez's next NODE's point.
## NODE* find()
Finds data by the key that given as a parameter.
## HashMap* CreateHashMap()
Creates a HashMap and returns it.
## int hashing()
Calculates hash code by key and given size.
## int add()
Adds given NODE into given HashMap.
## List* HashMapToList()
Casts given HashMap to a List and returns the list
## HashMap* ListToHashMap()
Casts given List to a HashMap and returns the HashMap.
## HashMap* rehash()
Changes number of elements in given Hashmap and returns the Hashmap 
## NODE* get()
Returns NODE by the key that given as a parameter.
## int Del()
Deletes the NODE by the key that given as a parameter.
## DestroyHM
Destroys given HashMap.
## int lengthHM()
Returns number of elements in HashMap that given as a parameter.
## int UsedList()
Returns number of list that is not empty in Given HashMap. 
## void Dolas()
This is the function that execute given function for every NODE in given HashMap. The function that given as a parameter have to return void and get one parameter thats type is NODE.
