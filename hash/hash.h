
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

typedef struct h *HashPointer;
typedef struct h {
	int countId;
	BeginPointer hash;
	int size;
}Hash;

//extern int countId;

HashPointer hashInit(int size);
int hashInsert(const HashPointer hash, int(*h)(char*, int), const char* key);
PointPointer hashSearch(const HashPointer hash, int(*h)(char*, int), const char* key);

int saveHash(const char* filename, const HashPointer hashT);
HashPointer loadHash(const char* filename);


#endif
