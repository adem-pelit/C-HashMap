#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
	char* key;
	void* data;
	struct node* next;
	struct node* prev;
}NODE;

typedef struct list{
	NODE* ilk;
	NODE* son;
	NODE* gez;
	int count;
	void  (*del)     (struct list*, NODE*);
	void  (*DelList) (struct list*       );
	NODE* (*Add)     (struct list*, void*);
	int   (*dolas)   (struct list*, int  );
	NODE* (*find)    (struct list*, char*);

}List;

List* CreateList(void  (*del)     (struct list*, NODE*),
				 void  (*DelList) (struct list*       ),
				 NODE* (*Add)     (struct list*, void*),
				 int   (dolas)    (struct list*, int  ),
				 NODE* (find)     (struct list*, char*)){
	List* l = (List*) malloc(sizeof(List));
	l->count = 0;
	l->gez = NULL;
	l->ilk = NULL;
	l->son = NULL;
	l->del = del;
	l->DelList = DelList;
	l->Add = Add;
	l->dolas = dolas;
	l->find = find;
	return l;
}

void del(List* list, NODE* node){

	if(list == NULL) return;
	if(list->ilk == NULL) return;
	if(node == NULL) return;

	if(node == list->ilk && node == list->son){

		list->count = 0;
		list->gez = NULL;
		list->ilk = NULL;
		list->son = NULL;
		free(node);
		return;
	}
	if(node == list->ilk){

		if(list->ilk == NULL)
		if(node->next == NULL)
		list->ilk = node->next;
		node->next->prev = NULL;
		free(node);
		list->gez = NULL;

	}
	else if(node == list->son){

		node->prev->next = NULL;
		list->son = node->prev;
		free(node);
		list->gez = NULL;
	}
	else{

		node->next->prev = node->prev;
		node->prev->next = node->next;
		free(node);
		list->gez = NULL;
	}
	list->count--;
}

void DelList(List* list){
	while(list->ilk != NULL){
		del(list, list->ilk);
	}
	free(list);
}

NODE* Add(List* list, void* data){
	NODE* node = (NODE*) malloc(sizeof(NODE));
	node->data = data;
	if(list->ilk == NULL){
		list->ilk = node;
		list->son = node;
		node->next = NULL;
		node->prev = NULL;
		list->count++;
		return node;
	}
	node->next = NULL;
	list->son->next = node;
	node->prev = list->son;
	list->son  = node;
	list->count++;
	return node;
}

int dolas(List* list, int yon){
	if(list->ilk == NULL) return 0;
	if(yon == 1){
		if(list->gez == NULL){
			list->gez = list->ilk;
			return 1;
		}
		if(list->gez->next == NULL){
			list->gez = NULL;
			return 0;
		}
		list->gez = list->gez->next;
		return 1;
	}
	if(yon == -1){
		if(list->gez == NULL){
			list->gez = list->son;
			return 1;
		}
		if(list->gez->prev == NULL){
			list->gez = NULL;
			return 0;
		}
		list->gez = list->gez->prev;
	}
}

NODE* find(List* list, char* key){
	NODE* temp;
	while(dolas(list, 1)){
		if(strcmp(key, list->gez->key) == 0){
			temp = list->gez;
			list->gez = NULL;
			return temp;
		}
	}
	return NULL;
}

typedef struct HM{
	int size;
	void** map;
}HashMap;

HashMap* CreateHashMap(int size){
	HashMap* hm = (HashMap*) malloc(sizeof(HashMap));
	hm->size = size;
	hm->map = (void**) calloc(sizeof(void*),hm->size);
	for(int i= 0; i<hm->size; i++){
		hm->map[i] = (void*) CreateList(del,DelList,Add,dolas,find);
	}
	List* l = (List*)hm->map[5];
	return hm;
}

int hashing(char* text, int size){
	int len = strlen(text);
	int sum = 0;
	for(int i=0; i<len; i++){
		sum += text[i];
	}
	sum %= size;
	return sum;
}

int add(HashMap* hm, char* key,void* data){
	int index = hashing(key, hm->size);
	List* list = (List*)(hm->map[index]);
	NODE* node = list->Add(list, data);
	node->key = (char*) malloc(strlen(key));
	strcpy(node->key, key);
}

List* HashMapToList(HashMap* hm){
	List* list = CreateList(del,DelList,Add,dolas,find);
	for(int i=0; i<hm->size; i++){
		List* l = (List*)hm->map[i];
		while(l->dolas(l,1)){
			NODE* node = list->Add(list, l->gez);
			node->key = (char*) malloc(strlen(l->gez->key));
            strcpy(node->key, l->gez->key);
		}
	}
	return list;
}

HashMap* ListToHashMap(List* list, int size){
	HashMap* hm = CreateHashMap(size);
	while(list->dolas(list, 1)){
		if(list->gez == NULL){
			return NULL;
		}
		add(hm, list->gez->key, list->gez->data);
	}
	return hm;
}

HashMap* rehash(HashMap* hm, int size){
    HashMap* hmNew = CreateHashMap(size);
    for(int i=0; i<hm->size; i++){
		List* l = (List*)hm->map[i];
		while(l->dolas(l,1)){
            add(hmNew, l->gez->key, l->gez->data);
		}
	}
    for(int i=0; i<hm->size; i++){
		List* l = (List*)hm->map[i];
		free(l);
	}free(hm);


    return hmNew;
}

NODE* get(HashMap* hm, char* key){
	int index = hashing(key, hm->size);
	List* list = (List*)hm->map[index];
	return list->find(list, key);
}

int Del(HashMap* hm, char* key){
	int index = hashing(key, hm->size);
	List* list = (List*)hm->map[index];
	NODE* node = list->find(list, key);

	if(node == NULL){
		return 0;
	}
	list->del(list, node);
	return 1;
}

void DestroyHM(HashMap* hm){
	for(int i=0; i<hm->size; i++){
		List* l = (list*)hm->map[i];
		l->DelList(l);
	}
	free(hm);
	hm == NULL;
}

int lengthHM(HashMap* hm){
	int used = 0;
	for(int i=0; i<hm->size; i++){
		List* l = (list*)hm->map[i];
		used += l->count;
	}
	return used;
}

int UsedList(HashMap* hm){
	int used = 0;
	for(int i=0; i<hm->size; i++){
		List* l = (list*)hm->map[i];
		if(l->count > 0){
			used++;
		}
	}
	return used;
}

void Dolas(HashMap* hm, void(func)(void*)){
	for(int i=0; i<hm->size; i++){
		List* l = (List*)hm->map[i];
		while(l->dolas(l, 1)){
			func(l->gez->data);
		}
	}
}

 //for more, read the readme.md
 //for problem or suggestion, contact me: apelit55@gmail.com
