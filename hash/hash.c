#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

//int countId;

HashPointer hashInit(int size) {
	HashPointer hashT= (HashPointer)malloc(sizeof(Hash));
	BeginPointer hash = (BeginPointer)malloc(sizeof(Begin)*size);
	hashT->hash = hash;
	hashT->countId = 1;
	hashT->size = size;
	int i;
	//countId = 1;
	for (i = 0; i < size; i++) {
		hash[i].quantity = 0;
		hash[i].next = NULL;
	}
	return hashT;
}
int hashInsert(const HashPointer hash, int (*h)(char*, int), const char* key) {

	int code = (*h)(key, hash->size);
	PointPointer point = (PointPointer)malloc(sizeof(Point));
	PointPointer Pi;
	strcpy(point->key, key);
	point->next = NULL;

	if ((hash->hash)[code].next == NULL) {
		(hash->hash)[code].quantity++;
		(hash->hash)[code].next = point;
		point->id = hash->countId;
		return (hash->countId)++;
	}
	for (Pi = (hash->hash)[code].next; Pi; Pi = Pi->next) {
		if (!strcmp(Pi->key, key)) {
			return (Pi->id)*(-1);//if exist return -id
		}
	}
	Pi = point;
	(hash->hash)[code].quantity++;
	point->id = hash->countId;
	return (hash->countId)++;
}
PointPointer hashSearch(const HashPointer hash, int(*h)(char*, int), const char* key) {
	int code = (*h)(key, hash->size);
	PointPointer Pi;
	printf(":%d:", code);//not
	if (!((hash->hash)[code].quantity))return NULL;
	for (Pi = (hash->hash)[code].next; Pi; Pi = Pi->next) {
		if (!strcmp(Pi->key, key)) {
			return Pi;
		}
	}
	return NULL;
}

int saveHash(const char* filename, const HashPointer hashT) {
	return 1;
}
HashPointer loadHash(const char* filename, int size) {
	return NULL;
}