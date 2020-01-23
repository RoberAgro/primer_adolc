# ADOL-C demos guide

This directory contains some well-documented demonstration projects to get started with ADOL-C.

We suggest this order to explore the demos:



### 1. demo_siso

This example shows how to compute the first derivatives of a single-input single-output function in forward and reverse modes.
The example selected is the simple scalar function:


<a href="https://www.codecogs.com/eqnedit.php?latex=f(x)&space;=&space;e^{x}" target="_blank"><img src="https://latex.codecogs.com/svg.latex?f(x)&space;=&space;e^{x}" title="f(x) = e^{x}" /></a>

Functions used:

- `fos_forward()`
- `fos_reverse()`


### 2. demo_simo

This example shows how to compute the first derivatives of a single-input multiple-output function in forward and reverse modes.
The example selected is the vector function given by the unit-radius helix given by:

<a href="https://www.codecogs.com/eqnedit.php?latex=f(t)&space;=&space;[\cos(t),&space;\;&space;\sin(t),&space;\;&space;t&space;]" target="_blank"><img src="https://latex.codecogs.com/svg.latex?f(t)&space;=&space;[\cos(t),&space;\;&space;\sin(t),&space;\;&space;t&space;]" title="f(t) = [\cos(t), \; \sin(t), \; t ]" /></a>

with tangent vector

<a href="https://www.codecogs.com/eqnedit.php?latex=f'(t)&space;=&space;[-\sin(t),&space;\;&space;\cos(t),&space;\;&space;1&space;]" target="_blank"><img src="https://latex.codecogs.com/svg.latex?f'(t)&space;=&space;[-\sin(t),&space;\;&space;\cos(t),&space;\;&space;1&space;]" title="f'(t) = [-\sin(t), \; \cos(t), \; 1 ]" /></a>

Functions used:

- `fos_forward()`
- `fos_reverse()`



### 3.a demo_miso_scalar

This example shows how to compute the first derivatives of a multiple-input single-output function in forward and reverse modes.
The example selected is the a scalar field given by the simple quadratic form:

<a href="https://www.codecogs.com/eqnedit.php?latex=f(x,y,z)&space;=&space;x^2&space;&plus;&space;z^2&space;&plus;&space;2x\,y&space;&plus;&space;z" target="_blank"><img src="https://latex.codecogs.com/svg.latex?f(x,y,z)&space;=&space;x^2&space;&plus;&space;z^2&space;&plus;&space;2x\,y&space;&plus;&space;z" title="f(x,y,z) = x^2 + z^2 + 2x\,y + z" /></a>

with gradient vector

<a href="https://www.codecogs.com/eqnedit.php?latex=\nabla&space;f&space;=&space;[2x&space;&plus;2y,&space;\;&space;2x,&space;\;&space;2z&space;&plus;1]" target="_blank"><img src="https://latex.codecogs.com/svg.latex?\nabla&space;f&space;=&space;[2x&space;&plus;2y,&space;\;&space;2x,&space;\;&space;2z&space;&plus;1]" title="\nabla f = [2x +2y, \; 2x, \; 2z +1]" /></a>
  

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

<a href="https://www.codecogs.com/eqnedit.php?latex=f(u,v)&space;=&space;[\cos(u)\,&space;\cos(v),&space;\;&space;\sin(u)&space;\,&space;\cos(v),&space;\;&space;\sin(v)&space;]" target="_blank"><img src="https://latex.codecogs.com/svg.latex?f(u,v)&space;=&space;[\cos(u)\,&space;\cos(v),&space;\;&space;\sin(u)&space;\,&space;\cos(v),&space;\;&space;\sin(v)&space;]" title="f(u,v) = [\cos(u)\, \cos(v), \; \sin(u) \, \cos(v), \; \sin(v) ]" /></a>

with Jacobian matrix

<a href="https://www.codecogs.com/eqnedit.php?latex=\nabla&space;f(u,v)&space;=\left&space;[\frac{\partial&space;f}{\partial&space;u},&space;\,&space;\frac{\partial&space;f}{\partial&space;u}\right]^{\mathrm{T}}" target="_blank"><img src="https://latex.codecogs.com/svg.latex?\nabla&space;f(u,v)&space;=\left&space;[\frac{\partial&space;f}{\partial&space;u},&space;\,&space;\frac{\partial&space;f}{\partial&space;u}\right]^{\mathrm{T}}" title="\nabla f(u,v) =\left [\frac{\partial f}{\partial u}, \, \frac{\partial f}{\partial u}\right]^{\mathrm{T}}" /></a>


<a href="https://www.codecogs.com/eqnedit.php?latex=\quad&space;\frac{\partial&space;f}{\partial&space;u}&space;=&space;[-\sin(u)\,&space;\cos(v),&space;\;&space;\cos(u)&space;\,&space;\cos(v),&space;\;&space;0)&space;]&space;\quad&space;\text{and}&space;\quad&space;\frac{\partial&space;f}{\partial&space;u}&space;=&space;[-\cos(u)\,&space;\sin(v),&space;\;&space;-\sin(u)&space;\,&space;\sin(v),&space;\;&space;\cos(v)" target="_blank"><img src="https://latex.codecogs.com/svg.latex?\quad&space;\frac{\partial&space;f}{\partial&space;u}&space;=&space;[-\sin(u)\,&space;\cos(v),&space;\;&space;\cos(u)&space;\,&space;\cos(v),&space;\;&space;0)&space;]&space;\quad&space;\text{and}&space;\quad&space;\frac{\partial&space;f}{\partial&space;u}&space;=&space;[-\cos(u)\,&space;\sin(v),&space;\;&space;-\sin(u)&space;\,&space;\sin(v),&space;\;&space;\cos(v)" title="\quad \frac{\partial f}{\partial v} = [-\sin(u)\, \cos(v), \; \cos(u) \, \cos(v), \; 0) ] \quad \text{and} \quad \frac{\partial f}{\partial u} = [-\cos(u)\, \sin(v), \; -\sin(u) \, \sin(v), \; \cos(v)" /></a>
 
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

<a href="https://www.codecogs.com/eqnedit.php?latex=f(x_{0},&space;x_{1},&space;...,&space;x_{n-1})&space;=&space;e^{\frac{1}{n}&space;\sum_{i=0}^{n-1}&space;x_{n}}" target="_blank"><img src="https://latex.codecogs.com/svg.latex?f(x_{0},&space;x_{1},&space;...,&space;x_{n-1})&space;=&space;e^{\frac{1}{n}&space;\sum_{i=0}^{n-1}&space;x_{n}}" title="f(x_{0}, x_{1}, ..., x_{n-1}) = e^{\frac{1}{n} \sum_{i=0}^{n-1} x_{n}}" /></a>

<a href="https://www.codecogs.com/eqnedit.php?latex=\frac{\partial&space;f}{\partial&space;x_{n}}&space;=&space;\frac{1}{n}&space;e^{\frac{1}{n}&space;\sum_{i=0}^{n-1}&space;x_{n}}" target="_blank"><img src="https://latex.codecogs.com/svg.latex?\frac{\partial&space;f}{\partial&space;x_{n}}&space;=&space;\frac{1}{n}&space;e^{\frac{1}{n}&space;\sum_{i=0}^{n-1}&space;x_{n}}" title="\frac{\partial f}{\partial x_{n}} = \frac{1}{n} e^{\frac{1}{n} \sum_{i=0}^{n-1} x_{n}}" /></a>

The example shows that the forward vector mode is superior to the forward scalar mode when there is more than one independent variable because it allows to process the AD-trace only once and reduces the computational time.
In addition, the example shows that the reverse AD is independent of the number of variables and should be the preferred choice to compute the derivatives of a multiple-input, single-output function.


Functions used:

- `fos_forward()`
- `fov_forward()`
- `fos_reverse()` (and `zos_forward()`)



### 6. demo_higher_order

This example shows how to compute the first and higher order derivatives of a multiple-input single-output function in forward and reverse modes.
The example selected is a n-dimensional exponential function with simple analytic derivatives that can be used to verify the AD results

<a href="https://www.codecogs.com/eqnedit.php?latex=f(x_{0},&space;x_{1},&space;...,&space;x_{n-1})&space;=&space;e^{\frac{1}{n}&space;\sum_{i=0}^{n-1}&space;x_{n}}" target="_blank"><img src="https://latex.codecogs.com/svg.latex?f(x_{0},&space;x_{1},&space;...,&space;x_{n-1})&space;=&space;e^{\frac{1}{n}&space;\sum_{i=0}^{n-1}&space;x_{n}}" title="f(x_{0}, x_{1}, ..., x_{n-1}) = e^{\frac{1}{n} \sum_{i=0}^{n-1} x_{n}}" /></a>

<a href="https://www.codecogs.com/eqnedit.php?latex=\frac{\partial&space;f}{\partial&space;x_{n}}&space;=&space;\frac{1}{n}&space;e^{\frac{1}{n}&space;\sum_{i=0}^{n-1}&space;x_{n}}&space;\qquad&space;\dots&space;\qquad&space;\frac{\partial^{k}&space;f}{\partial&space;x_{n}^{k}&space;}&space;=&space;\frac{1}{n^{k}}&space;e^{\frac{1}{n}&space;\sum_{i=0}^{n-1}&space;x_{n}}" target="_blank"><img src="https://latex.codecogs.com/svg.latex?\frac{\partial&space;f}{\partial&space;x_{n}}&space;=&space;\frac{1}{n}&space;e^{\frac{1}{n}&space;\sum_{i=0}^{n-1}&space;x_{n}}&space;\qquad&space;\dots&space;\qquad&space;\frac{\partial^{k}&space;f}{\partial&space;x_{n}^{k}&space;}&space;=&space;\frac{1}{n^{k}}&space;e^{\frac{1}{n}&space;\sum_{i=0}^{n-1}&space;x_{n}}" title="\frac{\partial f}{\partial x_{n}} = \frac{1}{n} e^{\frac{1}{n} \sum_{i=0}^{n-1} x_{n}} \qquad \dots \qquad \frac{\partial^{k} f}{\partial x_{n}^{k} } = \frac{1}{n^{k}} e^{\frac{1}{n} \sum_{i=0}^{n-1} x_{n}}" /></a>


Functions used:
- `hov_forward()`
- `hov_reverse()` (and `zos_forward()`)

The functions to compute higher order derivatives in scalar mode, `hos_forward()` and `hos_reverse()`, are a simpler alternative to the ones introduced in this demo.


### 7.a demo_traceless_scalar

This example shows how to compute the first derivatives of the n-dimensional exponential function

<a href="https://www.codecogs.com/eqnedit.php?latex=f(x_{0},&space;x_{1},&space;...,&space;x_{n-1})&space;=&space;e^{\frac{1}{n}&space;\sum_{i=0}^{n-1}&space;x_{n}}" target="_blank"><img src="https://latex.codecogs.com/svg.latex?f(x_{0},&space;x_{1},&space;...,&space;x_{n-1})&space;=&space;e^{\frac{1}{n}&space;\sum_{i=0}^{n-1}&space;x_{n}}" title="f(x_{0}, x_{1}, ..., x_{n-1}) = e^{\frac{1}{n} \sum_{i=0}^{n-1} x_{n}}" /></a>

using the traceless variant of ADOL-C in scalar mode


### 7.b demo_traceless_vector

This example shows how to compute the first derivatives of the n-dimensional exponential function

<a href="https://www.codecogs.com/eqnedit.php?latex=f(x_{0},&space;x_{1},&space;...,&space;x_{n-1})&space;=&space;e^{\frac{1}{n}&space;\sum_{i=0}^{n-1}&space;x_{n}}" target="_blank"><img src="https://latex.codecogs.com/svg.latex?f(x_{0},&space;x_{1},&space;...,&space;x_{n-1})&space;=&space;e^{\frac{1}{n}&space;\sum_{i=0}^{n-1}&space;x_{n}}" title="f(x_{0}, x_{1}, ..., x_{n-1}) = e^{\frac{1}{n} \sum_{i=0}^{n-1} x_{n}}" /></a>


using the traceless variant of ADOL-C in vector mode
