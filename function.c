#include <stdbool.h>
#include "function.h"

Node* initialize_node() {
	Node* newNode = (Node*)malloc(sizeof(Node));

	if (newNode != NULL) {
		newNode->next = NULL;
		newNode->prev = NULL;
		newNode->data = NULL;
	}

	return newNode;
}

Bucket* initialize_bucket() {
	Bucket* newBucket = (Bucket*)malloc(sizeof(Bucket));

	if (newBucket != NULL) {
		newBucket->first = NULL;
		newBucket->next = NULL;
		newBucket->prev = NULL;
		newBucket->hashcode = 0;
	}

	return newBucket;
}

int hashing(void* data) {
	int* tmp = (int*)data;
	int code = *tmp % 12;
	return code;
}
void print_data(void* data) {
	int* buff = (int*)data;
	printf("%d", *buff);
}
void hash_view(Hash* h, void(*print_data)(void*)) {
	if (h != NULL && h->first != NULL) {
		printf("\n\nPrinting hashmap:");
		for (Bucket* b_tmp = h->first; b_tmp != NULL; b_tmp = b_tmp->next) {
			printf("\nHashcode:%d", b_tmp->hashcode);
			for (Node* n_tmp = b_tmp->first; n_tmp != NULL; n_tmp = n_tmp->next) {
				printf("\nNode data:");
				print_data(n_tmp->data);
			}
			printf("\n");
		}
	}
	else {
		printf("Hashmap is empty! You cannot print it!");
	}
}

Hash* initialize_hash() {
	Hash* newHash = (Hash*)malloc(sizeof(Hash));

	if (newHash != NULL) {
		newHash->first = NULL;
		newHash->last = NULL;
		newHash->hashing = hashing;
		newHash->hash_view = hash_view;
	}
	return newHash;
}

void insert_node(Bucket* b, void* data) {
	Node* n = initialize_node();
	n->data = data;
	printf("\nNew node:");
	print_data(data);
	printf(" has been added to hashcode:%d", b->hashcode);
	printf("\n");
	if (b->first == NULL) {
		b->first = n;
	}
	else {
		n->next = b->first;
		b->first->prev = n;
		b->first = n;
	}
}
void insert_bucket(Hash* h, void* data) {
	int hashcode = h->hashing(data);
	Bucket* b = initialize_bucket();
	bool isBucket = false;
	if (h->first == NULL) {											//utworzenie pierwszego bucketa
		h->first = b;
		h->last = b;
		b->hashcode = hashcode;
		insert_node(b, data);
	}
	else {
		for (Bucket* tmp = h->first; tmp != NULL; tmp = tmp->next) {
			if (tmp->hashcode == hashcode) {						//wstawienie node do istniejacego bucketa
				isBucket = true;
				insert_node(tmp, data);
				free(b);
				break;
			}
		}
		if (!isBucket) {
			b->hashcode = hashcode;
			for (Bucket* tmp = h->first; tmp != NULL; tmp = tmp->next) {
				if (tmp->hashcode > b->hashcode) {						//utworzenie bucketa pomiedzy innymi rosnąco
					b->prev = tmp->prev;
					if (tmp->prev != NULL)
						tmp->prev->next = b;
					b->next = tmp;
					tmp->prev = b;
					break;
				}
				else if (tmp == h->last && tmp->hashcode < b->hashcode){	//ustawienie bucketa na samym koncu
					tmp->next = b;
					b->prev = tmp;
					h->last = b;
					break;
				}
			}
			insert_node(b, data);
		}
	}
}
void delete_node(Hash* h, void* data) {
	int hashcode = hashing(data);
	Bucket* source = NULL;
	Node* toDel = NULL;
	if (h != NULL && h->first != NULL) {
		for (Bucket* tmp = h->first; tmp != NULL; tmp = tmp->next) {
			if (tmp->hashcode == hashcode) {
				source = tmp;
			}
		}
		if (source != NULL) {
			for (Node* n = source->first; n != NULL; n = n->next) {
				if (n->data == data) {
					toDel = n;
				}
			}
			if (toDel != NULL) {
				if (toDel->next != NULL)
				toDel->next->prev = toDel->prev;
				if (toDel->prev != NULL)
				toDel->prev->next = toDel->next;
				toDel->data = NULL;
				toDel->next = NULL;
				toDel->prev = NULL;
				free(toDel);
				printf("\n");
				print_data(data);
				printf(" has been deleted from hashcode %d", source->hashcode);
			}
			else {
				printf("\nNo such data to delete!");
			}

		}
		else {
			printf("\nThere's no matching hashcode!");
		}
	}
	else {
		printf("\nHashmap is empty!");
	}
	printf("\n");
}
void delete_bucket(Hash* h, int hashcode) {
	if (h != NULL && h->first != NULL) {
		Bucket* bToDel = NULL;
		for (Bucket* tmp = h->first; tmp != NULL; tmp = tmp->next) {
			if (tmp->hashcode == hashcode) {
				bToDel = tmp;
			}
		}
		if (bToDel != NULL) {
			delete_nodes(bToDel);			//usunięcie nodów z bucketa
			bToDel->first = NULL;
			bToDel->hashcode = NULL;
			if(bToDel->next != NULL)
			bToDel->next->prev = bToDel->prev;
			if (bToDel->prev != NULL)
			bToDel->prev->next = bToDel->next;
			free(bToDel);
			printf("\nHashcode:%d", hashcode);
			printf(" has been deleted!");
		}
		else {
			printf("\nThere's no such hashcode in hashmap!");
		}
	}
	else {
		printf("\nHashmap is empty!");
	}
	printf("\n");
}
void isData(Hash* h, void* data) {
	printf("\n");
	if (h != NULL && h->first != NULL) {
		int hashcode = h->hashing(data);
		Bucket* source = NULL;
		Node* element = NULL;
		for (Bucket* tmp = h->first; tmp != NULL; tmp = tmp->next) {
			if (tmp->hashcode == hashcode) {
				source = tmp;
			}
		}
		if (source != NULL) {
			for (Node* buff = source->first; buff != NULL; buff = buff->next) {
				if (buff->data == data) {
					element = buff;
				}
			}
			if (element != NULL) {
				print_data(data);
				printf(" exists in hashcode:%d.", source->hashcode);
			}
			else {
				printf("No such data in hashmap!");
			}
		}
		else {
			printf("There's no such hashcode in hashmap!");
		}
	}
	else {
		printf("Hashmap is empty!");
	}
	printf("\n");
}

void delete_nodes(Bucket* b) {
	Node* n_del = b->first;
	if (n_del != NULL) {
		for (n_del; n_del != NULL; n_del = b->first) {
			b->first = n_del->next;
			n_del->data = NULL;
			n_del->next = NULL;
			n_del->prev = NULL;
			free(n_del);
		}
	}
}
void delete_buckets(Hash* h) {
	Bucket* b_del = h->first;
	if (b_del != NULL) {
		for (b_del; b_del != NULL; b_del = h->first) {
			h->first = b_del->next;
			delete_nodes(b_del);
			b_del->first = NULL;
			b_del->next = NULL;
			b_del->prev = NULL;
			b_del->hashcode = NULL;
			free(b_del);
		}
	}
}
void delete_hash(Hash* h) {
	if (h != NULL) {
		delete_buckets(h);
		free(h);
	}
	printf("\nHashmap has been deleted.");
}
