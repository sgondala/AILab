#include <iostream>
#include <cmath>

void training(int** augmentedNegatedX, int* weights, int numInputs) {
  int numRows = pow(2, numInputs);
  int iter = 0;
  while(true) {
    ++iter;
    for(int i = 0; i <= numInputs; ++i) {
      std::cout << weights[i] << ' ';
    }
    std::cout << '\n';

    int i;
    for(i = 0; i < numRows; ++i) {
      int product = 0;
      for(int j = 0; j <= numInputs; ++j) {
        product += augmentedNegatedX[i][j] * weights[j];
      }
       if(product <= 0) {
         for(int j = 0; j <= numInputs; ++j) {
           weights[j] += augmentedNegatedX[i][j];
         }
         break;
       }
      /*
      float val = 1/(1+exp(-1*product));
      float error = val-1;
      std::cout << "error " << error << std::endl;
      if(error > 0.1) {
        for(int j = 0; j <= numInputs; ++j) {
          weights[j] += 1*error*val*(1-val)*augmentedNegatedX[i][j];
        }
        break;
      } 
      */
    }
    if(i == numRows) {
      std::cout<< iter << '\n';
      return;
    }
  }
}

int main() {
  int numInputs;
  std::cin >> numInputs;
  int numRows = pow(2,numInputs);
  int** xvector = new int*[numRows];
  for(int i = 0; i < numRows; ++i) {
    xvector[i] = new int[numInputs];
  }
  int* yvector = new int[numRows];
  for(int i = 0; i < numRows; ++i) {
    for(int j = 0; j < numInputs; ++j) {
      std::cin >> xvector[i][j];
    }
    std::cin >> yvector[i];
  }
  int** augmentedNegatedX = new int*[numRows];
  for(int i = 0; i < numRows; ++i) {
    augmentedNegatedX[i] = new int[numInputs+1];
  }
  for(int i = 0; i < numRows; ++i) {
    bool b = (yvector[i] == 0);
    augmentedNegatedX[i][0] = (b ? 1 : -1);
    for(int j = 1; j <= numInputs; ++j) {
      augmentedNegatedX[i][j] = xvector[i][j-1] * (b ? -1 : 1);
    }
  }

  int* weights = new int[numInputs+1];
  for(int i = 0; i <= numInputs; ++i) {
    weights[i] = 0;
  }
  training(augmentedNegatedX, weights, numInputs);
}
