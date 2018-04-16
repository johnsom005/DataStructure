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

	//freopen("test.txt", "w", stdout);

	srand(time(NULL));
	HashPointer hash;
	PointPointer p;
	int i, len, j, max, q, total;
	int count = 0;
	char temp[8];
	hash = loadHash("test.dat");//
	//hash = hashInit(20);
	/*for (i = 0; i < 15; i++) {
		len = rand() % 6 + 2;
		for (j = 0; j < len; j++) {
			temp[j] = (int)'a' + rand() % 26;
		}
		temp[j] = '\0';
		printf("%s\\", temp);
		if (hashInsert(hash, hashf, temp) > 0)count++;
	}*/
	max = total = 0;
	for (i = 0; i < 20; i++) {
		q = (hash->hash)[i].quantity;
		//printf("%d\n", q);
		total += q;
		if(q)printf("%d\\%d\n", i, total);
		if (q > max) {
			max = q;
		}
	}
	printf("MAX:%d count:%d Total:%d\n", max, hash->countId,total);
	//saveHash("test.dat", hash);
	while (1) {
		scanf("%s", temp);
		p = hashSearch(hash, hashf, temp);
		if (p == NULL) {
			printf("Not found\n");
			continue;
		}
		printf("id:%d key:%s\n", p->id, p->key);
	}

	system("pause");
	return 0;
}