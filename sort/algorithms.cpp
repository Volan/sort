#include "algorithms.h"
#include <stdlib.h>
#include <math.h>
#include <limits.h>

void swap(int* arr, size_t i, size_t j) {
	int tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
}

int check(int* arr, size_t size, int order) {
	size_t i = 1;
	for (i = 1; i < size; ++i) {
		if (order == DESC) {
			if (arr[i - 1] < arr[i])
				return 1;
		}
		else {
			if (arr[i - 1] > arr[i])
				return 1;
		}
	}
	return 0;
}

void selection(int* arr, size_t size, int order) {
	size_t i, j, index;
	int temp;
	for (i = 0; i < size - 1; ++i) {
		index = i;
		for (j = i + 1; j < size; ++j) {
			if (order == DESC) {
				if (arr[index] < arr[j])
					index = j;
			}
			else {
				if (arr[index] > arr[j])
					index = j;
			}
		}
		if (index != i)
			swap(arr, index, i);
	}
}

void insertion(int* arr, size_t l, size_t r, int order) {
	size_t i, j;
	for (i = l + 1; i < r; ++i) {
		for (j = i; j > l; --j) {
			if (order == DESC) {
				if (arr[j - 1] < arr[j])
					swap(arr, j - 1, j);
				else
					break;
			}
			else {
				if (arr[j - 1] > arr[j])
					swap(arr, j - 1, j);
				else
					break;
			}
		}
	}
}

void insertion(int* arr, size_t size, int order) {
	insertion(arr, 0, size, order);
	//size_t i, j, flag;
	//for (i = 1; i < size; ++i) {
	//	flag = 1;
	//	for (j = i; flag == 1 && j > 0; --j) {
	//		if (order == DESC) {
	//			if (arr[j - 1] < arr[j])
	//				swap(arr, j - 1, j);
	//			else {
	//				flag = 0;
	//				continue;
	//			}
	//		}
	//		else {
	//			if (arr[j - 1] > arr[j])
	//				swap(arr, j - 1, j);
	//			else {
	//				flag = 0;
	//				continue;
	//			}
	//		}
	//	}
	//}
}

void merge(int* arr, int* aux, size_t l, size_t m, size_t r, int order) {
	size_t k = l, i, left = l, middle = m + 1, right = middle;

	for (i = l; i <= r; ++i)
		aux[i] = arr[i];
	
	while (k <= r)
	{
		if (right > r) {
			while (left < middle)
				arr[k++] = aux[left++];
			break;
		}
		if (left >= middle) {
			while (right <= r)
				arr[k++] = aux[right++];
			break;
		}

		if (order == DESC) {
			if (aux[left] > aux[right])
				arr[k++] = aux[left++];
			else
				arr[k++] = aux[right++];
		}
		else {
			if (aux[left] < aux[right])
				arr[k++] = aux[left++];
			else
				arr[k++] = aux[right++];
		}
	}
}

void mergeSort(int* arr, int* aux, size_t l, size_t r, int order) {
	if (r <= l)
		return;

	size_t middle = (r - l) / 2 + l;
	mergeSort(arr, aux, l, middle, order);
	mergeSort(arr, aux, middle + 1, r, order);
	merge(arr, aux, l, middle, r, order);
}

void merge(int* arr, size_t size, int order) {
	int *aux = (int*)malloc(sizeof(int) * size);
	if (aux == NULL)
		return;
	mergeSort(arr, aux, 0, size - 1, order);
	free(aux);
}


void dip(int* arr, size_t size, size_t index, int order) {
	size_t child = 2 * index + 1;
	size_t tmp = -1;
	if (child < size) {
		if (child + 1 < size) {
			if (order == DESC) {
				if (arr[child] < arr[child + 1])
					++child;
			}
			else {
				if (arr[child] > arr[child + 1])
					++child;
			}
		}
		if (order == DESC) {
			if (arr[index] < arr[child]) {
				swap(arr, index, child);
				dip(arr, size, child, order);
			}
		}
		else {
			if (arr[index] > arr[child]) {
				swap(arr, index, child);
				dip(arr, size, child, order);
			}
		}
	}
}

void heap(int* arr, size_t size, int order) {
	size_t middle = size / 2;
	int i, j;

	for (i = middle; i >= 0; --i)
		dip(arr, size, i, order == DESC ? ASC : DESC);

	j = size - 1;
	for (i = 0; i < size; ++i) {
		swap(arr, 0, j--);
		dip(arr, j + 1, 0, order == DESC ? ASC : DESC);
	}
}

size_t medianByThree(int* arr, int l, int r) {
	int indexes[3];
	int i, j;
	indexes[0] = rand() % (r - l) + l;
	do {
		indexes[1] = rand() % (r - l) + l;
	} while (indexes[1] == indexes[0]);
	do {
		indexes[2] = rand() % (r - l) + l;
	} while (indexes[2] == indexes[1] || indexes[2] == indexes[0]);

	for (i = 1; i < 3; ++i)
		for (j = i; j > 0; --j)
			if (arr[indexes[j - 1]] > arr[indexes[j]])
				swap(indexes, j - 1, j);
	return indexes[1];
}

size_t partition(int* arr, int l, int r, int order) {
	int p = l, i;
	//if (r - l >= 10)
	//	swap(arr, l, medianByThree(arr, l, r));
	//else
		swap(arr, l, rand() % (r - l) + l);
	
	int splitter = l + 1;
	for (i = l + 1; i <= r; ++i) {
		if (order == DESC) {
			if (arr[p] < arr[i])
				swap(arr, splitter++, i);
		}
		else {
			if (arr[p] > arr[i])
				swap(arr, splitter++, i);
		}
	}
	swap(arr, splitter - 1, p);
	return splitter - 1;
}

void quickSort(int* arr, int left, int right, int order) {
	if (right <= left)
		return;
	if (right - left <= 10)
		insertion(arr, left, right + 1, order);
	int p = partition(arr, left, right, order);
	quickSort(arr, left, p - 1, order);
	quickSort(arr, p + 1, right, order);
}

void quick(int* arr, size_t size, int order) {
	quickSort(arr, 0, size - 1, order);
}


void shuffle(int* arr, size_t size, int order) {
	int i, j, gap = size / 2;

	while (gap >= 1) {
		for (i = gap; i < size; ++i) {
			for (j = i; j >= 0 && j - gap >= 0; j -= gap) {
				if (order == DESC) {
					if (arr[j - gap] < arr[j])
						swap(arr, j - gap, j);
					else
						break;
				}
				else {
					if (arr[j - gap] > arr[j])
						swap(arr, j - gap, j);
					else
						break;
				}
			}
		}
		gap /= 2;
	}
}

void bubble(int* arr, size_t size, int order) {
	int flag = 1;
	size_t i;
	while (flag)
	{
		flag = 0;
		for (i = 1; i < size; ++i) {
			if (order == DESC) {
				if (arr[i - 1] < arr[i]) {
					swap(arr, i - 1, i);
					flag = 1;
				}
			}
			else {
				if (arr[i - 1] > arr[i]) {
					swap(arr, i - 1, i);
					flag = 1;
				}
			}
		}
	}
}

void counting(int* arr, size_t size, int order) {
	size_t c_size = RAND_MAX + 1, i, j;
	int* count = (int*)malloc(sizeof(int) * c_size);
	if (count == NULL)
		return;
	for (i = 0; i < c_size; ++i)
		count[i] = 0;
	for (i = 0; i < size; ++i)
		++count[arr[i]];

	j = 0;
	for (i = 0; i < c_size; ++i)
		while (count[i] != 0) {
			arr[j++] = i;
			--count[i];
		}
	free(count);
	return;
}