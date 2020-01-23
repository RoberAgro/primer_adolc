


### Summary of ADOL-C official demos

- Speelpening (speelpenning.cpp)
Compute the derivatives of \\(f(x) = \prod_{i=0}^{n-1} x_{i}  \\)
The example uses the gradient() and hessian() drivers that are suitable for multivariate scalar functions (useful for unconstrained or bound-constrained optimization)

- Power example (powerexam.cpp)
Compute the derivatives of \\(f(x) = x^n \\) for interger \\(n\\)
The derivatives are computed by forward AD and reverse AD using low-level functions.
The function power can be replaced by any real function to see if the forward and reverse are consistent and to check against analytic values if they are known.

- Determinant example (detexam.cpp)
Computes the a determinant by recursive expansion along rows
The example shows that when there are many for independent than dependent variables the reverse mode is more suitable


- ODE example (odexam.cpp)
Solves the Robertson test problem (stiff system of ODEs arising from a three-specie chemical reaction)
Uses methods forode() reverse() and accode()


- LU factorization example (luexam.cpp)
computation of LU factorization with pivoting
Uses zos_forward() and fos_reverse()


There are also 4 examples for the traceless mode

It is also possible to create the `additional_examples` folder at compile/instalation time to get examples for more advanced functionality