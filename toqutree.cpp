
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
//Working: yes (with reliance on buildtree)
toqutree::toqutree(PNG & imIn, int k){ 

/* This constructor grabs the 2^k x 2^k sub-image centered */
/* in imIn and uses it to build a quadtree. It may assume  */
/* that imIn is large enough to contain an image of that size. */

// // Creating the subimage
PNG subimage(pow(2,k),pow(2,k));
int center = imIn.width()/2;
// Getting the right coordinates for the subimage square
int upleft = center - pow(2,k)/2;
int upright = center + pow(2,k)/2;

// Change the pixel by using getPixel, and then change the pixel 
// Help from a TA here
for(int x = 0; x < pow(2,k); x++){
	for(int y = 0; y < pow(2,k); y++){
		*(subimage.getPixel(x,y))=*(imIn.getPixel(x,y));
		}
	}
root=buildTree(&subimage, pow(2,k));
}

//Debug Sheet
//Compiles: yes
//Working: yes
//FULL MARKS 
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
//Compiles: yes
//Working: haven't done bigger cases yet
//@TODO
toqutree::Node * toqutree::buildTree(PNG * im, int k) {
	if(k==1){
		//Pixel Doesn't matter just return 1 pixel
		HSLAPixel avg= *(im->getPixel(0,0));
		Node* newNode =  new Node(pair<int,int>(0,0), 1, avg);
		return newNode;
	}
	else if(k==2){
		//2x2 pretty straight foward
		stats* pngStats= new stats(*im);
		HSLAPixel avg= pngStats->getAvg(pair<int,int>(0,0),pair<int,int>(1,1));
		Node* newNode= new Node(pair<int,int>(1,1), 2, avg);
		newNode->SE = new Node(pair<int,int>(0,0),1,*(im->getPixel(1,1)));
		newNode->SW = new Node(pair<int,int>(0,0),1,*(im->getPixel(0,1)));
		newNode->NE = new Node(pair<int,int>(0,0),1,*(im->getPixel(1,0)));
		newNode->NW = new Node(pair<int,int>(0,0),1,*(im->getPixel(0,0)));
		delete pngStats;
		return newNode;
	}
	else {
		//This is just here because for some reason the other code fails
		stats* pngStats= new stats(*im);
		HSLAPixel avg= pngStats->getAvg(pair<int,int>(0,0),pair<int,int>(1,1));
		Node* newNode= new Node(pair<int,int>(1,1), 2, avg);
		newNode->SE = new Node(pair<int,int>(0,0),1,*(im->getPixel(1,1)));
		newNode->SW = new Node(pair<int,int>(0,0),1,*(im->getPixel(0,1)));
		newNode->NE = new Node(pair<int,int>(0,0),1,*(im->getPixel(1,0)));
		newNode->NW = new Node(pair<int,int>(0,0),1,*(im->getPixel(0,0)));
		delete pngStats;
		return newNode;

	// 	//Static vars
	// 	stats* pngStats= new stats(*im);
	// 	pair<int,int> pivotStart = make_pair(k/4, k/4);
	// 	int boundary=k/2;
	// 	HSLAPixel avg= pngStats->getAvg(make_pair(0,0),make_pair(k-1,k-1));

	// 	//Thing we cycle through to determine optimal points
	// 	pair<int,int> NWStart;
	// 	pair<int,int> NEStart;
	// 	pair<int,int> SEStart;
	// 	pair<int,int> SWStart;

	// 	//Optimal splitting point
	// 	pair<int,int> optimalCtr;
	// 	int currMinEntropy = 9999;

	// 	//SEARCH HERE
	// 	for (int y=pivotStart.first; y < pivotStart.first+boundary; y++){
	// 		for (int x = pivotStart.first; x< pivotStart.first+boundary; x++){
	// 			//Entropy for respective corners;
	// 			int SE = pngStats->entropy(make_pair(x,y), make_pair((x+boundary-1) % k,(y+boundary-1) % k));
	// 			int SW = pngStats->entropy(make_pair((x+boundary) % k,y), make_pair((x-1) % k,(y+boundary-1)%k));
	// 			int NE = pngStats->entropy(make_pair(x,(y+boundary)% k), make_pair((x+boundary-1)%k,(y-1) % k));
	// 			int NW = pngStats->entropy(make_pair((x+boundary) % k,(y+boundary) % k), make_pair((x-1) % k,(y-1) % k));
	// 			int avgEntropy = (SE+SW+NE+NW)/4;

	// 			if (currMinEntropy >= avgEntropy){
	// 				currMinEntropy = avgEntropy;
	// 				optimalCtr = make_pair(x,y);
	// 				NWStart = make_pair((x+boundary) % k,(y+boundary) % k);
	// 				NEStart = make_pair(x,(y+boundary)% k);
	// 				SEStart = make_pair(x,y);
	// 				SWStart = make_pair((x+boundary) % k,y);
	// 		}

	// 	}
	// }
	// 	PNG* SE = subPNG(im, SEStart,k);
	// 	PNG* SW = subPNG(im, SWStart,k);
	// 	PNG* NE = subPNG(im, NEStart,k);
	// 	PNG* NW = subPNG(im, NWStart,k);

	// 	Node * newNode= new Node(optimalCtr, k, avg);
	// 	newNode->SE = buildTree(SE, k/2);
	// 	newNode->SW = buildTree(SW, k/2);
	// 	newNode->NE = buildTree(NE, k/2);
	// 	newNode->NW = buildTree(NW, k/2);

	// 	delete NE;
	// 	delete NW;
	// 	delete SE;
	// 	delete SW;
	// 	delete pngStats;
	// 	return newNode;
	}
}	

PNG* toqutree::subPNG(PNG* originalIm, pair<int,int>start,int k){
	PNG* subImg= new PNG(k/2, k/2);
	for(int x = 0;x<originalIm->width(); x++){
		for(int y = 0;y<originalIm->height(); y++){	
			//Handles wrapping 		
			HSLAPixel pixelSpot = *(subImg->getPixel(x,y));
			pixelSpot= *(originalIm->getPixel((start.first+x)%originalIm->width(),(start.second+y)%originalIm->width()));
		}
	}
	return subImg;
}

//Debug Sheet
//Compiles: yes
//Working: yes
//FULL MARKS -> Clear works therefor it means our code for render works at least
PNG toqutree::render(){
// My algorithm for this problem included a helper function
// that was analogous to Find in a BST, but it navigated the 
// quadtree, instead.
	return renderimg(root);
}

PNG toqutree::renderimg(Node* node){
	int dim = node->dimension;
	PNG img(dim,dim);
	if(node->SE==NULL || node->SW==NULL || node->NE==NULL || node->NW==NULL){
		//Case where we are at the end of the tree
		for(int x = 0;x<dim;x++){
			for(int y = 0; y<dim ; y++){
				HSLAPixel* pixel = img.getPixel(x,y);
				*pixel = node->avg;
			}
		}
		//Return the rendered PNG
		return img;
	}
	else {
		int ctrx= node->center.first;
		int ctry= node->center.second;
		//render the subimages
		PNG NEimg = renderimg(node->NE);
		PNG NWimg = renderimg(node->NW);
		PNG SEimg = renderimg(node->SE);
		PNG SWimg = renderimg(node->SW);

		for(int x=0; x< (dim/2); x++){
			for(int y=0; y<(dim/2); y++){
				//Idea from TA in lab
				//THIS IS CANCER CALCULATION NATHAN, NOT SURE IF IT'S RIGHT
				pair<int, int> NE = make_pair(((ctrx+x)%dim), (((ctry+dim/2)%dim+y)%dim));        
				pair<int, int> NW = make_pair((((ctrx+dim/2)%dim+x)%dim), (((ctry+dim/2)%dim+y)%dim));
				pair<int, int> SE = make_pair(((ctrx+x)%dim), ((ctry+y)%dim));
				pair<int, int> SW = make_pair((((ctrx+dim/2)%dim+x)%dim), ((ctry+y)%dim));

				*img.getPixel(NE.first, NE.second) = *(NEimg.getPixel(x,y));
				*img.getPixel(NW.first, NW.second) = *(NWimg.getPixel(x,y));
				*img.getPixel(SE.first, SE.second) = *(SEimg.getPixel(x,y));
				*img.getPixel(SW.first, SW.second) = *(SWimg.getPixel(x,y));
			}
		}
		return img;
	}

}

/* oops, i left the implementation of this one in the file! */
void toqutree::prune(double tol){
	prune(root,tol);
}

//Debug Sheet
//Compiles: yes
//Working: no, yet to be implemented
//@TODO
void toqutree::prune(Node* node,double tol){
	if (pruneCheck(node,node,tol) == 1){
		clear(node);
	}
	else{
		if(node->dimension >2){
			prune(node->NW, tol);
			prune(node->NE, tol);
			prune(node->SW, tol);
			prune(node->NE, tol);
		}
		return;
	}
}
//Debug Sheet
//Compiles: yes
//Working: yes
//FULL MARKS 
// I REALIZE THAT I COULD HAVE USED A FUCKING BOOLEAN, BUT I'M TOO USED TO 213
int toqutree::pruneCheck(Node* prev, Node* curr, double tol){
	int avgDistNE = prev->avg.dist(curr->NE->avg);
	int avgDistNW = prev->avg.dist(curr->NW->avg);
	int avgDistSE = prev->avg.dist(curr->SE->avg);
	int avgDistSW = prev->avg.dist(curr->SW->avg);

	if (curr->dimension <= 2 && avgDistNE < tol && avgDistNW < tol && avgDistSE < tol && avgDistSW < tol){
		return 1; //true
	}
	else if (curr->dimension != 2){
		//I pray this actually works
		//If all satisfy the condition that they are similar, we can return true, but otherwise false
		//Recursively checks if the base case above is met
		if (pruneCheck(prev,curr->NW, tol) != 1){
			return 0; //False
		}
		if (pruneCheck(prev,curr->NE, tol) != 1){
			return 0; //False
		}
		if (pruneCheck(prev,curr->SE, tol) != 1){
			return 0; //False
		}
		if (pruneCheck(prev,curr->SW, tol) != 1){
			return 0; //False
		}
		else {
			return 1; //True
		}
	}
	else{
		return 0; //False
	}
}



//Debug Sheet
//Compiles: yes
//Working: yes
//FULL MARKS 
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
//Working: yes
//FULL MARKS 
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


