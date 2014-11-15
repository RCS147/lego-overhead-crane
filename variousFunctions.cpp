// v.1
// Last revision made Nov. 12, 2014 by Yaning Tan
// Revised Nov. 13, 2014 by Rachel Lee - added bfs function to be called by findClosestColour and findStorePos
// Revised Nov. 14, 2014 by Rachel Lee - merged bfs function and findClosestColor, integrated findClosestColor in findStorePos

int const Y_COL=3;
int const X_ROW=2;
int const Z_HI=4;

int const X_MAX = 1150;
int const Y_MAX = 760;
int const Z_MAX = 300;

short const motorX = motorA;
short const motorY = motorB;
short const motorZ = motorC;

short const limitX = S1;
short const limitY = S2;
short const limitZ = S3;
short const color = S4;

int grid[X_ROW][Y_COL][Z_HI];

struct Block() {
	int x, y,z;
	int color;
	
}

void zero(){
	//move x,y,z motors in the negative direction until limits are hit
	//set encoders to zero
}

// Used in findClosestColor function in order to have a list of arrays
struct Ar{
		int elem[2];
	};
	
void findClosestColor (int color, int & xPos, int & yPos, bool findStack){
	// Searches a grid by starting at one corner and looking at adjacent squares
	// if findStack, changes xPos, yPos to location of nearest available stack
	// 		doesn't change if no available stacks
	// if !findStack, changes xPos, yPos to location of nearest colour stack
	
	/* @param color				The color to look for
	// @param xPos, yPos		The coordinates of where the arm should go to findStack/retrieve
	// @param findStack			True if looking for a stack of a specific colour with space available, false if otherwise
	//							(i.e. Looking for empty space or looking to retrieve something)
	*/
	cout << "Looking for "<<color<<endl;
	int x,y;
	list <Ar> q; // A queue to findStack what to look at next
	bool visited[X_ROW][Y_COL]={false};
	bool leave=false;

	Ar a;
	Ar current;
	a.elem[0]=1;
	a.elem[1]=0;
	q.push_back(a);
	
	a.elem[0]=0;
	a.elem[1]=1;
	q.push_back(a);
	
	// Searches while there are still elements to search or until the colour is found
	while (!q.empty() && !leave){
		current = q.front();
		q.pop_front();
		
		x = current.elem[0];
		y = current.elem[1];
		
		if (!visited[x][y]){
			// If called by retrieve function and found colour stack
			// Or if called by findStack function and found colour stack and stack has space for another box
			if (grid[x][y][0]==color && !findStack || grid[x][y][0]==color && findStack && grid[x][y][Z_HI-1]!=color){
				xPos=x;
				yPos=y;
				leave=true;
			}
			
			
			else {
				visited[x][y]=true;
				
				// Adds the adjacent squares to the search queue
				if (x+1<X_ROW){
					a.elem[0]=x+1;
					q.push_back(a);
				}
			
				if (y+1<Y_COL){
					a.elem[0]=x;
					a.elem[1]=y+1;
					q.push_back(a);
				}
			}	
		}
	}
}

void findStorePos(int color, int&x,int&y, int&z){
	// Determines where the block should be stored
	/* @param color			Colour to look for
	// @param x, y			Coordinates
	*/
	int tempX,tempY;
	z=0; // z-coordinate set to 0 by default
	
	findClosestColor(-1,x,y,false);
	
	tempX=x;
	tempY=y;
	
	findClosestColor(color,tempX,tempY,true);
	cout<< tempX<<" "<<tempY<<endl;
	
	/* 	If an existing stack has space for another block, xPos and yPos would
	//	have changed in the second call of bfs
	// 	Loop through stack (z-direction) to find height of stack
	*/
	if (tempX!=x && tempY!=y){
		x=tempX;
		y=tempY;
		
		//Finds height of stack
		for (int i=0;i<Z_HI;i++)
			if (grid[x][y][i]==color && i>z)
				z=i;
				
		z+=1; // Next space up is where box is stored
	}
}

void move (xCurrent, yCurrent,x,y,z){
	//Retract the forks to avoid collisions
	motor[motorZ] = -50;
	while(SensorValue[limitZ] != 1);
	motor[motorZ] = 0;
	nMotorEncoder[motorZ] = 0;
	
	//Set the motor encoder targets
	//the X_MAX, Y_MAX and Z_MAX values store the number of encoder counts from
	//th zero position to the maximum reach of the crane. 
	nMotorEncoderTarget[motorX] = (x - xCurrent)*X_MAX/X_ROW;
	nMotorEncoderTarget[motorY] = (y - yCurrent)*Y_MAX/Y_COL;
	nMotorEncoderTarget[motorZ] = (z)*Z_MAX/Z_HI;
	
	//Move to the proper X, Y position
	motor[motorX] = sgn(x - xCurrent)*50;
	motor[motorY] = sgn(y - yCurrent)*50;
	
	while(motor[motorX] > 0 && motor[motorY] > 0)
	{
		if(nMotorRunState[motorX] == runStateHoldPosition)
		{
			motor[motorX] = 0;
		}
		if(nMotorRunState[motorY] == runStateHoldPosition)
		{
			motor[motorY] = 0;
		}
		
		//If the limit switch is tripped, stop the motor and reset the encoders
		if(SensorValue[limitX] != 0)
		{
			motor[motorX] = 0;
			nMotorEncoder[motorX] = 0;
		}
		if(SensorValue[limitY] != 0)
		{
			motor[motorY] = 0;
			nMotorEncoder[motorY] = 0;
		}
	}	
	
	//Lower the arm
	motor[motorZ] = 50;
	while(motor[motorZ] > 0)
	{
		if(nMotorRunState[motorZ] == runStateHoldPosition)
		{
			motor[motorZ] = 0;
		}
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

