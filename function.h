#pragma once
#include <stdlib.h>
#include <stdio.h>

typedef struct Node Node;
struct Node {
	Node* next;
	Node* prev;
	void* data;
};

typedef struct Bucket Bucket;
struct Bucket {
	Node* first;
	Bucket* next;
	Bucket* prev;
	int hashcode;
};

typedef struct Hash Hash;
struct Hash {
	Bucket* first;
	Bucket* last;
	int (*hashing)(const void*);
	void (*hash_view)(const void*);
};

Node* initialize_node();

Bucket* initialize_bucket();

Hash* initialize_hash();
void delete_hash(Hash* h);

void print_data(void* data);
int hashing(void* data);
void hash_view(Hash* h, void(*print_data)(void*));

void insert_node(Bucket* b, void* data);
void insert_bucket(Hash* h, void* data);
void delete_node(Hash* h,void* data);
void delete_bucket(Hash* h, int hashcode);
void isData(Hash* h, void* data);

void delete_nodes(Bucket* b);
void delete_buckets(Hash* h);
void delete_hash(Hash* h);