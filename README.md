# MiniTree
A light weight decision tree based on the CHAID method.
## Introduction
The objectives of this work are simple:
* Understand how a learning algorithm works, how to develop it and use it.
* Get a decision tree algorithm as light as I want for various applications, such as simple AIs and fast data analysis
To do so I decided to develop an algorithm based on a very classical method: the CHAID method. It's not the best method ever developed, but as described later, it's an easy to interpret method, and not too complicated to implement.
## The method
Taking a finite number of parameters and an output.
The objective of the decision tree is to produce parameters groups the most homogeneous possible, therefore, to separate the most independent ones. After each separation, the new groups are again separated on the same principle until the final decision on the parameter to predict can be reliably taken.
The CHAID method uses the chi-squared test of independence. The determination of this chi-square allows determine whether there is a significant association between two groups.
The cut value for continuous variables is chosen optimizing the chi-squared value at its maximum.
## Current status
The development is still under heavy work: It's able to read data and output to learn and construct a full tree based on the CHAID method. Some tests are needed to check out the calculation, the structure itself being already validated.
### Still to do:
- Obtaining an output predation from a parameter set.
- Managing continuous and discreet output (weight).
- Testing learning ageing (slow weight decrease) for adaptation, the goal is to slowly forget not reinforced behaviors.
