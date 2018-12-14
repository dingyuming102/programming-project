#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <basicFunction.h>
#include <plantTree.h>


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
    /*
    growTree(head);
    growTree(head);
    removeChildren(head->child[1]);// task2-1
    writeTree( head );
    destroyTree(head);
	*/
    
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
  	printf("\nadded %i nodes\n",add_max);
  	printf("\nremoved %i nodes\n",cut_max);
    writeTree( head );//task3-1
    */
     
    //*
    growTree(head);
    growTree(head);
    growTree(head);
    setFlag(head);
    adapt(head);
  	printf("\nadded %i nodes\n",add_max);
  	printf("\nremoved %i nodes\n",cut_max);
    writeTree(head);  //task3-2
    //*/


  	return 0;
}
