//double FindMaxRec(const double arr[], int low, int high, int maxInd) {
//    if (low >= high) {
//        return arr[maxInd];
//    }
//    if (arr[low] > arr[maxInd]) {
//        return FindMaxRec(arr, low + 1, high, low);
//    }
//    else {
//        return FindMaxRec(arr, low + 1, high, maxInd);
//    }
//}