

// [Pascal Triangle]

void pascal_triangle(){
    c[1][1] = 1;
    for (int i = 0 ; i <= N ; i++){
        for (int ii = 0 ; ii <= i ; ii ++){
            if (ii == 0 || ii == i) c[i][ii] = 1;
            else c[i][ii] = (c[i-1][ii-1]+c[i-1][ii]);
        }
    }
}

// [Max 1D Range Sum]

int main(){

  int n = 9, A[] = { 4, -5, 4, -3, 4, 4, -4, 4, -5 };   // a sample array A
  int running_sum = 0, ans = 0;
  for (int i = 0; i < n; i++)                                       // O(n)
    if (running_sum + A[i] >= 0) {  // the overall running sum is still +ve
      running_sum += A[i];
      ans = max(ans, running_sum);          // keep the largest RSQ overall
    }
    else        // the overall running sum is -ve, we greedily restart here
      running_sum = 0;      // because starting from 0 is better for future
                           // iterations than starting from -ve running sum
  printf("Max 1D Range Sum = %d\n", ans);                    // should be 9
}

