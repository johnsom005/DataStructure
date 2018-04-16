
#ifndef HASH_H
#define HASH_H

#define MAXLEN 16

typedef struct p *PointPointer;
typedef struct p {
	char key[MAXLEN];
	int id;
	PointPointer next;
}Point;

typedef struct n *BeginPointer;
typedef struct n {
	int quantity;
	PointPointer next;
}Begin;

extern int countId;

BeginPointer hashInit(int size);
int hashInsert(const BeginPointer hash, int size, int(*h)(char*, int), const char* key);
PointPointer hashSearch(const BeginPointer hash, int size, int(*h)(char*, int), const char* key);

int saveHash(const char* filename, const BeginPointer hashT);
BeginPointer loadHash(const char* filename, int size);


#endif
