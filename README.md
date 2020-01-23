# A primer on ADOL-C







## Introduction

This is an unofficial repository that aims to provide a primer on how to install and use the C++ library ADOL-C.

 From the [ADOL-C project homepage](https://projects.coin-or.org/ADOL-C)

> The package ADOL-C (Automatic Differentiation by OverLoading in C++) facilitates the evaluation of first and higher derivatives of vector functions that are defined by computer programs written in C or C++.
The numerical values of derivative vectors are obtained free of truncation errors at a small multiple of the run time and randomly accessed memory of the given function evaluation program.

In short, ADOL-C is a powerful C++ library that allows to compute first and higher order derivatives of your C/C++ code in forward and reverse modes This information is essential for gradient-based optimization in fields such as aerodynamic shape optimization or model predictive control.






## Contents

The repository is organized as follows:

- [Detailed installation instructions](./adolc_installation.md) for Linux
- [A minimum working example](./adolc_minimum_working_example.md) to check if the installation was sucessful
- [A step-by-step explanation](./adolc_minimum_working_example_explanation.md) of the minimum working example to help you understand how ADOL-C works
- [A set of demonstration projects](/my_demos/adolc_demos_readme.md) showing some of the ADOL-C capabilities including the
	- Easy-to-use drivers for optimization
	- Trace_based forward and reverse functions
	- The traceless forward mode functions
	



**We hope that this repo can be useful to ADOL-C newcomers!**

Roberto Agromayor
Thursday, 23. January 2020 05:06PM 



<p style="margin-bottom:0cm;"> </p>
<p align="center">
        <img src="./figures/derivative_def.svg" height="250" width="500"/>
        &emsp; &emsp; &emsp; &emsp; &emsp;
        <img src="./figures/cpp_logo.svg" height="250" width="250"/>
</p>
<p style="margin-bottom:1cm;"> </p>

