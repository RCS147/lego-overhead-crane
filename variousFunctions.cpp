// v.1
// Last revision made Nov. 12, 2014 by Yaning Tan

int const Y_COL=3;
int const X_ROW=2;
int const Z_HI=4;

int grid[X_ROW][Y_COL][Z_HI]={-1};

struct Block() {
	int x, y,z;
	int color;
	
}

void zero(){
	//move x,y,z motors in the negative direction until limits are hit
	//set encoders to zero
}

void sort(){
	// @param Block
	// if colour already in inventory, put it with other colours
	// else, put in empty space
	// update array height
	 int xInd, yInd, zInd=-1,xEm,yEm, needEmpty=0;
	 for (int i=0;i<X_ROW;i++){
	 	for (int j=0;j<Y_COL;j++){
	 		
	 		// If a pile for the colour exists, keep track of those coordinates
	 		if (grid[i][j][0]==color){
	 			for (int k=0;k<Z_HI;k++){
	 				// Finds height of stack
	 				if (k>zInd)
	 					zInd=k;

	 				needEmpty=-1;
	 			}
	 		}

 			// Save the first empty grid location in case the colour is not found
 			else if (needEmpty==0 && grid[i][j][0]==-1){
 				xEm=i;
 				yEm=j;
 				needEmpty=1;
 			}
 				
 		}
	 	
	 }
	 
	 if (zInd==Z_HI-1 || needEmpty==1){
	 	// If stack of colours is too high or no existing stack, put in empty space
	 	// Assume will never have more blocks than can fit in warehouse
	 	// Assume will not have more colours than can fit
	 	
		// move block to [xEm][yEm][0]
		//update grid
	 }
	 
	 else{
	 	//move block to [xInd][yInd][zInd+1]
	 	// update grid
	 }
}

void move (xCurrent, yCurrent,x,y,z){
	if (xCurrent<x)){
		//x motor has positive value
	}
	else{
		//x motor has negative value
	}
}

void retrieve (int nObjects){
	//pickOrder
	//for loop
		//move to each location
		//pick up and verify object has been retrieved
		//move back to loading bay and unload
		
}

void store(){
	//move to loading bay
	//pick up object and detect colour
	//determine storage location
	//move to storage location
	//verify object has been stored
}

int pickOrder (int n){
	//order picking algorithm
	return n;
}

