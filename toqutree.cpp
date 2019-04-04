
/**
 *
 * toqutree (pa3)
 * significant modification of a quadtree .
 * toqutree.cpp
 * This file will be used for grading.
 *
 */

#include "toqutree.h"

toqutree::Node::Node(pair<int,int> ctr, int dim, HSLAPixel a)
	:center(ctr),dimension(dim),avg(a),NW(NULL),NE(NULL),SE(NULL),SW(NULL)
	{}

toqutree::~toqutree(){
	clear(root);
}

toqutree::toqutree(const toqutree & other) {
	root = copy(other.root);
}


toqutree & toqutree::operator=(const toqutree & rhs){
	if (this != &rhs) {
		clear(root);
		root = copy(rhs.root);
	}
	return *this;
}


//Debug Sheet
//Compiles: yes
//Working: not sure, but most likely yes
toqutree::toqutree(PNG & imIn, int k){ 

/* This constructor grabs the 2^k x 2^k sub-image centered */
/* in imIn and uses it to build a quadtree. It may assume  */
/* that imIn is large enough to contain an image of that size. */

// // Creating the subimage
// PNG subimage(pow(2,k),pow(2,k));
// int center = imIn.width()/2;
// // Getting the right coordinates for the subimage square
// int upleft = center - pow(2,k)/2;
// int upright = center + pow(2,k)/2;

// // Change the pixel by using getPixel, and then change the pixel 
// for(int x = 0; x < pow(2,k); x++){
// 	for(int y = 0; y < pow(2,k); y++){
// 		HSLAPixel* pixel = subimage.getPixel(x,y);
// 		HSLAPixel* originalpixel = imIn.getPixel(upleft + x, upleft + y);
// 		*pixel = *originalpixel; 
// 	}
// }

// root = buildTree(subimage,k);

}

//Debug Sheet
//Compiles: yes
//Working: internally yes
int toqutree::size() {
	return size(root);
}

int toqutree::size(const Node* node){
	int count = 1;
	if (node->NW == NULL && node->SW == NULL && node->SE == NULL && node->NE == NULL){
		return count;
	}
	if (node->NW != NULL){
		count = count+size(node->NW);
	}
	if (node->NE != NULL){
		count = count+size(node->NE);
	}
	if (node->SW != NULL){
		count = count+size(node->SW);
	}
	if (node->SE != NULL){
		count = count+size(node->SE);
	}

	return count;
}

//Debug Sheet
//Compiles: no
//Working: no
toqutree::Node * toqutree::buildTree(PNG * im, int k) {
	/* your code here */

	//Optimal entropy and points for deciding the split
	pair<int,int> optimal;
	double minEntropy;
	return NULL;
}

//Debug Sheet
//Compiles: yes
//Working: no
PNG toqutree::render(){

// My algorithm for this problem included a helper function
// that was analogous to Find in a BST, but it navigated the 
// quadtree, instead.

/* your code here */
}

/* oops, i left the implementation of this one in the file! */
void toqutree::prune(double tol){

	// prune(root,tol);

}


//Debug Sheet
//Compiles: yes
//Working: yes

/* called by destructor and assignment operator*/
void toqutree::clear(Node * & curr){

	//Run through conds to slowly delete the node
	if (root->NW != NULL){
		clear(root->NW);
	}
	if (root->NE != NULL){
		clear(root->NE);
	}
	if (root->SW != NULL){
		clear(root->SW);
	}
	if (root->SE != NULL){
		clear(root->SE);
	}

	if (root->NW == NULL && root->SW == NULL && root->SE == NULL && root->NE == NULL){
		delete curr;
		curr = NULL;
	}
	else {
		delete curr;
		curr = NULL;
	}
	//Everything should be deleted now
}

//Debug Sheet
//Compiles: yes
//Working: should be

/* called by assignment operator and copy constructor */
toqutree::Node * toqutree::copy(const Node * other) {
	root = copyTree(other);
}

toqutree::Node * toqutree::copyTree(const Node * other) {
		if (other != NULL){
		Node* newNode = new Node(other->center, other->dimension, other->avg);

		newNode->NW = copyTree(other->NW);
		newNode->NE = copyTree(other->NE);
		newNode->SW = copyTree(other->SW);
		newNode->SE = copyTree(other->SE);

		return newNode;
	}
	else {
		return NULL;
	}
}


