
/*
Compress

aabbbccccaaa
a2b3c4a3

iterate each chars,  count iterations, then compare size of characters

*/


#import <cmath>
#import <iostream>
#import <string>
#import <sstream>


void addCompressionToStringStream(std::stringstream *ss, char lastChar, int charCnt)
{
	if(lastChar)
	{
		if(charCnt > 1)
		{
			*ss << charCnt << lastChar;
		}
		else
		{
			*ss << lastChar;
		}	
	}
}

std::string compress(std::string toCompress)
{
	int compressLenght = toCompress.size();

	std::stringstream output;
			
	char frontChar = NULL;
	int frontCnt = 0;
	
	for(int startPivot = 0; startPivot <= compressLenght;  startPivot++)
	{
		if (toCompress[startPivot] == 0)
		{
			break;
		}

		if (frontChar == 0 || frontChar != toCompress[startPivot] )
		{
			
			addCompressionToStringStream(&output, frontChar, frontCnt);

			frontChar = toCompress[startPivot];
			frontCnt = 0;
		}

		frontCnt++;
	}
	addCompressionToStringStream(&output, frontChar, frontCnt);



	if (compressLenght > output.gcount())
	{
		return output.str();
	}

	return toCompress;
}


int main(int argc, char* argv[])
{
	if (argc>1)
	{
		std::string result = compress(argv[1]);

		std::cout << "Compressed: " << result << std::endl;

	}

}