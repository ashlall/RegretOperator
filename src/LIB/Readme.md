# Regret-Minimization with Monotonic Utility functions
This folder contains the source code for the implementation of the ``lesser is better`` (LIB) problem. In this folder, we will use multiple file to test the regret ratio of the ``Cube``, ``Sphere`` and ``ImpGreedy`` algorithm when applying our LIB utility class. 

## Getting started:
In order to understand the purpose and idea of the LIB algorithm, please refer to the paper:
* Regret-Minimization with Monotonic Utility functions

## Running the test:
Run the ``Makefile``
### Dataset:
We will generate our dataset through the ``generatedata.cpp`` file and the ``split.cpp`` file. 
##### generatedata.cpp:
usage:

``
./generatedata <Dimensions> <Distribution> <NumberofPoints> <Filename>
``

``
Distribution syntax: E(qually), A(nticorrelated), C(orrelated)
``

This file generate dataset of ``N`` points, ``D`` dimensions with a specific data distribution.

##### split.cpp:
usage:

``
./split filename num-split 
``
or 

``
./split filename num-split file-prefix
``

This file split a datafile into equally separated dataset. This allow us to test on different independence dataset.

### Vary:
Our main file will be 5 vary files ``vary-N``, ``vary-M``, ``vary-db`` and ``vary-D``. Each of these file test the regret ratio of the three algorithm Cube, Sphere and ImpGreedy by changing one variables and fixing others. The default value will be: ``N = 10000``, ``D = 4``, ``db = 2``, ``M = 0.2`` and ``K = 20``

#### vary-N.cpp
usage

``
./vary-N file-prefix K M db
``

This file change the ``N`` variable, the number of points in the database. We will be able to output 2 files. The log file and the ``varyN-e4-k20-db2`` which contains the running times and the regret ratio on each algorithm.  


#### vary-D.cpp
usage;
``
./vary-D file-prefix K 
``

This file change the ``D`` variable, the number of dimension in the database. We will be able to output 2 files. The log file and the ``varyD-e-N10000-k20`` which contains the running times and the regret ratio on each algorithm.  

#### vary-K.cpp
usage

``
./vary-K file-prefix db M
``

This file change the ``K`` variable, the number of points of the result subset. We will be able to output 2 files. The log file and the ``varyK-e4-db2`` which contains the running times and the regret ratio on each algorithm.  

#### vary-M.cpp
usage

``
./vary-M file-prefix K db
``

This file change the ``M`` variable, the number of points in the database. We will be able to output 2 files. The log file and the ``varyM-e4-k20-N100000-db2`` which contains the running times and the regret ratio on each algorithm.  

#### vary-db.cpp
usage;
``
./vary-db file-prefix K 
``

This file change the ``db`` variable, the number of points in the database. We will be able to output 2 files. The log file and the ``varydb-e4-k20`` which contains the running times and the regret ratio on each algorithm.  

### Plot:
The ``makeplot.cpp`` takes in one of the output file from the vary program and plot the regret ratio
usage

``
./makeplot [N|D|K|M|db] input-file ouput-file 
``

or 

``
./makeplot [N|D|K|M|db] input-file output-file times
``



