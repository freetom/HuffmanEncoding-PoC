/*
	This file define the huffman tree, and nodes, used to create the encoding to compress the data;
*/

#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include <algorithm>

using namespace std;

//Class Node, for internals and leaves nodes
class Node{
	public:
		Node *l,*r,*p;
		unsigned char *data;
		unsigned int v;

		Node(unsigned int v){
			l=r=p=NULL;
			data=NULL;
			this->v=v;
		}
};

class HuffmanTree{
	
	private:
		//root of the tree
		Node* root;

		
		void printEncodingHelp(Node* n, int level, char* str){
			#ifdef DEBUG
			if(n->l==NULL && n->r==NULL){
				str[level]='\x00';
				printf("%s->%c = %d value\n",str,*(n->data),(unsigned int)*(n->data) );
				bits_needed[*(n->data)]=level;
			}
			else{
				if(n->l!=NULL){
					str[level]='0';
					printEncodingHelp(n->l,level+1,str);
				}
				if(n->r!=NULL){
					str[level]='1';
					printEncodingHelp(n->r,level+1,str);
				}
			}
			#endif
		}

		int depthHelp(Node* n, int max_val){
			int l=max_val,r=max_val;
			if(n->l!=NULL) l=depthHelp(n->l,max_val+1);
			if(n->r!=NULL) r=depthHelp(n->r,max_val+1);

			return max(l,r);
		}

		void inOrderVisitHelp(Node* n){
			#ifdef DEBUG
			if(n==NULL) return;

			inOrderVisitHelp(n->l);
			printf("%d\n",n->v );
			inOrderVisitHelp(n->r);
			#endif
		}

	public:
		//Array that contains for each symbol how many bits are needed to encode it 
		int bits_needed[256];

		//Constructor
		HuffmanTree(){
			root=NULL;

			for(int i=0;i<256;i++){
				bits_needed[i]=0;
			}

		}

		//Constructor overload
		HuffmanTree(Node* root){
			this->root=root;
		}

		//Function that print for each symbol its encoding
		void printEncoding(){
			char* str=new char[depth()+1];
			printEncodingHelp(root,0,str);
			delete str;
		}

		//Calculate the depth of the tree
		int depth(){
			return depthHelp(root,0);
		}

		//Make an in order visit
		void inOrderVisit(){
			inOrderVisitHelp(root);
		}
};

#endif
