#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <basicFunction.h>
#include <plantTree.h>

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
		return;
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


void setFlag(Node *node){
	double value;
	int i,flag;
	if(node){
		for(i=0;i<4;i++){
	 		setFlag(node->child[i]);
			value = nodeValue( node, 0.0 );
			if(node->child[0]==NULL){
				if(value>0.5)
					node->flag = 1;
				else if(value<-0.5)
					node->flag = -1;
				else
					node->flag = 0;
			}
		}
		return;		
	}else
		return;
}




void addTree1(Node *node){
	int i;
	if(node){
		for(i=0;i<4;i++){
	 		addTree(node->child[i]);
			if(node->child[0]==NULL && node->flag==1){
				makeChildren( node );
				add_max += 4;
			}
		}
		return;		
	}else
		return;

}
int addTree(Node *node){
	int i,change;
	if(node->level < 6){
		for(i=0;i<4;i++){
			if(node->child[i])
				addTree(node->child[i]);
		}if(node->flag == 1){
			makeChildren(node);
			change += 4;
		}
	}
	return change;
		
}

int cutTree(Node *node){
	int i;
	int change;
	if(node->child[0]){
		for(i=0;i<4;i++){
	 		cutTree(node->child[i]);
			if( node->child[0]->flag == -1 &&node->child[1]->flag == 1 &&node->child[2]->flag == -1 &&node->child[3]->flag == -1 ) {
				removeChildren(node);
				change += 4;
			}
		}
	}
	return change;

}


void adapt(Node * head){
	int add_temp,cut_temp;
	
	do{
		
		
		add_temp = addTree(head);
		cut_temp = cutTree(head);
		printf("\nadded %i nodes\n",add_temp);
  		printf("\nremoved %i nodes\n",cut_temp);
	}while(add_temp!=0 || cut_temp!=0);
	
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
