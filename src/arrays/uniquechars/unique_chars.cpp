
#include <iostream>
#include <cmath>

int main(int argc, char *argv[]){
	if (argc>1)
	{
		char *reverseThis = argv[1];
		
/*
		Alternative 1
		int i = strlen(reverseThis);
		char *reversedString  = (char *)malloc(i*sizeof(char));
		//memset(reversedString, NULL, i);
		int resI = 0; 

		for (; i>=0; i--)
		{
			if(reverseThis[i]==NULL)
			{
				continue;
			}
			reversedString[resI] = reverseThis[i];
			resI++;
		}
		reversedString[resI] = NULL;
*/


		int endPivot = strlen(reverseThis);
		int startPivot = 0;
		int  center = ceil(endPivot/2);
		char *reversedString  = (char *)malloc(endPivot*sizeof(char));

		for(; startPivot < center && endPivot > center; startPivot++, endPivot--)
		{
			if(reverseThis[endPivot]==NULL)
			{
				endPivot--;
			}
			reversedString[startPivot] = reverseThis[endPivot];
			reversedString[endPivot] = reverseThis[startPivot];
		}
		reversedString[center] = reverseThis[center];
		reversedString[strlen(reverseThis)] = NULL;

		std::cout << "Reversed: "<< reversedString << std::endl;
		
	}

}