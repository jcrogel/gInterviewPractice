#include <iostream>
#include <vector>

class JCHeap
{
	private:
		std::vector<int> __heap;

		static std::vector<int> __buildMaxHeap(std::vector<int> src)
		{
			int size = (src.size()/2)-1;
			//
			
			for(int i = size; i != -1; i--)
			{

				JCHeap::__maxHeapify(&src, i);
			}
			std::cout << "Built!"<< std::endl;

			return src;
		}


		static int __getHeapSize(const std::vector<int> *src, int i)
		{
			int result;
			result = src->size()-i;
			return result;
		}

		static void __maxHeapify(std::vector<int> *src, int i)
		{
			//
			int leftIndex = JCHeap::__getLeftIndex(i);
			int rightIndex = JCHeap::__getRightIndex(i);
			int largestValue = i;

			if(leftIndex < src->size() && src->at(leftIndex) > src->at(largestValue))
			{
				largestValue = leftIndex;
			}

			if(rightIndex < src->size() && src->at(rightIndex) > src->at(largestValue))
			{
				largestValue = rightIndex;
			}

			if(largestValue != i)
			{
				//std::cout << "i: " << i << " Value: " << (*src)[i] << " largestIndex: " << largestValue << " largestValue: " << (*src)[largestValue] << std::endl;
				JCHeap::__swapXY(src, i, largestValue);
				/*
				std::cout << "Step:" << i << "; ";
				for (std::vector<int>::iterator I = src->begin(); I!= src->end(); I++)
				{
					std::cout << (*I) << ",";
				}
				std::cout << std::endl;
				*/
				JCHeap::__maxHeapify(src, largestValue);
			}

			return;
		}


		static int __getParentIndex(int i)
		{
			return (i/2)-1;	// Done to conform i=1; i=0 from pseudocode
		}

		static int __getLeftIndex(int i)
		{
			return (2*i)+1;  // Done to conform i=1; i=0 from pseudocode
		}

		static int __getRightIndex(int i)
		{
			return (2*i)+2; // Done to conform i=1; i=0 from pseudocode
		}

		static void __swapXY(std::vector<int> *src, int x, int y)
		{
			int tempValue = src->at(x);
			(*src)[x] = src->at(y);
			(*src)[y] = tempValue;
		}

	public:
		
		JCHeap(std::vector<int> source){
			__heap = JCHeap::__buildMaxHeap(source);
		}

		~JCHeap()
		{

		}

		int getParent(int i)
		{
			return 0;
		}

		int getLeft(int i)
		{
			return 0;
		}

		int getRight(int i)
		{
			return 0;
		}

		std::vector<int> getHeap()
		{
			return __heap;
		}

		std::vector<int> getSorted()
		{
			std::vector<int> heap = __heap;
			std::vector<int> result;
			result.reserve(heap.size());


			while (heap.size()>0)
			{
				int lastPos = heap.size()-1;
				JCHeap::__swapXY(&heap , 0, lastPos);
				result.push_back(heap[lastPos]);
				heap.pop_back();
				JCHeap::__maxHeapify(&heap, 0);
			}

			return result;
		}

};


std::vector<int> parseArray(char *arg)
{
	int elemCnt = 0;
	
	int lastComma = 0;

	std::vector<int> result;
	std::string argChar(arg);

	int found = argChar.find(',');

	while (found != std::string::npos)
	{
		if (found > argChar.size())
		{
			break;
		}

		char *subStr = const_cast<char *>(argChar.substr(lastComma, found-lastComma).c_str());
		result.push_back(atoi(subStr));

		lastComma = found + 1;
		found = argChar.find(',', lastComma);
	}

	if(lastComma < argChar.size())
	{
		char *subStr = const_cast<char *>(argChar.substr(lastComma, found-lastComma).c_str());
		result.push_back(atoi(subStr));
	}

	return result;
}

int main(int argc, char *argv[])
{
	if (argc>1)
	{
		std::vector<int> intArray = parseArray(argv[1]);
		JCHeap h(intArray);
		std::vector<int> heap = h.getHeap();
		std::vector<int> sorted = h.getSorted();

		std::cout << "Heap:";
		for (std::vector<int>::iterator I = heap.begin(); I!= heap.end(); I++)
		{
			std::cout << (*I) << ",";
		}
		std::cout << std::endl;

		std::cout << "Sorted:";
		for (std::vector<int>::iterator I = sorted.begin(); I!= sorted.end(); I++)
		{
			std::cout << (*I) << ",";
		}
		std::cout << std::endl;

	}
} 