#### Fast-BWKP

This project contains Work-in-Progress code for the Black and White Knapsack Problem.

* Folder `data` contains a test dataset based on Pisinger's hard knapsack instances.
* Folder `src` contains the source code.

##### Building

1. Clone this repository:
  * Either clone via git `git clone https://github.com/alberto-santini/fast-bwkp.git`.
  * Or get the zipped version of the master branch: `wget https://github.com/alberto-santini/fast-bwkp/archive/master.zip && unzip master.zip`.
2. Create a build directory:
  1. `cd fast-bwkp`
  2. `mkdir build`
  3. `cd build`
3. Run CMake: `cmake -DCPLEX_ROOT_DIR=<path>`
  * `<path>` is such that the following file exists: `<path>/cplex/include/ilcplex/cplex.h`.
  * Additionally, you might tell cmake if you want a debug build (slower, not optimised, with debug symbols) by using `-DCMAKE_BUILD_TYPE=Debug` or a release build (faster, O3-optimised, without debug symbols) by using `-DCMAKE_BUILD_TYPE=Release`.
4. Run make: `make`

##### License

This software is distributed under the GNU General Public License v3, as detailed in `LICENSE.txt`.