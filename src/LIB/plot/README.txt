#Running makeplot
g++ -o makeplot makeplot.cpp

#makeplot for regret ratio of equally distributed data 
./makeplot N varyn-e4-k20-db2 plot-varyN
./makeplot M varyM-e4-k20-N10000-db2 plot-varyM
./makeplot K varyK-e4-db2 plot-varyK
./makeplot D varyD-e-N10000-k20 plot-varyD 
./makeplot db varydb-e6-k20 plot-varydb

#makeplot for time of equally distributed data
./makeplot N varyn-e4-k20-db2 plot-varyN t
./makeplot M varyM-e4-k20-N10000-db2 plot-varyM t
./makeplot K varyK-e4-db2 plot-varyK t
./makeplot D varyD-e-N10000-k20 plot-varyD t 
./makeplot db varydb-e6-k20 plot-varydb t

#makeplot for regret ratio of anti-correlated data 
./makeplot N varyn-a4-k20-db2 plot-varyN-a
./makeplot M varyM-a4-k20-N10000-db2 plot-varyM-a
./makeplot K varyK-a4-db2 plot-varyK-a
./makeplot D varyD-a-N10000-k20 plot-varyD-a 
./makeplot db varydb-a6-k20 plot-varydb-a

#makeplot for time of anti-correlated data 
./makeplot N varyn-a4-k20-db2 plot-varyN-a t
./makeplot M varyM-a4-k20-N10000-db2 plot-varyM-a t 
./makeplot K varyK-a4-db2 plot-varyK-a t
./makeplot D varyD-a-N10000-k20 plot-varyD-a t 
./makeplot db varydb-a6-k20 plot-varydb-a t

#makeplot regret ratio of nba data
./makeplot K nba-varyK-NBA-db4 plot-NBAvaryK

