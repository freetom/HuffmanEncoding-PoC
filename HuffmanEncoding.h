/*
	Class that provide huffman encoding precise estimation of compression of data.
	Without considering the additional overload added by meta-compression-info.
	the encoding schema is based on the frequencies of the symbols of the alphabet.
	This method is lossless compression.

	The steps are:
		-Count frequencies of symbols
		-Build a tree based on frequencies that define the new encoding for each symbol
	Then optionally:
		-print stats on compression
		-save the compressed file (not implemented but pretty trivial)

	Bortoli Tomas in 2013
*/

#ifndef HUFFMAN_ENCODING_H
#define HUFFMAN_ENCODING_H

#define DEBUG

#include <iostream>
using namespace std;

#include "HuffmanTree.h"
#include "MinPriorityQueue.h"

#define BITS_IN_A_BYTE 8

class HuffmanEncoding{
	private:
		unsigned int frequencies[256];
		HuffmanTree *t;
	public:

		HuffmanEncoding(){
			t=NULL;
			for(int i=0;i<256;i++)
				frequencies[i]=0;
		}
		
		void countFrequencies(unsigned char* data, int len){
			for(int i=0;i<len;i++){
				frequencies[data[i]]++;
			}

			#ifdef DEBUG
			printf("Frequencies:\n");
			for(int i=0;i<256;i++){
				if(frequencies[i]!=0){
					printf("%c:%d\n",(unsigned char)i,frequencies[i] );
				}
			}
			printf("\n\n");
			#endif

		}

		void createEncoding(){

			//Count how many symbols are present, and alloc the necessary space.
			int len=0;
			for(int i=0;i<256;i++){
				if(frequencies[i]!=0)
					len++;
			}

			Node** leafs=new Node*[len];

			//Initialize the min priority queue
			MinPriorityQueue *q=new MinPriorityQueue();

			//Initialize the leaf nodes and inserts it in the queue
			int j=0;
			for(int i=0;i<256;i++){
				if(frequencies[i]!=0){
					leafs[j]=new Node(frequencies[i]);
					leafs[j]->data=new unsigned char;
					*(leafs[j]->data)=i;

					q->addElem(leafs[j]);

					//printf("%c\n",*(leafs[j]->data) );
					j++;
				}
			}
			
			//q->printQueue();

			//Create the tree, extracting the 2 min priority nodes and sum their values to create a new node, put this node into the queue
			//Repeat this until the queue will be empty
			Node *val1,*val2;
			while(!q->lastOne()){

				//DEBUG
				//q->printQueue(); cin.ignore();

				val1=q->removeElem();
				val2=q->removeElem();

				Node* newNode= new Node(val1->v+val2->v);
				val1->p=val2->p=newNode;
				newNode->r=val1; newNode->l=val2;

				q->addElem(newNode);	
			}

			t=new HuffmanTree(q->removeElem());
			
			#ifdef DEBUG
			printf("Encoding:\n");
			t->printEncoding();
			#endif

			delete q;

			//Compute and print gain from the initial size, to the final size.
			computeGain();
		}

		void computeGain(){
			if(t==NULL) return;

			long int initialSize=0;
			long int finalSize=0;
			for(int i=0;i<256;i++)
				initialSize+=frequencies[i]*BITS_IN_A_BYTE;
			for(int i=0;i<256;i++)
				finalSize+=frequencies[i]*t->bits_needed[i];

			#ifdef DEBUG
			printf("\n\n");
			printf("Outcome of huffman compression:\n");
			printf("\tInitial weight of file: %d bytes\n",initialSize/BITS_IN_A_BYTE );
			printf("\tWeight after Huffman Compression: %d bytes\n",finalSize/BITS_IN_A_BYTE );
			printf("\tThe final file scale %f%% respect to the initial file; without calculating compression meta-info weight\n",((float)finalSize)/((float)initialSize)*100.0f );
			printf("\n\n");
			#endif
		}
};

#endif

