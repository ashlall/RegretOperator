# Regret Minimizing Query
Regret Minimizing Query is a recently proposed query for multi-criteria decision making. There has been existing algorithms that efficiently implement the regret minimizing query but only for static dataset and "bigger is better" criteria. Our projects are an elaboration on those drawbacks of current regret minimizing query algorithms. One of our projects is about dynamically updating a result set returned by a regret minimizing query in a dynamic database. The other project focuses on solving for "lesser is better" criteria.

## Getting Started
#### Prerequisites
To understand more about the regret minimizing query, we refer readers to previously published work listed below.
* [Regret-Minimizing Representative Databases](http://www.vldb.org/pvldb/vldb2010/papers/R99.pdf) (this will give a solid definition and basic understanding)

The papers below are optional:
1. [k-Regret Queries with Nonlinear Utilities](http://www.vldb.org/pvldb/vol8/p2098-kesslerfaulkner.pdf)
2. [Efficient k-Regret query Algorithm with Restriction-free Bound for any Dimensionality](https://dl.acm.org/citation.cfm?id=3183713.3196903)
3. [Interactive Regret Minimization](http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.306.6067&rep=rep1&type=pdf)

The <b>References</b> section in those papers is also a good source to find more about the regret minimizing query.

#### Installing
Our algorithms and test files are coded in C++ and use the `glpk` package. Install the `glpk` package using the following command.

``
sudo apt-get install glpk-utils libglpk-dev 
``

## Running the tests
The instructions for running the tests for each project can be found inside the folders `DynamicCube` and `LIB`

## Authors
* <b>Dr. Ashwin Lall</b> - research mentor
#### Dynamic Updates for Regret-Minimization Query
* Hiep Phan
* Minh Do
#### Regret-Minimization with Monotonic Utility Functions
* Quang Nguyen
* Matthew Rinker
## License
Both of our projects are licensed under the GNU GENERAL PUBLIC LICENSE - see the <b>LICENSE</b> file for more details.

## Acknowledgments
We want to thank the following people who helped us made these projects possible
* Dr. Ashwin Lall for he was our research mentor
* Min Xie for her great help in generating ideas for the research
* The J.Reid & Polly Anderson Endowed Fund for funding this research