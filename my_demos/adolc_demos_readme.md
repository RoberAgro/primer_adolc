# ADOL-C demos guide

This directory contains some well-documented demonstration projects to get started with ADOL-C.

We suggest this order to explore the demos:



###1. demo_siso

This example shows how to compute the first derivatives of a single-input single-output function in forward and reverse modes.
The example selected is the simple scalar function:

<math display="block">
  <mi>f</mi>
  <mo stretchy="false">(</mo>
  <mi>x</mi>
  <mo stretchy="false">)</mo>
  <mo>=</mo>
  <msup>
    <mi>e</mi>
    <mi>x</mi>
  </msup>
</math>

Functions used:

- `fos_forward()`
- `fos_reverse()`


### 2. demo_simo

This example shows how to compute the first derivatives of a single-input multiple-output function in forward and reverse modes.
The example selected is the vector function given by the unit-radius helix given by:

\\[ f(t) = [\cos(t), \; \sin(t), \; t ]   \\] 

with tangent vector

\\[ f'(t) = [-\sin(t), \; \cos(t), \; 1 ]   \\] 

Functions used:

- `fos_forward()`
- `fos_reverse()`



### 3.a demo_miso_scalar

This example shows how to compute the first derivatives of a multiple-input single-output function in forward and reverse modes.
The example selected is the a scalar field given by the simple quadratic form:

\\[f(x,y,z) = x^2 + z^2 + 2x\,y + z \\]

with gradient vector

\\[ \nabla f =  [2x +2y, \; 2x, \; 2z +1]
  \\]
  

Functions used:

- `fos_forward()`
- `fos_reverse()`
- `gradient()`


### 3.b demo_miso_vector

This example shows how to compute the first derivatives of a multiple-input single-output function in forward and reverse modes.
The example selected is the same quadratic form as for the `demo_miso_scalar` example but this time the derivatives are computed using the vector mode AD.

- `fov_forward()`
- `fov_reverse()` (and `zos_forward()`)
- `gradient()`



### 4.a demo_mimo_scalar

This example shows how to compute the first derivatives of a multiple-input multiple-output function in forward and reverse modes.
The example selected is the parametrization of a unit-radius sphere:

\\[ f(u,v) = [\cos(u)\, \cos(v), \; \sin(u) \, \cos(v), \; \sin(v) ]   \\] 

with Jacobian matrix

\\[ \nabla f(u,v) =\left [\frac{\partial f}{\partial u}, \, \frac{\partial f}{\partial u}\right]^{\mathrm{T}} \quad \text{with} \quad \frac{\partial f}{\partial u} = [-\sin(u)\, \cos(v), \; \cos(u) \, \cos(v), \; 0) ] \quad \text{and} \quad \frac{\partial f}{\partial u} = [-\cos(u)\, \sin(v), \; -\sin(u) \, \sin(v), \; \cos(v)  \\]

\\[  \\] 


 
Functions used:

- `fos_forward()`
- `fos_reverse()`
- `jacobian()`


### 4.b demo_mimo_vector
This example shows how to compute the first derivatives of a multiple-input multiple-output function in forward and reverse modes.
The example selected is the same unit-radius sphere as for the `demo_mimo_scalar` example but this time the derivatives are computed using the vector mode AD.

Functions used:

- `fov_forward()`
- `fov_reverse()` (and `zos_forward()`)
- `jacobian()`



### 5. demo_large_problem

This example compares three different ways to compute the first derivatives of a scalar field (multiple-input, single-output function):

- Forward scalar mode with a for-loop
- Forward vector mode
- Reverse mode

The choice of function is a n-dimensional exponential function with simple analytic derivatives that can be used to verify the AD results

\\[  f(x_{0}, x_{1}, ..., x_{n-1}) = e^{\frac{1}{n} \sum_{i=0}^{n-1} x_{n}} \\]

\\[ \frac{\partial f}{\partial x_{n}} = \frac{1}{n} e^{\frac{1}{n} \sum_{i=0}^{n-1} x_{n}} \\]



The example shows that the forward vector mode is superior to the forward scalar mode when there is more than one independent variable because it allows to process the AD-trace only once and reduces the computational time.
In addition, the example shows that the reverse AD is independent of the number of variables and should be the preferred choice to compute the derivatives of a multiple-input, single-output function.


Functions used:

- `fos_forward()`
- `fov_forward()`
- `fos_reverse()` (and `zos_forward()`)



### 6. demo_higher_order

This example shows how to compute the first and higher order derivatives of a multiple-input single-output function in forward and reverse modes.
The example selected is a n-dimensional exponential function with simple analytic derivatives that can be used to verify the AD results

\\[  f(x_{0}, x_{1}, ..., x_{n-1}) = e^{\frac{1}{n} \sum_{i=0}^{n-1} x_{n}} \\]

\\[ \frac{\partial f}{\partial x_{n}} = \frac{1}{n} e^{\frac{1}{n} \sum_{i=0}^{n-1} x_{n}}  \qquad \dots \qquad \frac{\partial^{k} f}{\partial x_{n}^{k} } = \frac{1}{n^{k}} e^{\frac{1}{n} \sum_{i=0}^{n-1} x_{n}}\\]


Functions used:
- `hov_forward()`
- `hov_reverse()` (and `zos_forward()`)

The functions to compute higher order derivatives in scalar mode, `hos_forward()` and `hos_reverse()`, are a simpler alternative to the ones introduced in this demo.


### 7.a demo_traceless_scalar

This example shows how to compute the first derivatives of the n-dimensional exponential function

\\[  f(x_{0}, x_{1}, ..., x_{n-1}) = e^{\frac{1}{n} \sum_{i=0}^{n-1} x_{n}} \\]

using the traceless variant of ADOL-C in scalar mode


### 7.b demo_traceless_vector

This example shows how to compute the first derivatives of the n-dimensional exponential function

\\[  f(x_{0}, x_{1}, ..., x_{n-1}) = e^{\frac{1}{n} \sum_{i=0}^{n-1} x_{n}} \\]

using the traceless variant of ADOL-C in vector mode
