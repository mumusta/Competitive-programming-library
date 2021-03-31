// [Binary Search]

// if infinite loop happend
// we can change mid to start + (end - start + 1) / 2
// or use 7alawany technique :D

int binary_search_first(int start, int end, int target){
    while (start < end){
        int mid = start + (end - start) / 2;
        if (F(mid) < target) start = mid + 1;
        else if (F(mid) > target) end = mid - 1;
        else end = mid;
    } return start;
}

int binary_search_last(int start, int end, int target){
    while (start < end){
        int mid = start + (end - start) / 2;
        if (F(mid) < target) start = mid + 1;
        else if (F(mid) > target) end = mid - 1;
        else start = mid;
    } return start;
}

// we always use 7alawany technique

double binary_search_double(double start, double end, double target){
    for (int i = 0 ; i < 600; i ++){ // iterate 200-600 iteration
        double mid = start + (end - start) / 2;
        if (F(mid) < target) start = mid;
        else end = mid;
    } return start;
}

// [Ternary Search]

// we always use 7alawany technique

double ternary_search_double(double left, double right){
    for (int i = 0 ; i < 600; i ++){ // iterate 200-600 iteration
        double g = left + (right - left) / 3, h = left + 2 * (right - left) / 3;
        if (F(g) < F(h)) right = h; // use > if F(x) increase then decrease
        else left = g;
    } return left;
}

// in integer ternary search we use while(right - left > 3) and then use 7alawany technique

