/*
 * HashMap.cpp
 *
 *  Created on: May 4, 2020
 *      Author: 13027
 */


#include "hashMap.hpp"
#include "hashNode.hpp"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <math.h>
using namespace std;

hashMap::hashMap(bool hash1, bool coll1) {
	map = NULL;
	first = "";
	mapSize = 101;
	numKeys = 0;
	hashfn = hash1;
	collfn = coll1;
	collisions = 0;
	hashcoll = 0;

	map = new hashNode*[mapSize];

	for(int i = 0; i < mapSize; i++){
		map[i] = NULL;
	}
}

void hashMap::addKeyValue(string k, string v){

	int index = getIndex(k);

	if(map[index] == NULL){
		map[index] = new hashNode(k, v);
		numKeys++;
	}

	else if(map[index]->keyword == k)
		map[index]->addValue(v);

	float loadFactor = 0;

	loadFactor = ((float)numKeys) / ((float)mapSize);

	if(loadFactor > 0.70)
		reHash();
}

int hashMap::getIndex(string k) {

	int index;

	if(hashfn)
		index = calcHash1(k);
	else
		index = calcHash2(k);

	if(map[index] == NULL)
		return index;

	else if(map[index] != NULL && map[index]->keyword == k)
		return index;

	else{
		if(collfn){
			hashcoll++;
			index = coll1(hashcoll, index, k);
			return index;
		}
		else{
			hashcoll++;
			index = coll2(hashcoll, index, k);
			return index;
		}
	}
}


int hashMap::calcHash2(string k){
	int base = 1;
	int product = 1;
	int len = k.length();

	for (int i = 0; i < len; i++){
		base = (int)(k[i]);
		product = product * base * i;
	}

	return  product % mapSize;
}

int hashMap::calcHash1(string k){
	int sum = 0;
	int len = k.length();

	for (int i = 0; i < len; i++)
		sum = sum + int(k[i]);

	return  sum % mapSize;
}

bool hashMap::isPrime(int n){
	// Corner cases
	if (n <= 1)  return false;
	if (n <= 3)  return true;

	// This is checked so that we can skip
	// middle five numbers in below loop
	if (n%2 == 0 || n%3 == 0)
		return false;

	for (int i=5; i*i<=n; i=i+6)
		if (n%i == 0 || n%(i+2) == 0)
			return false;

	return true;
}

void hashMap::getClosestPrime() {
	int N = 2 * mapSize;
	int prime;

	// Base case
	if (N <= 1)
		prime = 2;

	else{
		prime = N;
		bool found = false;

		// Loop continuously until isPrime returns
		// true for a number greater than n
		while (!found) {
			prime++;

			if (isPrime(prime))
				found = true;
		}
	}

	mapSize = prime;
}
void hashMap::reHash() {

	int index;
	int oldMapSize = mapSize;
	getClosestPrime(); // find the closest prime number to (2 * mapSize)

	hashNode** oldMap = map;
	map = new hashNode*[mapSize]; // Created a new map with new mapSize

	for(int i = 0; i < mapSize; i++)
		map[i] = NULL; // assigned values of new array to NULL

	for(int i = 0; i < oldMapSize; i++){
		if(oldMap[i] != NULL){
			index = getIndex(oldMap[i]->keyword);
			map[index] = oldMap[i];
		}
	}

	delete []oldMap; // deleted the original array of pointers to hashNodes
}

int hashMap::coll1(int h, int index, string k) {
	// Linear Probing

	int i = 1;

	while (map[(index + i) % mapSize] != NULL && map[(index + i) % mapSize]->keyword != k){
		collisions++;
		i++;
	}

	return (index + i) % mapSize;
}


int hashMap::coll2(int h, int index, string k){
	//Double Hashing
	int firstsum = 0, secondsum = 0;

	firstsum = calcHash1(k);
	secondsum = calcHash2(k);
	index = (firstsum + secondsum) % mapSize;


	while (map[index] != NULL && map[index]->keyword != k){
		collisions++;
		index = (index + 1) % mapSize;
	}
	return index % mapSize;


}


int hashMap::findKey(string k) {
	//NOTE: THIS METHOD CANNOT LOOP from index 0 to end of hash array looking for the key.
	//That destroys any efficiency in run-time.
	int index = getIndex(k);

	if(map[index] == NULL || map[index]->keyword != k){
		return -1;
	}

	else
		return index;
}


void hashMap::printMap() {
	cout << "In printMap()" << endl;
	for (int i = 0; i < mapSize; i++) {
		//cout << "In loop" << endl;
		if (map[i] != NULL) {
			cout << map[i]->keyword << ": ";
			for (int j = 0; j < map[i]->currSize;j++) {
				cout << map[i]->values[j] << ", ";
			}
			cout << endl;
		}
	}
}


