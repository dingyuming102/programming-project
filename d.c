#include "stdio.h"
#include "stdlib.h"
#include "math.h"

// tree data structure

int maxLevel = 6;

int num_add;
int num_del;

struct qnode {
	int level;
	int flag;
	double xy[2];
	struct qnode *child[4];
};
typedef struct qnode Node;

// function definitions

Node *makeNode( double x, double y, int level );
void makeChildren( Node *parent );
void writeTree( Node *head );
void writeNode( FILE *fp, Node *node );
void printOut( FILE *fp, Node *node );
void destroyTree( Node *node );
void growTree( Node *node );
void removeChildren(Node * parent);
void setFlag(Node *node);
void addTree(Node *node);
void cutTree(Node *node);
void adapt(Node * head);
double nodeValue( Node *node, double time );
double value( double x, double y, double time );
int judge_leafnode(Node *node);
void adjust_tree(Node *node);


// main

int main( int argc, char **argv ) {

  	Node *head;

  	// make the head node
  	head = makeNode( 0.0,0.0, 0 );

  	// make a tree
  	//makeChildren( head );
  	//makeChildren( head->child[1] );

  	// print the tree for Gnuplot
	//writeTree( head );
	
	
	/*
    growTree(head);
    growTree(head);
    writeTree( head ); 
	destroyTree( head );//level 2 full---task 1-1*/    
    
    /*
    growTree(head);
    makeChildren(head->child[1]);
    writeTree( head );
    destroyTree(head);
    // print the tree for Gnuplot task1-2
    */
    
    growTree(head);
    growTree(head);
    removeChildren(head->child[1]);// task2-1
    writeTree( head );
    destroyTree(head);
	
    
    /*
    growTree(head);
    setFlag(head);
    makeChildren( head->child[1]);
    makeChildren( head->child[2]);
    removeChildren(head->child[1]);
    writeTree( head );
    destroyTree(head);//task2-2
	*/
     
    /*
    growTree(head);
    growTree(head);
    growTree(head);
    setFlag(head);
	addTree(head);
	cutTree(head);
  	printf("\nadded %i nodes\n",num_add);
  	printf("\nremoved %i nodes\n",num_del);
    writeTree( head );//task3-1
    destroyTree(head);
    */
     
    /*
    growTree(head);
    growTree(head);
    growTree(head);
    //setFlag(head);
	//adapt(head);
    writeTree(head);  //task3-2
    destroyTree(head);
    //*/


  	return 0;
}

// make a node at given location (x,y) and level

Node *makeNode( double x, double y, int level ) {

	int i;

  	Node *node = (Node *)malloc(sizeof(Node));

  	node->level = level;

  	node->xy[0] = x;
  	node->xy[1] = y;

  	for( i=0;i<4;++i )
    	node->child[i] = NULL;

  	return node;
}

// split a leaf nodes into 4 children

void makeChildren( Node *parent ) {

  	double x = parent->xy[0];
  	double y = parent->xy[1];

  	int level = parent->level;

  	double hChild = pow(2.0,-(level+1));

  	parent->child[0] = makeNode( x,y, level+1 );
  	parent->child[1] = makeNode( x+hChild,y, level+1 );
  	parent->child[2] = makeNode( x+hChild,y+hChild, level+1 );
  	parent->child[3] = makeNode( x,y+hChild, level+1 );
	
  	return;
}

// write out the tree to file 'quad.out'

void writeTree( Node *head ) {

  	FILE *fp = fopen("quad.out","w");

  	writeNode(fp,head);

  	fclose(fp);

  	return;
}

// recursively visit the leaf nodes

void writeNode( FILE *fp, Node *node ) {

  	int i;

  	if( node->child[0] == NULL )
    	printOut( fp, node );
  	else {
    	for ( i=0; i<4; ++i ) {
      		writeNode( fp, node->child[i] );
    	}
  	}
  	return;
}

// write out the (x,y) corners of the node

void printOut( FILE *fp, Node *node ) {
  	double x = node->xy[0];
  	double y = node->xy[1];
  	int level = node->level;
  	double h = pow(2.0,-level);

  	fprintf(fp, " %g %g\n",x,y);
  	fprintf(fp, " %g %g\n",x+h,y);
  	fprintf(fp, " %g %g\n",x+h,y+h);
  	fprintf(fp, " %g %g\n",x,y+h);
  	fprintf(fp, " %g %g\n\n",x,y);

  	return;
}

void destroyTree( Node *node ){
	int i;
	if( !node ){
		return;
	}else{
		for( i=0;i<4;++i ){
			destroyTree( node->child[i] );
		}
		free(node);
		return;
	}
	
}

void growTree( Node *node ){
	int i;

	if(node->child[0] != NULL){
		for( i=0;i<4;++i )
			growTree( node->child[i] );
	}else{
		makeChildren( node );
	}
		return;
}




void removeChildren(Node * parent){
	int i;
	for( i=0;i<4;++i ){
		if(parent->child[i]){
			removeChildren(parent->child[i]);
			free(parent->child[i]);
			parent->child[i] = NULL;
		}
	}

}



void addTree(Node *node){
	int i;
	if((judge_leafnode(node) && node->flag==1) && node->level<maxLevel){
		makeChildren(node);
		num_add += 4;
		return;
	}
	for(i=0;i<4;i++){
		if(node->child[i])
			addTree(node->child[i]);
	}
		
}

void cutTree(Node *node){
	int i;
	if(judge_leafnode(node) && node->child[0]->flag==-1 && node->child[1]->flag==-1 && node->child[2]->flag==-1 && node->child[3]->flag==-1){
		removeChildren(node);
		num_del += 4;
		return;
	}
	for(i=0;i<4;i++){
		if(node->child[i])
			cutTree(node->child[i]);
	}

}

int judge_leafnode(Node *node){
	int i;
	for(i=0;i<4;i++){
		if(node->child[i]){
			return 0;
		}
	}
	return 1;
}

void setFlag(Node *node){
	int i;
	if(!judge_leafnode(node)) 
		node->flag=0;
	else if(nodeValue(node,0.0)>0.5){
		node->flag=1;
	}
	else if(nodeValue(node,0.0)<-0.5){
		node->flag=-1;
	}
	else{
		node->flag=0;
	}
	for(i=0;i<4;i++){
		if(node->child[i]){
			setFlag(node->child[i]);
		}
	}
}
void adapt(Node *node){
	int tmp_add,tmp_del,count=1;
	do{
		tmp_add = num_add;
  		tmp_del = num_del;
		setFlag(node);
		addTree(node);
		setFlag(node);
    	cutTree(node);
    	setFlag(node);
    	printf("\nStage%d:\n",count);
  		printf("\nadded %i nodes\n",num_add-tmp_add);
  		printf("\nremoved %i nodes\n",num_del-tmp_del);
  		count++;
  	}while(tmp_add!=num_add || tmp_del!=num_del);
  	printf("\ntotal added %i nodes\n",num_add);
  	printf("\ntotal removed %i nodes\n",num_del);
}








// Evaluate function at centre of quadtree node

double nodeValue( Node *node, double time ) {

  	int level = node->level;
  	double x = node->xy[0];
  	double y = node->xy[1];

  	double h = pow(2.0,-level);

  	return( value( x+0.5*h, y+0.5*h, time ) );
}

// Data function

double value( double x, double y, double time ) {

  	return( 2.0*exp(-8.0*(x-time)*(x-time)) - 1.0 ) ;
}


