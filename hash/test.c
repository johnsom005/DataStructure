#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hash.h"

#define PRIME 97

int hashf(char *key, int size) {
	int i, f = 0;
	for (i = 0; i < strlen(key); i++) {
		f = (f*PRIME + (int)key[i]) % size;
	}
	return f;
}

int main(void) {

	srand(time(NULL));
	BeginPointer hash;
	PointPointer p;
	int i, len, j, max;
	char temp[8];
	hash = hashInit(500);
	
	for (i = 0; i < 350; i++) {
		len = rand() % 6 + 2;
		for (j = 0; j < len; j++) {
			temp[j] = (int)'a' + rand() % 26;
		}
		temp[j] = '\0';
		printf("%s\\", temp);
		hashInsert(hash, 500, hashf, temp);
	}
	max = 0;
	for (i = 0; i < 500; i++) {
		printf("%d\n", hash[i].quantity);
		if (hash[i].quantity > max) {
			max = hash[i].quantity;
		}
	}
	printf("MAX:%d\n", max);
	while (1) {
		scanf("%s", temp);
		p = hashSearch(hash, 500, hashf, temp);
		if (p == NULL) {
			printf("Not found\n");
			continue;
		}
		printf("id:%d key:%s\n", p->id, p->key);
	}

	system("pause");
	return 0;
}