/*
	This program implements the huffman encoding for lossless compression
	It just print statistics on the effect that the compression have on the file provided as parameter.
	To effectively encode the file, not many modifications are needed.
	Usage: ./a.out fileToCompress
*/

#include <iostream>
#include <fstream>

#include "HuffmanEncoding.h"

#define ARG_ERR -1
#define FILE_ERR -2
#define ALLOC_ERR -3

using namespace std;

int main(int argc, char* argv[]){
	
	//If there is no argument, terminate.
	if(argc!=2){
		printf("Usage: %s fileToCompress\n",argv[0]);
		return ARG_ERR;
	}

	//Open file
	FILE* f=fopen(argv[1],"r"); 
	if(!f){
		printf("Error opening the file \"%s\"\n",argv[1]);
		return FILE_ERR;
	}

	//Find file length
	fseek( f, 0, SEEK_END ) ; 
	int length = ftell( f ) ; 
	rewind ( f ) ; 

	//alloc memory for data
	unsigned char* data = new (nothrow) unsigned char[length]; 
	if(  !data )
		return ( ALLOC_ERR ) ; 
	
	//Read the file and store the data in an array
	int i = 0 ; 
	while( i < length )
		data[ i++ ] = getc( f );
	fclose(f);	//close the file


	HuffmanEncoding* he=new HuffmanEncoding();
	he->countFrequencies(data, length);
	delete data;
	he->createEncoding();
	
}

