/*
 * MakeSeuss.cpp
 *
 *  Created on: May 4, 2020
 *      Author: 13027
 */

#include "makeSeuss.hpp"
#include "hashMap.hpp"

#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>

using namespace std;

makeSeuss::makeSeuss(string f1,string f2,bool hash1, bool coll1) {
	ht = new hashMap(hash1,coll1);
	newfile = f2;
	fn = f1;

	readFile();
	writeFile();
}
void makeSeuss::readFile(){
	ifstream infile(fn.c_str(),ios::in);     // open file
	string key = "";
	string value="";
	infile>> key;

	infile >> key;
	ht->first = key;

	while (infile >> value) {          // loop getting single characters
		//cout << key <<": " << value << endl;
		ht->addKeyValue(key,value);
		key = value;
		value = "";
	}
	ht->addKeyValue(key,value);
	cout << endl;
	infile.close();

	ht->printMap();

	cout<<"****************************************************"<<endl;
	cout<<"****************************************************"<<endl;
	cout<<"****************************************************"<<endl;
	cout<<"****************************************************"<<endl;
	cout<<"****************************************************"<<endl;
}

void makeSeuss::writeFile() {
	cout<<"Entering writefile()"<<endl;
	ofstream outfile(newfile.c_str(),ios::out);
	cout<<newfile<<endl;

	float hashfloat = (float)ht->hashcoll/(float)ht->numKeys;
	float collfloat =  (float)ht->collisions/(float)ht->numKeys;
	if (ht->hashfn && ht->collfn) {
		cout<<"Enter 1"<<endl;
		outfile << "Collisions using hash 1: "<< hashfloat << ", and collision handling 1: " << collfloat <<endl;
	}
	else if (ht->hashfn) {
		cout<<"Enter 2"<<endl;
		outfile << "Collisions using hash 1: "<< hashfloat << ", and collision handling 2: " << collfloat<<endl;
	}
	else if (ht->collfn) {
		cout<<"Enter 3"<<endl;
		outfile << "Collisions using hash 2: "<< hashfloat << ", and collision handling 1: " << collfloat<<endl;
	}
	else {
		cout<<"Enter 4"<<endl;
		outfile << "Collisions using hash 2: "<< hashfloat << ", and collision handling 2: " << collfloat<<endl;
	}
	//cout<<"Ifs completed"<<endl;
	outfile<<endl;
	outfile << ht->first << " ";
	//cout<<"ht->first is "<<ht->first<<endl;
	string key = "";
	string value = ht->map[ht->getIndex(ht->first)]->getRandValue();
	//cout<<value<<endl;
	int ct = 0;
	int len = 0;
	//cout<<"Entedhmbn"<<endl;
	while (ct < 500 &&  value != "") {
		key = value;
		outfile << key << " ";
		if (len == 11) {
			outfile << "\n";
			len = 0;
		}
		else len++;
		value = ht->map[ht->getIndex(key)]->getRandValue();
		//cout<<value<<endl;
		ct ++;
	}
	cout<<"Closing file"<<endl;
	outfile.close();
}

