void qSort(int arr[], int begin, int end) {
    if (end - begin < 1)
        return;

    int pivot = arr[end];

    int i_left = begin, i_right = end;
    while (i_left < i_right) {
        while (arr[i_left] <= pivot && i_left < i_right)
            i_left++;
        while (arr[i_right] > pivot && i_left < i_right)
            i_right--;

        if (i_left != i_right) {
            int temp = arr[i_left];
            arr[i_left] = arr[i_right];
            arr[i_right] = temp;
        }
    }

    qSort(arr, begin, i_left - 1);
    qSort(arr, i_right, end);
}

