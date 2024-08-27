# Working with Romain's solver

## Compile
`make` does the thing.

## Run

+ Example 1: Solve Rifki20 with 21 nodes, service time to 0, time steps of 6 minutes (small) -> `./bin/tdtsptw solve ACS pw_constant 21 ./benchmarks/Rif20/sigma=100/n=21/cost_100_6_21_1.txt benchmarks/Rif20/TW_Ari18/n21_l6_sigma100/beta_50/tt01_tw04.tw benchmarks/Rif20/s/21_0`

+ Example 2: Perform preprocessing: `./bin/tdtsptw preprocess pw_constant 21 ./benchmarks/Rif20/sigma=100/n=21/cost_100_6_21_1.txt benchmarks/manual_benchmarks/TWs/timewindow_21_2.txt benchmarks/Rif20/s/21_0`

### Note

##### Addition of a final node
Romain adds a final node that represent the return depot. This allows him to consider that start depot node 0 has the following TW in a makespan objective context: `0 : [0;0]`. Hence, there are not 1 but 2 nodes associated with the depot, so for $n=21$ nodes including 1 depot, Romain has matrices of size $n+1=22$ nodes!
