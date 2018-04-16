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
		//printf("hash:%d,id:%d,key:%s\n", code, hash->countId, key);
		point->id = hash->countId;
		return (hash->countId)++;
	}
	for (Pi = (hash->hash)[code].next; Pi; Pi = Pi->next) {
		if (!strcmp(Pi->key, key)) {
			free(point);
			//printf("\n!!!exist!!!\n");
			return (Pi->id)*(-1);//if exist return -id
		}
	}
	point->next = (hash->hash)[code].next;
	(hash->hash)[code].next = point;
	//printf("hash:%d,id:%d,key:%s\n", code, hash->countId, key);
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

int saveHash(const char* filename, const HashPointer hash) {
	FILE *fptr = fopen(filename, "wb");
	int size, result, i;
	int count = 0;
	PointPointer Pi;
	if (!hash) {
		printf("hash table doesn't exist\n");
		return -1;
	}
	size = hash->size;
	if (fptr == NULL) {
		printf("file connot open\n");
		return -2;
	}
	result = fwrite(hash, sizeof(Hash), 1, fptr);
	if (result != 1) {
		printf("writing Hash is failed\n");
		return -3;
	}
	result = fwrite(hash->hash, sizeof(Begin), size, fptr);
	if (result != size) {
		printf("writing Hash table is failed\n");
		return -4;
	}

	for (i = 0; i < size; i++) {
		for (Pi = (hash->hash)[i].next; Pi; Pi = Pi->next) {
			
			result = fwrite(Pi, sizeof(Point), 1, fptr);
			//count++;
			//printf("%d:%d\n", i, count);
			if (result != 1) {
				printf("writing bucket is failed\n");
				return -5;
			}
		}
	}
	//printf("count:%d\n", count);
	
	fclose(fptr);
	return 1;
}
HashPointer loadHash(const char* filename) {

	FILE *fptr = fopen(filename, "rb");
	int result, count, i, f, c;
	HashPointer hashT = (HashPointer)malloc(sizeof(Hash));
	BeginPointer hash;
	PointPointer bucket;

	if (fptr == NULL) {
		printf("cannot open file\n");
		return NULL;
	}
	//read header structure
	result = fread(hashT, sizeof(Hash), 1, fptr);
	if (result != 1) {
		printf("reading Hash is failed\n");
		return NULL;
	}
	//read hash structure
	hash = (BeginPointer)malloc(sizeof(Begin)*(hashT->size));
	result = fread(hash, sizeof(Begin), (hashT->size), fptr);
	if (result != (hashT->size)) {
		printf("reading Hash table is failed\n");
		return NULL;
	}
	//connect header to hash 
	hashT->hash = hash;
	//read every node
	count = hashT->countId - 1;
	bucket = (PointPointer)malloc(sizeof(Point)*count);
	result = fread(bucket, sizeof(Point), count, fptr);
	if (result != count) {
		printf("reading bucket is failed\n");
		return NULL;
	}
	//link node to table
	c = 0;
	for (i = 0; i < hashT->size; i++) {
		hash[i].next = NULL;
		for (f = 0; f < hash[i].quantity; f++) {
			bucket[c].next = hash[i].next;
			hash[i].next = bucket + c;
			c++;
		}
	}
	printf("c:%d\n", c);//test


	return hashT;
}