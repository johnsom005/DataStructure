#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

int countId;

BeginPointer hashInit(int size) {
	BeginPointer hash= (BeginPointer)malloc(sizeof(Begin)*size);
	int i;
	countId = 1;
	for (i = 0; i < size; i++) {
		hash[i].quantity = 0;
		hash[i].next = NULL;
	}
	return hash;
}
int hashInsert(const BeginPointer hash, int size, int (*h)(char*, int), const char* key) {

	int code = (*h)(key, size);
	PointPointer point = (PointPointer)malloc(sizeof(Point));
	PointPointer Pi;
	strcpy(point->key, key);
	point->next = NULL;

	if (hash[code].next == NULL) {
		hash[code].quantity++;
		hash[code].next = point;
		point->id = countId;
		return countId++;
	}
	for (Pi = hash[code].next; Pi; Pi = Pi->next) {
		if (!strcmp(Pi->key, key)) {
			return (Pi->id)*(-1);//if exist return -id
		}
	}
	Pi = point;
	hash[code].quantity++;
	point->id = countId;
	return countId++;
}
PointPointer hashSearch(const BeginPointer hash, int size, int(*h)(char*, int), const char* key) {
	int code = (*h)(key, size);
	PointPointer Pi;
	printf(":%d:", code);
	if (!(hash[code].quantity))return NULL;
	for (Pi = hash[code].next; Pi; Pi = Pi->next) {
		if (!strcmp(Pi->key, key)) {
			return Pi;
		}
	}
	return NULL;
}

int saveHash(const char* filename, const BeginPointer hashT) {
	return 1;
}
BeginPointer loadHash(const char* filename, int size) {
	return NULL;
}