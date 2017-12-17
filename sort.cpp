#include<iostream>

using namespace std;


void output(int list[], int n){
    for(int i=0; i<n; i++){
        cout << list[i] << ", ";
    }
    cout << endl;
}

void bubbleSort(int list[], int n){
    /*冒泡排序*/
    for(int i=0; i<n-1; i++){
        for(int j=i+1; j<n; j++){
            if(list[i] > list[j]){
                swap(list[i], list[j]);
            }
        }
        output(list, n);
    }
}

void orientedBubbleSort(int list[], int n){
    /*定向的冒泡排序，比上边的冒泡排序性能稍微好点*/
    int left = 0;
    int right = n-1;
    while(left < right){
        for(int i=left; i<right; i++){
            if(list[i] > list[right]){swap(list[i], list[right]);}
        }
        right --;
        for(int j=right; j>left; j--){
            if(list[j] < list[left]){swap(list[j], list[left]);}
        }
        left ++;
        output(list, n);
    }
//    output(list, n);
}

void selectionSort(int list[], int n){
    /*选择排序*/
    for(int i=0; i<n-1; i++){
        int min = i;
        for(int j=i; j<n; j++){
            if(list[j] < list[min]){ min = j;}
        }
        swap(list[i], list[min]);
        output(list, n);
    }
}

void insertionSort(int list[], int n){
    /*插入排序*/
    int *sortedList = new int[n];
    sortedList[0] = list[0];
    for(int i=1; i<n; i++){
        int j = i;
        while(j >= 0 && sortedList[j] > list[i]){
            sortedList[j+1] = sortedList[j];
            j--;
        }
        sortedList[j+1] = list[i];
        output(sortedList, i+1);
    }
}

int quickSort_partition(int list[], int left, int right){
    //快速排序的分类方法
    int pivot = right;
    int tail = left - 1;
    for(int i=left; i<right; i++){
        if(list[i] < list[pivot]){
            swap(list[++tail], list[i]);
        }
    }
    swap(list[tail+1], list[pivot]);
    return tail + 1;
}

void quickSort(int list[], int left, int right, int n){
    output(list,n+1);
    //快速排序
    if(right-left < 1){
        return;
    }
    int index = quickSort_partition(list, left, right);
    quickSort(list, left, index-1, n);
    quickSort(list, index+1, right, n);
}

int radixSort_num_in_position(int num, int position){
    //返回数字num从右往左数第position个数字
    int temp = 1;
    for(int i=0; i<position-1; i++){
        temp = temp*10;
    }
    return (num/temp)%10;
}

void radixSort(int list[], int n, int max){
    //基数排序
    int box[30][30] = {0};
    for(int pos=1; pos<max; pos++){
        for(int i=0; i<n; i++){
            int num = radixSort_num_in_position(list[i],pos);
            box[num][++box[num][0]] = list[i];
        }
        int counter = 0;
        for(int j=0; j<=10; j++){
            for(int i=1; i<=box[j][0]; i++){
                list[counter] = box[j][i];
                counter ++;
            }
            box[j][0] = 0;
        }
        output(list, n);
    }
}

void mergeSort_merge(int list[], int left, int mid, int right){
    //归并排序的归并方法
    int ol = left;
    int len = right - left + 1;
    int *temp = new int[len];
    int index_1 = left;
    int index_2 = mid+1;
    int index_0 = 0;
    while(index_1 <= mid && index_2 <= right){
        temp[index_0++] = list[index_1] >= list[index_2] ? list[index_2++] : list[index_1++];
    }
    while(index_1 <= mid){
        temp[index_0++] = list[index_1++];
    }
    while(index_2 <= right){
        temp[index_0++] = list[index_2++];
    }
    for(int i=0; i<len; i++){
        list[left++] = temp[i];
    }
    for(int i=0; i<len; i++){
        cout << temp[i] << ", ";
    }
    cout << endl;
}

void mergeSort(int list[], int left, int right){
    //归并排序
    if(left == right){
        return;
    }
    int mid = (left+right)/2;
    mergeSort(list, left, mid);
    mergeSort(list, mid+1, right);
    mergeSort_merge(list, left, mid, right);
}

int main(){
    //测试数据
    int len = 12;
    int list[12] = {56,45,75,23,12,755,0,433,231,283,81,823};
    //排序方法
//    bubbleSort(list, len);
//    (list, len);
//    selectionSororientedBubbleSortt(list, len);
//    insertionSort(list, len);
//    quickSort(list, 0, len-1, len-1);
//    output(list,len);
    mergeSort(list, 0, len-1);
    output(list,len);
//    radixSort(list,len, 4);
//    output(list, len);
    return 0;
}