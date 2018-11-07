/*
 * test.cpp
 *
 *  Created on: Nov 27, 2017
 *      Author: lavy
 */

#include <iostream>
#include "splayTree.h"
using std::ostream;

class func{
private:
	int factor;
public:
	func(int factor):factor(factor){}
	~func(){}
	int operator()(int param){
		return param+factor;
	}
};

class indi{
private:
	int factor;
public:
	indi(int factor):factor(factor){}
	~indi(){}
	int operator()(int param){
		return !(param%factor);
	}
};

class updVal{
private:
	int indi,factor;
public:
	updVal(int indi,int factor):indi(indi),factor(factor){}
	~updVal(){}
	int operator()(int indicator,int value){
		if( !(indicator%indi) ){
			value = value+factor;
		}
		return value;
	}
};
class fnc{
public:
	~fnc(){}
	int operator()(int param){
		return param;
	}
};


int main(){
	SplayTree<int,int> splay;

//		splay.Insert(4,4);
//		splay.Insert(3,4);
//		splay.Insert(10,4);
//		splay.Insert(11,4);
//		splay.Insert(6,4);

//
//		splay.UpdateValue<func>(a,16);

//		splay.Delete(16);
//		splay.Insert(12,4);
//		splay.Find(3);
//		splay.Insert(2,4);
//		splay.Insert(5,4);
//		splay.Find(5);


	for (int i=0; i<5; i++ ){
		try{
					splay.Insert(3*i,i);
					}catch(...){}

		}

	splay.Insert(11,11);

	for (int i=5; i>0; i-- ){
		try{
					splay.Insert(11*i,i);
					}catch(...){}

		}

	for (int i=5; i>0; i-- ){try{
		splay.Insert(7*i,i);
		}catch(...){}

		}


	splay.Delete(21);


	for (int i=0; i<2000; i++ ){
		try{
			splay.Insert(i,i);
		}catch(...){}
		}


		for (int i=0; i<4000; i++ ){
			try{
				splay.Find(i);
			}catch(...){

			}
		}

	func a(2000);
	indi b(2);
	splay.UpdateTreeKeys(a,b);

			int* c = NULL;
			fnc d;
			splay.GetAllKeys<fnc,int>(d,c);

			for (int i=0; i<2000; i++ ){
				try{
					splay.Find(c[i]);
				}catch(...){

				}
			}
			free(c);


		for(int i = 0; i< 4000; i++)
			try{
				splay.Delete(i);
			}catch(...){

			}

		for (int i=0; i<2000; i++ ){
			try{
			splay.Insert(2*i,i);
			}catch(...){}
		}

		for (int i=2000; i>0; i-- ){
			try{
				splay.Insert(7*i,i);
				}catch(...){}
		}

		for (int i=0; i<2000; i++ )	{	try{
			splay.Insert(3*i,i);
			}catch(...){}
		}

		for (int i=2000; i>0; i-- ){
			try{
			splay.Insert(5*i,i);
			}catch(...){}
		}

		for (int i=0; i<2000; i++ ){		try{
			splay.Insert(11*i,i);
			}catch(...){}
		}




		for (int i=0; i<2000; i++ ){		try{
			splay.Insert(13*i,i);
			}catch(...){}
		}

		for (int i=6000; i<12000; i++ ){
			try{
			splay.Delete(i);
			}catch(...){}
		}

		for (int i=20000; i>15000; i-- ){
			try{
			splay.Delete(i);
			}catch(...){}
		}

		for (int i=26000; i>0; i-- ){
			try{
			splay.Delete(i);
			}catch(...){}

		}

		std::cout << "work2" << std::endl;

	return 0;
}


