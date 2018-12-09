# MPSiS 2018/2019
# Model 1a

/* Number of variables */
param n, integer, >= 1;

/* Set of variable indices, up to 'n' */
set I, default {1..n};

/* Decision variables */
var x{i in I} >= 0;

/* Objective function 'z' */
maximize z: x[1] + 3*x[2];

/* Constraints */

s.t. C1: -x[1] + x[2] <= 1;
s.t. C2:  x[1] + x[2] <= 2;

/* Input data */

data;

param n := 2;

end;
