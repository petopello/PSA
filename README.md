# Partial Sum Accumulation algorithm: Linear-time neighbor summation in Hamming space  
PSA is an optimized method for computing sum of neighbors in Hamming space. It is implemented in pure NumPy and works for arbitrary-dimensional arrays, even if they are non-symmetric.  

def SHN_PSA(space, q, r):
- space (list[number]): complete hamming space (all possible combinations of the elements in each dimension exist) flattened in a 1D array
- q (list[number]): number of possible elements in each dimension
- r (int): maximum Hamming distance for neighbor summation
- return (list[number]): hamming space with the sums of values of all neighbors within distance ≤ r, flattened in a 1D array

## Links  
- [google colab](https://colab.research.google.com/drive/1aENKd7eemGqmjdB8Y6ysxAx4BykguXUM?usp=sharing)  
- [post](https://sudapollismo.substack.com/p/partial-sum-accumulation-algorithm)
