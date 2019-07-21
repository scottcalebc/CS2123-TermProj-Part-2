part2 : part2.o heapSort_int.o heapSort_str.o insertionSort_int.o insertionSort_str.o mergeSort_int.o mergeSort_str.o quickSort_int.o quickSort_str.o \
		radixSort_int.o radixSort_str.o searchAlgorithms.o selectionSort_int.o selectionSort_str.o 
		gcc -g -o part2 part2.o heapSort_int.o heapSort_str.o insertionSort_int.o insertionSort_str.o mergeSort_int.o mergeSort_str.o quickSort_int.o quickSort_str.o \
				radixSort_int.o radixSort_str.o searchAlgorithms.o selectionSort_int.o selectionSort_str.o 

heapSort_int.o : heapSort_int.c projectHeader.h
	gcc -c heapSort_int.c

heapSort_str.o : heapSort_str.c projectHeader.h
	gcc -c heapSort_str.c

insertionSort_int.o : insertionSort_int.c projectHeader.h
	gcc -c insertionSort_int.c

insertionSort_str.o : insertionSort_str.c projectHeader.h
	gcc -c insertionSort_str.c

mergeSort_int.o : mergeSort_int.c projectHeader.h
	gcc -c mergeSort_int.c

mergeSort_str.o : mergeSort_str.c projectHeader.h
	gcc -c mergeSort_str.c

quickSort_int.o : quickSort_int.c projectHeader.h
	gcc -c quickSort_int.c

quickSort_str.o : quickSort_str.c projectHeader.h
	gcc -c quickSort_str.c

radixSort_int.o : radixSort_int.c projectHeader.h
	gcc -c radixSort_int.c

radixSort_str.o : radixSort_str.c projectHeader.h
	gcc -c radixSort_str.c

searchAlgorithms.o : searchAlgorithms.c projectHeader.h
	gcc -c searchAlgorithms.c

selectionSort_int.o : selectionSort_int.c projectHeader.h
	gcc -c selectionSort_int.c

selectionSort_str.o : selectionSort_str.c projectHeader.h
	gcc -c selectionSort_str.c

part2.o : part2.c projectHeader.h
	gcc -c part2.c

run:
	./part2

clean:
	rm part2 part2.o heapSort_int.o heapSort_str.o insertionSort_int.o insertionSort_str.o mergeSort_int.o mergeSort_str.o quickSort_int.o quickSort_str.o \
		radixSort_int.o radixSort_str.o searchAlgorithms.o selectionSort_int.o selectionSort_str.o \