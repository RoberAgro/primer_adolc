# ADOL-C Installation

This document contrains a detailed explanation of how to install the ADOL-C library in Linux.

## Requirements

The package `autoconf` is required to generate the configuration files used during the installation of ADOL-C.
To install this package type the following commands in your terminal

	sudo apt-get update
	sudo apt-get install autoconf


## Installing ADOL-C

ADOL-C can be compiled using the [usual gnu triplet](https://www.howtogeek.com/105413/how-to-compile-and-install-from-source-on-ubuntu/):

> configure -> make -> make install

The detailed steps are as follows:

- First, create the directories `adolc-version/adolc_base` and `adolc-version/adolc_source` that will be used during the installation.

		mkdir adolc-version adolc-version/adolc_base adolc-version/adolc_source
	
	You can remplace the termination of `adolc-version` by the latest release of ADOL-C, for instance `adolc-2.7.0`


- Download the source files from the [official ADOL-C repository](https://gitlab.com/adol-c/adol-c) and extract them into the `adolc-version/adolc_source` directory

- Set the destination installation directory editing the field `AC_PREFIX_DEFAULT(...)` of the `configure.ac` file. In our case it should look something like:
	
		AC_PREFIX_DEFAULT(${HOME}/my_software/adolc-version/adolc_base)

- Now we can use the package `autoconf` to generate the executable file `configure` from the `configure.ac` file. To do that, simply type:

		autoreconf -fi
	

- To complete the installation just run the gnu triplet:

		./configure
		make
		make install
		
	This may take a while. If the installation was successful you should be able to see the directories `adolc_base/include` and `adolc_base/lib64`. 
	
	To check  that ADOL-C is running on your system you can try to compile and execute the [minimum working example](./adolc_minimum_working_example.md) provided in this repository.


