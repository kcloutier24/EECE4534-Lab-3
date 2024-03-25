# Lab 3: PWM Kernel Platform Driver 

In this lab you will learn the basics about Linux kernel modules and
drivers. Using the knowledge from previous labs, we will now explore the
configuration and control of hardware peripherals in the context of an
operating system driver. You will learn about the kernel and how to
configure and control peripherals in kernel-space is different from the
user-space perspective.

In the pre-lab assignment, you implemented a partial platform driver
that controls AXI Timer peripherals, providing a sysfs interface to
input parameters directly as user-readable values that control the
characteristics of the generated PWM signal. This lab does not come 
new skeleton code. Instead, this lab builds upon 
the pre-lab code to create a working platform driver 


## Overview 

The instructions for ths lab are detailed in the following steps:

 1. (Reserved for feedback branch pull request. You will receive top level feedback there). 
 2. [PWM Controller Driver](.github/STARTING_ISSUES/2.%20PWM%20Controller%20Driver.md)
 3. [PWM Animation Driver](.github/STARTING_ISSUES/3.%20PWM%20Animation%20Driver.md) 
 4. [Post Lab Questions](.github/STARTING_ISSUES/4.%20Post%20Lab%20Questions.md)


After accepting this assignment in github classroom, each step is converted into a [github issue](https://docs.github.com/en/issues). Follow the issues in numerically increasing issue number (the first issue is typically on the bottom of the list). 

## General Rules

Please commit your code frequently or at e very logical break. Each commit should have a meaningful commit message and [cross reference](https://docs.github.com/en/get-started/writing-on-github/working-with-advanced-formatting/autolinked-references-and-urls#issues-and-pull-requests) the issue the commit belongs to. Ideally, there would be no commits without referencing to a github issue. 

Please comment on each issue with the problems faced and your approach to solve them. Close an issue when done. 

# Reading List

The following documents will help you complete the pre-lab assignment.
These will also help you in subsequent lab assignments.

Please complete the reading assignments that are marked as
***\[Required\]*** before attempting the pre-lab assignments.

See the reading list in the prelab assignment.

**HINT:** Whenever you see the man-pages mentioned or a comment like
*see man \<name\>*, you can examine the documentation for that by simply
typing `man <name>` in a terminal inside the development environment.
Online man pages are available as well, such as
<https://linux.die.net/man/>.