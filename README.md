# Linear Regression using Xilinx Virtex-7 FPGA

## Introduction:
Implemented Linear Regression algorithm using Xilinx Virtex-7 FPGA. I studied two architectures for our project one with loop unrolling and one without it. Let’s discuss both implementation. 
There are two for loops, one to control number of iterations to perform before converging and other to compute mean square error with complete dataset. In this example we used 576 elements in dataset and 2000 iterations to converge a result. Often times it could be less than this but we took this as a worst case scenario. 
The linear regression algorithm is feed in with data from memory. It will compute the result and update the weight accordingly in each iteration. After 2000 iterations it is supposed to have found the real weights and pass it as output. The Figure 3 gives an idea of how in each step values are calculated and passed on to next stage. 

## Optimization:
I performed below optimization to improve the throughput of the system. We did so by unrolling the loop. By doing so we resulted in 4X faster throughput at the cost of 1.5X more DSP core blocks. 

## Performance comparison at Very High Level: 
It may seem little vague for implementing this algorithm in FPGA and one would argue that this type of algorithm can be implemented in C++ and it won’t be much of a problem. So, we studied the performance of this algorithm in hardware in FPGA and also in Laptop. Even though the FPGA runs at 20X slower clock it can comfortably yield results 8X faster than Laptop. 

## Conclusion:
FPGA and other parallel architectures lead us to achieve more throughput than traditional microprocessors. So the whole industry is trying to leverage these for machine learning algorithms to achieve faster throughput. 
