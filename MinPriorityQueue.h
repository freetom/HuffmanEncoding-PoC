
#ifndef MIN_PRIORITY_QUEUE_H
#define MIN_PRIORITY_QUEUE_H

#include "HuffmanTree.h"

class QueueNode{
	public:
		Node *n;
		QueueNode *next;

		QueueNode(){
			n=NULL;
			next=NULL;
		}
};

class MinPriorityQueue{
	private:
		QueueNode *head,*tail;
	public:
		MinPriorityQueue(){
			head=NULL;
			tail=NULL;
		}

		void addElem(Node* n){
			if(!head){
				head=tail=new QueueNode();
				head->n=tail->n=n;
			}
			else if(head==tail){
				if(n->v<head->n->v){
					QueueNode* tmp=head;
					head=new QueueNode(); head->n=n;
					tail=tmp;
					head->next=tail;
				}
				else{
					tail=new QueueNode();
					tail->n=n;
					head->next=tail;
				}
			}
			else{
				if(head->n->v>=n->v){
					QueueNode *newNode=new QueueNode();
					newNode->n=n; newNode->next= head;
					head=newNode;
				}
				else{

					QueueNode *curr=head,*prec=head;
					while(curr!=NULL){
						if(curr->n->v>=n->v){
							QueueNode *newNode=new QueueNode();
							newNode->n=n; newNode->next= curr;
							if(prec!=NULL) prec->next=newNode;
							
							break;
						}
						prec=curr;
						curr=curr->next;
					}
					if(!curr){
						QueueNode *newNode=new QueueNode();
						newNode->n=n;
						prec->next=newNode;

						tail=newNode;
					}
				}
			}
		}

		bool lastOne(){
			return head==tail;
		}

		Node* removeElem(){
			Node* ret;

			if(head==NULL)
				ret=NULL;
			else if(head==tail){
				ret= head->n;
				delete head;
				head=tail=NULL;
			}
			else{
				ret=head->n;
				QueueNode *tmp=head->next;
				delete head;
				head=tmp;
			}

			return ret;
		}

		void printQueue(){
			#ifdef DEBUG
			QueueNode* curr=head;
			while(curr!=NULL){
				printf("%d\n",curr->n->v);

				curr=curr->next;
			}
			#endif
		}
};

#endif

