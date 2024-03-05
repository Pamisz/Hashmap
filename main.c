#include "function.h"

int main() {
	int data[] = { 1,2,3,13,14,15,25,26,27 };

	Bucket* b = initialize_bucket();
	Hash* h = initialize_hash();

	insert_bucket(h, &data[0]);
	insert_bucket(h, &data[1]);
	insert_bucket(h, &data[2]);
	insert_bucket(h, &data[3]);
	insert_bucket(h, &data[4]);
	insert_bucket(h, &data[5]);
	insert_bucket(h, &data[6]);
	insert_bucket(h, &data[7]);
	insert_bucket(h, &data[8]);
	
	h->hash_view(h, print_data);	


	//usuwanie
	delete_node(h, &data[3]);		//poprawne usuniecie danej

	int noBucket = 4;				//hashcode = 4
	delete_node(h, &noBucket);		//usuniêcie danej, która do której nie ma hashcode

	int noNode = 37;				//hashcode = 1
	delete_node(h, &noNode);		//usuniêcie nieistniej¹cej danej, która ma istniej¹cy hashcode


	h->hash_view(h, print_data);

	delete_bucket(h, 2);			//usuniêcie hashcodu ==2
	delete_bucket(h, 5);			//usuniêcie nieistniej¹cego hashcodu (5)

	h->hash_view(h, print_data);

	isData(h, &data[0]);			//wyszukanie istniej¹cej danej
	isData(h, &data[3]);			//wyszukanie nieistniej¹cej danej


	//zwolnienie pamiêci
	delete_hash(h);
	return 0;
}