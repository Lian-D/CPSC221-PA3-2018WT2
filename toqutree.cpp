
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
PNG* subimage = new PNG(pow(2,k),pow(2,k));
int center = imIn.width()/2;
// Getting the right coordinates for the subimage square
int upleft = center - pow(2,k)/2;
int upright = center + pow(2,k)/2;

// Change the pixel by using getPixel, and then change the pixel 
for(int x = 0; x < pow(2,k); x++){
	for(int y = 0; y < pow(2,k); y++){
		HSLAPixel* pixel = subimage->getPixel(x,y);
		HSLAPixel* originalpixel = imIn.getPixel(upleft + x, upleft + y);
		*pixel = *originalpixel; 
	}
}

root = buildTree(subimage,k);

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
	//Case inwhich the we have the smallest division
	if (k==0){
		stats* pngStats = new stats(*im);
		pair<int, int> coordinates = make_pair(0,0);
		HSLAPixel avg = pngStats->getAvg(make_pair(0,0),make_pair(0,0));
		Node* newNode = new Node(coordinates,0,avg);
		newNode->NW = NULL;
		newNode->NE = NULL;
		newNode->SW = NULL;
		newNode->SE = NULL;
		delete pngStats;
		delete im;
		return newNode;
	}
	//Not the smallest division
	else {
		//For the SE
		pair<int, int> ul_SE_Coordinates;
		pair<int, int> lr_SE_Coordinates;

		//For the SW
		pair<int, int> ul_SW_Coordinates;
		pair<int, int> lr_SW_Coordinates;

		//For the NE 
		pair<int, int> ul_NE_Coordinates;
		pair<int, int> lr_NE_Coordinates;

		//For the NW
		pair<int, int> ul_NW_Coordinates;
		pair<int, int> lr_NW_Coordinates;

		long currMinEntropy=0;

		int subDim = pow(2,k)/2;
		int incrementSpace = pow(2,k)/4;

		stats* pngStats = new stats(*im);
		for (int y=incrementSpace; y < 3*incrementSpace; y++){
			for (int x = incrementSpace; x< 3*incrementSpace; x++){
				int SE = pngStats->entropy(make_pair(x,y), make_pair(x+subDim - 1, y+subDim - 1));
				int SW = pngStats->entropy(make_pair(x+subDim,y), make_pair(x+subDim+subDim -1, y+subDim - 1));
				int NE = pngStats->entropy(make_pair(x,y+subDim), make_pair(x+subDim-1, y+subDim+subDim-1));
				int NW = pngStats->entropy(make_pair(x+subDim,y+subDim), make_pair(x+subDim+subDim-1, y+subDim+subDim-1));

				int avgEntropy = (SE+SW+NE+NW)/4;

				if (currMinEntropy == 0){
					currMinEntropy = avgEntropy;
				}
				else if (currMinEntropy < avgEntropy){
					currMinEntropy = avgEntropy;
					ul_SE_Coordinates = make_pair(x,y);
					lr_SE_Coordinates = make_pair(x+subDim - 1, y+subDim - 1);

					ul_SW_Coordinates = make_pair(x+subDim,y);
					lr_SW_Coordinates = make_pair(x+subDim+subDim -1, y+subDim - 1);

					ul_NE_Coordinates = make_pair(x,y+subDim);
					lr_NE_Coordinates = make_pair(x+subDim-1, y+subDim+subDim-1);

					ul_NW_Coordinates = make_pair(x+subDim,y+subDim);
					lr_NW_Coordinates = make_pair(x+subDim+subDim-1, y+subDim+subDim-1);
				}
			}
		}
		Node* newNode = new Node(ul_SE_Coordinates, k, pngStats->getAvg(ul_SE_Coordinates,lr_SE_Coordinates));

		*newNode->SE = buildTree(subPNGMaker(*im,ul_SE_Coordinates,lr_SE_Coordinates,k-1), k-1);
		*newNode->SW = buildTree(subPNGMaker(*im,ul_SW_Coordinates,lr_SW_Coordinates,k-1), k-1);
		*newNode->NE = buildTree(subPNGMaker(*im,ul_NE_Coordinates,lr_NE_Coordinates,k-1), k-1);
		*newNode->SW = buildTree(subPNGMaker(*im,ul_NW_Coordinates,lr_NW_Coordinates,k-1), k-1);

		delete pngStats;
		delete im;
		return newNode;
	}

}

PNG* toqutree::subPNGMaker(PNG* im, pair<int,int> ul, pair<int,int> lr, int k){
	PNG* subimage = new PNG(pow(2,k),pow(2,k));
	for(int x = ul.first; x < lr.first; x++){
		for(int y = ul.second; y < lr.second; y++){
			HSLAPixel* pixel = subimage->getPixel(x,y);
			HSLAPixel* originalpixel = im->getPixel(x, y);
			*pixel = *originalpixel; 
		}
	}
	return subimage;
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
	prune(root,tol);
}

void toqutree::prune(Node* node,double tol){

}


//Debug Sheet
//Compiles: yes
//Working: yes

/* called by destructor and assignment operator*/
void toqutree::clear(Node * & curr){
	if (curr == NULL){
		return;
	}
	else{
		clear(curr->SE);
		clear(curr->SW);
		clear(curr->NE);
		clear(curr->NW);

		delete curr;
		curr = NULL;
	}
}

//Debug Sheet
//Compiles: yes
//Working: should be

/* called by assignment operator and copy constructor */
toqutree::Node * toqutree::copy(const Node * other) {
	root = copyTree(other);
	return root;
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


