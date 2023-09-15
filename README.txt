The following are notes on how to modify the files within this directory
in order to create a project using this template

********** DISCLAIMER **********

This template is meant to be used as a tool to assist with the
creation of Geant4 projects. It was made by one person and may
contain spelling errors, bugs, incorrect comments, among other
things. Feel free to correct any of these issues if you feel
comfortable enough to make changes

********** REQUIREMENTS **********

The following actions are REQUIRED in order for this template
to work as intended:

- Within the "run.sh" file, set the INSTALL_PATH variable to the
  absolute path of your Geant4 installation
  
********** GENERAL **********

By default, the project is configured to look for header files in the
"include" directory and source code files within the "src" directory, 
with the exception of the main source code file, which should be located in
the main project directory. The locations of these files may be changed,
and new directories may be added, by modifying "CMakeLists.txt". Though,
it is probably not worth making any changes unless it is necessary and
you know how to properly modify "CMakeLists.txt"

By default, Geant4 output files will be generated in the "output-files"
directory within the project directory

********** AUTOMATION **********

More exact details related to how to automate data generation and
visualization can be found below, but please note these general
steps for automation:

1. Make sure "auto.mac" contains the necessary Geant4 commands for
   your program to generate some output files.
2. Make sure "process-data.cc" ultimately creates an "output.root" file
   within the directory "output-files/analysis-gen" within the
   project directory
3. Run the "run.sh" Bash scripts with the -a or -v argument

********** run.sh **********

To make building projects easier, the "run.sh" Bash script has been 
created, which can automatically create a build directory for a 
project, build, and execute a project executable. You can use 
this script by running the following inside of the project folder:
$ . run.sh	(to build and run)
$ . run.sh -rb	(to force a complete rebuild and run)
$ . run.sh -a   (to run with automatic data analysis. See "auto.mac" and
                "process-data.cc" below)

********** CMakeLists.txt **********

By default within "CMakeLists.txt", the project name, main code file, and
output executable have been named as "Geant4Template", "template.cc", and
"template" respectively. If you wish to change these, please change the
values of their corresponding variables

********** template.cc **********

Removing any of the code within "template.cc" will most likely result
in the project not building as expected. Feel free to add additional
code to this file, but note that removing code that is already there
is not advised

********** auto.mac **********

In the event that the project is run using the run.sh Bash script
with the -a argument, this macro will be run once the program has
been built and begins running. This macro should contain the necessary
Geant4 commands to generate the output required by analyze.py. The
way in which output files are generated is determined by how you
program your project, so make sure to configure this macro correctly
if you wish to use the automatic feature of run.sh

********** UI-init.mac **********

This macro is executed by the project as soon as the GUI is opened.
In order to have the UI be customized upon opening, you can place
Geant4 commands within this macro to preset certain values.

********** project-variables.txt **********

This file is a text file that is read by src/init.cc, and contains values
may be frequently adjusted. This allows you to configure variables for your
project without interacting directly with the source code. Feel free to use
this file to do so, however remember if you change the structure of how
variable appear within this file, you will also have to modify src/init.cc
to ensure the new values are read correctly

********** process-data.cc **********

In the event that the project is run using the run.sh Bash script
with the -a argument, this C++ script will be run once the auto.mac
macro has been executed and Geant4 has closed. This script should ultimately
generate a file named "output.root" in the directory "output-files/analysis-gen"
within the project directory. "output.root" should contain all data you wish
to visualize, as after this script terminates, run.sh will attempt to open
the "output.root" file in the specified directory. Note that this script
is run within this directory, making it easier to generate files within it

********************************
