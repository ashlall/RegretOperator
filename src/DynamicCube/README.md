# Dynamic Updates for Regret-Minimizing Query
This project is about dynamically updating a result set returned by a regret-minimizing query in a dynamic databases, i.e., insertion and deletion of points occur frequently. 

## Getting Started
For basic understanding of the regret-minimizing query and required installation, please read the `README` in the root directory.

For more information on this project, please read the paper included in this folder.

## Running the tests
Our default values for ``n, d, k`` are as follow: 
``
n = 10000,
d = 4,
k = 30,
``

Note: This folder already has results of running the test files. If you decide to run the test files yourself, the results in folder `Results` will be overwritten.
#### Compiling the files
In the `DynamicCube` folder, type `make` in the command line to compile all files or use ``make <test>`` to compile a test file individually. For example, ``make varyn`` to compile vary-n test file.

#### Vary-m
To run vary-m tests, use the following command: ``./varym a <k> <starting-m> <number of tests>``.

For example, ``./varym a 30 0 10`` will test `m` values from `0.0` to `0.9` (10 tests, each proceeding test increase `m` by `0.1`).
#### Vary-n
To run vary-n tests, use the following command: ``./varyn a <k> <test-insert> <test-delete> <m>``. The values for `n` are `100, 1000, 10000`.

For example, ``./varyn a 30 1 0 0.3`` will run vary-n insertion tests for anti-correlated data with `k=30` and `m=0.3`.

#### Vary-d
Similar to vary-n, use the following command: ``./varyd a <k> <test-insert> <test-delete> <m>``. The values for `d` are `2, 3, 4, 5, 6`.

#### Vary-k
To run vary-k tests, use the following command: ``./varyk a <test-insert> <test-delete> <m>``. The values for `k` are `20, 25, 30, 35, 40`.

#### Real-world datasets
To run tests on real-world datasets, you first need to compile all the files using `make` or just the files for testing real-world datasets using `make real`.

To generate test results for real-world datasets, use the following command: ``./testrealdata <input> <K> <m>``. Options for `<input>` include: `nba`, `color`, `house`, `stock`.

For example, to test the `color` dataset with `k = 30`, `m = 0.3`, use the following command:

``./testrealdata color 30 0.3``

## Generating plots
Compile the files if you haven't done so. To compile only files for plotting, use `make makeplot`.

To generate a plot for a specific test, you need the corresponding valid test result. For example, if you want to plot vary-n insertion, you need the file `varyn.log` in folder `Results`. The log file is already provided in this repository, but you can also generate it by running the vary-n test.  

#### For vary-n, vary-d, vary-k tests
To generate the plots for vary-n, vary-d or vary-k, use the following command:

`./makeplot <test> <test type>`

Options for `<test>` include: `n`, `d`, `k`. They are for vary-n, vary-d and vary-k respectively. 

Options for `<test type>` include: `i` for insertion and `d` for deletion.

For example, to generate the plots for vary-n insertion test, use: `./makeplot n i`. This will generate `varyn_rr.eps` and `varyn_rt.eps` in the `Plots` folder. They are the plots for average maximum regret ratio and running time, respectively.

#### For vary-m test
To generate the plots for vary-m, use: `./makeplot varym`.

#### For real-world datasets
To generate the plots for all 4 real-world datasets (`nba`, `color`, `house`, `stock`), use `./makeplot realdataset`. This will generate the average regret ratio plot `realdata_rr.eps` and running time plot `realdata_rt.eps` in the `Plots` folder. Note that this command requires valid results for all 4 datasets listed above. 