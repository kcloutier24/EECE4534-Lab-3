# Prelab for Lab 3: PWM Platform Driver

# Reading list

Please read through the list and use the resources as a reference for your assignments.

1. M. Tim Jones, "Anatomy of the Linux kernel:  History and architectural decomposition", 2007, https://www.ibm.com/developerworks/linux/library/l-linux-kernel/
2. Chapter 2: "Building and Running Modules" of Linux Device Drivers, Third Edition, O’Reilly, 2005 https://lwn.net/Kernel/LDD3/
Note LDD3 uses an old kernel version 2.6 (updated examples if you are curious) While the exact API has changed, the concepts still hold true. Read the chapter for understanding (no need to perform the setup steps).

3. Slides / Materials for Embedded Linux training course (4 days) [link](https://bootlin.com/doc/training/embedded-linux/)
4. Slides / Materials for Linux Kernel Module development (5 days) [link](https://bootlin.com/doc/training/linux-kernel/) , based on BBB, PLENTY of details
5. Why not C++ in Kernel? [link](http://vger.kernel.org/lkml/#s15-3)
6. Writing Linux Kernel Module (explains some of the background again, but still short) [link](http://derekmolloy.ie/writing-a-linux-kernel-module-part-1-introduction/)
7. Linux Driver Templates [link](https://github.com/makelinux/ldt)
8. The Linux Kernel (Documentation) [link](https://www.kernel.org/doc/html/latest/)
9. Browse Kernel Sources 4.19 [link](http://elixir.free-electrons.com/linux/v4.19/source)
10. GitBook Linux Insides [link](https://www.gitbook.com/book/0xax/linux-insides/details)
11. Device Tree for Dummies, Thomas Petazzoni (Apr. 2014): http://j.mp/1jQU6NR


# Pre-lab Assignment

The instructions for ths lab are detailed in the following steps:

1. (Reserved for feedback branch pull request. You will receive top level feedback there). 
2. [Theory and code analysis](.github/STARTING_ISSUES/2.%20Theory%20and%20code%20analysis.md)
3. [Insert Kernel Module](.github/STARTING_ISSUES/3.%20Insert%20Kernel%20Module.md)
4. [Simulation Workaround](.github/STARTING_ISSUES/4.%20Simulation%20Workaround.md)
5. [Implement SysFS period](.github/STARTING_ISSUES/5.%20Implement%20SysFS%20period.md)
6. [Implement SysFS duty](.github/STARTING_ISSUES/6.%20Implement%20SysFS%20duty.md)
7. [HW Interfacing Prep](.github/STARTING_ISSUES/7.%20HW%20Interfacing%20Prep.md)

After accepting this assignment in github classroom, each step is converted into a [github issue](https://docs.github.com/en/issues). Follow the issues in numerically increasing issue number (the first issue is typically on the bottom of the list). 

## General Rules

Please commit your code frequently or at e very logical break. Each commit should have a meaningful commit message and [cross reference](https://docs.github.com/en/get-started/writing-on-github/working-with-advanced-formatting/autolinked-references-and-urls#issues-and-pull-requests) the issue the commit belongs to. Ideally, there would be no commits without referencing to a github issue. 

Please comment on each issue with the problems faced and your approach to solve them. Close an issue when done. 



