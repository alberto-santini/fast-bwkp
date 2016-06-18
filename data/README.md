## Black&White Knapsack Instances

### General remarks

These instances are obtained from Knapsack instances from the literature. The colours are assigned randomly, unless otherwise stated. In particular, for each knapsack instance, we generated two Black&White instances, by assigning the colours with probabilities 50-50% in one case, and 70-30% in the other. All instance filenames end, therefore, with the characters `_col_0.5.txt` in the first case, or `_col_0.3.txt` in the second case.

In general, the filename has the form `<I>_<n>_<R>_col_<p>.txt`. The number `n` denotes the number of items in the instance, `R` gives the range of coefficients (see below), and `I` is a progressive number, used to avoid collisions in filenames.

The format of the instances is as follows:

* The first line contains four integer numbers: total number of items (`n`), number of black items, number of white items, capacity of the bin.
* The second line contains `n` entries, one for each item. The `i`-th entry is `b` if the `i`-th item is black, or `w` if it is white.
* The third line contains `n` entries, giving the weight of each item (the weight is an integer number).
* The fourth line contains `n` entries, giving the profit of each item (the profit is an integer number).

### Type of instances

#### Instances from *Where are the hard knapsack problems?*

The paper *Where are the hard knapsack problems?* by David Pisinger introduces three sets of instances:

* **Instances with small coefficients**
  * **Uncorrelated** (`uncorrelated`). Item weights and profits are chosen randomly in the interval `[1,R]` and no correlation exists between them.
  * **Weakly Correlated** (`weakly_correlated`). Item weights are chosen randomly in the interval `[1,R]`. For each item `j`, the profit `p_j` is chosen randomly in the interval `[w_j - R/10, w_j + R/10]` such that `p_j >= 1`.
  * **Strongly Correlated** (`strongly_correlated`). Item weights are chosen randomly in the interval `[1,R]`. For each item `j`, the profit is set as `p_j = w_j + R/10`.
  * **Inverse Strongly Correlated** (`inverse_strongly_correlated`). Item profits are chosen randomly in the interval `[1,R]`. For each item `j`, the weight is set as `w_j = p_j + R/10`.
  * **Almost Strongly Correlated** (`almost_strongly_correlated`). Item weights are chosen randomly in the interval `[1,R]`. For each item `j`, the profit is chosen randomly in the interval `[w_j - R/10 - R/500, w_j - R/10 + R/500]` such that `p_j >= 1`.
  * **Subset Sum** (`subset_sum`). Item weights are chosen randomly in the interval `[1,R]`. For each item `j`, the profit is equal to the weight.
  * **Similar Weights** (`similar_weights`). Item weights are chosen randomly in the interval `[100 000, 100 100]` and profits are chosen randomly in the interval `[1, 1000]`.
* **Instances with large coefficients** are obtained in the same way as the previous class of instances, but using very high numbers for the coefficients (i.e., using a very high of value of `R`). The folders containing these instances end in `_lc`.
* **Difficult Instances with Small Coefficients**
  * **Span Instances** These instances are denoted as `span(2,10)` in the paper. The instances have been created as follows: given 2 starting items (called the *spanner items*), all other items are generated as their multiples, where the multiplicative factor is between 1 and 10. The two spanner items can be generated according to three different distributions, therefore giving the three sets of instances: `uncorrelated_span`,  `weakly_correlated_span`, and `strongly_correlated_span`.
  * **MSTR Instances** (`mstr`). These instances (Multiple Strongly-Correlated) are denoted as `mstr(3R/10, 2R/10, 6)` in the paper. They are made up by items drawn from two strongly-correlated sets with items of weights randomly distributed in `[1,R]`. The profits of the items are determined in the following way: if the weight of item `j` is divisible by 6, then `p_j = w_j + 3 * R / 10`; otherwise, `p_j = w_j + 2 * R / 10`.
  * **Pceil Instances** (`pceil`). These instances (Profit Ceiling) are denoted as `pceil(3)` in the paper. The weight of the items are distributed randomly in `[1,R]` and the profit of item `j` is set to `p_j = 3 * ceil(w_j / 3)`; therefore, all profits are multiples of 3.
  * **Circle Instances** (`circle`). These instances are denoted as `circle(2/3)` in the paper. The weight of the items are distributed randomly in `[1,R]`. The profit of item `j` is set to `p_j = 2/3 * sqrt(4 * R^2 - (w_j - 2 * R)^2)`; therefore, the function that associates an item's profit to its weight draws the arc of an ellipsis.

For each type of instance with small coefficients, we have 8 sizes: 50, 100, 200, 500, 1000, 2000, 5000, 10000 items. For each size, there are two possible values for `R`: 1000 and 10 000. For each of the 16 combinations of size and `R`, we use all the 100 Knapsack instances provided by David Pisinger. Since we colour each instance in two ways, we end up with a total of `16 * 100 * 2 = 3200` instances for each type. The instances `similar_weights` are an exception as they are only available for `R = 1000` and therefore only give 1600 Black&White Knapsack instances.

For each type of instance with large coefficients, we have 8 sizes: 50, 100, 200, 500, 1000, 2000, 5000, 10000 items. For each size, there are three possible values for `R`: 100 000, 1 000 000, and 10 000 000. For each of the 24 combinations of size and `R`, we use all the 100 Knapsack instances provided by David Pisinger. Since we colour each instance in two ways, we end up with a total of `24 * 100 * 2 = 4800` instances for each type. The instances `similar_weights_lc` are an exception as they are only available for `R = 10 000` and `R = 1 000 000` and therefore only give 3200 Black&White Knapsack instances.

For each type of difficult instance with small coefficients, we have 9 sizes: 20, 50, 100, 200, 500, 1000, 2000, 5000, and 10000 items. (`R` is always set to 1000). For each size, we use all the 100 Knaspack instances provided by David Pisinger. Since we colour each instance in two ways, we end up with a total of `9 * 100 * 2 = 1800` instances for each type.

In each instance, the capacity is the original one from the Knapsack instance, which is calculated as `c = h / 101 * sum(w_j)` where `h` is a progressive number going from 1 to 100 (corresponding to each of the 100 base instances).

#### Instances from *Dynamic Programming and Strong Bounds for the 0-1 Knapsack Problem*

The paper *Dynamic Programming and Strong Bounds for the 0-1 Knapsack Problem* by Martello, Pisinger, Toth introduces several types of instances:

* **Avis Subset Sum** (`avis_subset_sum`). Item weights and profits are equal and are set to `w_j = p_j = n * (n+1) + j`. The knapsack's capacity is `c = n * (n+1) * floor((n-1) / 2) + n * (n-1) / 2`.
* **Avis Knapsack** (`avis_knapsack`). Item profits are generated randomly in `[1, 1000]` and the weight of item `j` is set as `w_j = n * (n+1) + j`. The knapsack's capacity is `c = n * (n+1) * floor((n-1) / 2) + n * (n-1) / 2`.
* **Collapsing Knapsack** (`collapsing_knapsack`). These were originally instances of the Collapsing Knapsack Problem (CKP). In *Simple but efficient approaches for the collapsing knapsack problem*, Pferschy, Pisinger and Woeginger have shown that every instance of the CKP can be turned into a corresponding Knapsack instance. The instances are generated as in *An exact algorithm for the 0-1 collapsing knapsack problem* by Fayard and Plateau, using profits in `[1, 300]`, weights in `[1,1000]` and capacities in `[1, 10 000]`.
* **Bounded Strongly Correlated** (`bounded_strongly_correlated`). These were originally instances for the Bounded Knapsack Problem (BKP). In *Knapsack Problems. Algorithms and Computer Implementations.*, Martello and Toth have shown that every instance of the BKP can be turned into a correponding Knapsack instance. The BKP instances are generated with weights in `[1, 1000]`, and profits set to `p_j = w_j + 1000`. The capacity is calculated as `c = h / 101 * sum(w_j)` where `h` is a progressive number going from 1 to 100 (corresponding to the 100 instances generated).
* **No Small Weights** (`no_small_weights`). These instances have weights generated in `[500, 1000]` and profits in `[w_j - 100, w_j + 100]` such that `p_j >= 1`.

We do not have the original instances used in *Dynamic Programming and Strong Bounds for the 0-1 Knapsack Problem*, and instead used a generator for these instances, provided by David Pisinger.

For each instance type, we considered four values of `n`: 50, 100, 500, 1000. We generated 100 instances for each type and each `n` and have therefore 400 base Knapsack instances for each of the 5 types, giving 800 Black&White Knapsack instances per type.

### Number of instances: summary

| Instance type                              | Total number of B&W Knapsack instances |
| :----------------------------------------- | -------------------------------------: |
| uncorrelated                               | 3200                                   |
| weakly_correlated                          | 3200                                   |
| strongly_correlated                        | 3200                                   |
| inverse_strongly_correlated                | 3200                                   |
| almost_strongly_correlated                 | 3200                                   |
| subset_sum                                 | 3200                                   |
| similar_weights                            | 1600                                   |
| uncorrelated_lc                            | 4800                                   |
| weakly_correlated_lc                       | 4800                                   |
| strongly_correlated_lc                     | 4800                                   |
| inverse_strongly_correlated_lc             | 4800                                   |
| almost_strongly_correlated_lc              | 4800                                   |
| subset_sum_lc                              | 4800                                   |
| similar_weights_lc                         | 3200                                   |
| uncorrelated_span                          | 1800                                   |
| weakly_correlated_span                     | 1800                                   |
| strongly_correlated_span                   | 1800                                   |
| mstr                                       | 1800                                   |
| pceil                                      | 1800                                   |
| circle                                     | 1800                                   |
| avis_subset_sum                            | 800                                    |
| avis_knapsack                              | 800                                    |
| collapsing_knapsack                        | 800                                    |
| bounded_strongly_correlated                | 800                                    |
| no_small_weights                           | 800                                    |