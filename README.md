# Overview
This project aims to investigate the characteristics of gap-sequences for the Shellsort algorithm, and the impact of experimentation with the increments of those sequences. Many empirically derived sequences - which the best performing ones are - seem to approach ever closer to an optimal gap-sequence formula yet the question remains an open one. This project asks if the optimal sequence is not so obvious because 
it does not belong to one elusive magic formula, but rather to an adaptive, self-tuning sequence proportional to array size (N), an optimal gap value perhaps better flexible rather than fixed for large bounds of N.

While the full task of analyising a wide enough set of N at each increment for many values at many different densities and optimal pass to gap-value ratios is unfeasible for large ranges of N, a similar in concept 
substitution is made. For some well-researched, established gap-sequences, their properties are examined and understood to the best capability, and their distinct values probed for any small changes improving performance at the 
specific lower and higher bounds of N for that value in that sequence. The latest formulas may perform so well because they have balanced the value density to gap size, but might they be further improved by balancing gap sizes into N, 
until one balance outweighs the other. This concept and other numerical factors are explored. 

## Configurations used although later versions may work
- Eclipse version 4.28.0 – Integrated development environment 
- C - GCC version 6.3.0 
- Anaconda navigator version 2.6.4 - Distribution platform 
- Jupyter notebook version 7.2.2 - web application utilised for python coding
- mt19937ar.c and mt19937ar.h source files available at <https://www.math.sci.hiroshima-u.ac.jp/m-mat/MT/MT2002/emt19937ar.html>

### Dependencies
None

#### Methodology
To obtain results that probe researched or experimental sequences for improvements or patterns in general, including what may exhibit faults for a gap sequence, based on the distinct k-increment for sequences that “activates” for certain array size bounds.
Within the source code established sequences are translated into C, and one is analysed at a time. Many values are tweaked throughout the code to obtain different analyses, such as increment multiplier (for scaled change across the sequence), number of repetitions
for data averaging, number of seeds used for PSRNG, array upper and lower bounds, analysing empirical or formulaic k values, trough and peak limits with an "iterationCounter" for what will be the graphical wave of results and setting it such that once it reaches those
limits it flips the "incrementBumper" that is making the small changes to the increments, hence a wave. Either fixed values of N are compared across sequences or increasing N is viewed for focusing on individual sequence performance. 
These results are saved to appropriately named files for Python tool graphing.

#### Usage
Run the desired algorithm either fixed value or formulaic, if formulaic "initialiseK" method must have the correct formula inserted, if using fixed increments "increments" array need only contain desired increments commenting out the formulaic increment lines. If using
fixed values of N "arrayLengths" need contain these values and for-loop on line 180 is used over for-loop at 183. 5 seeds and 100 loops per sort are used for data averaging hence 500 division value for overall values per sort on line 277 which writes to save file. Ensure
appropriate file name on line 159. Lines 164 and 274 to be uncommented to include percentage change value to save file.

##### Author 
https://github.com/MuhJava
