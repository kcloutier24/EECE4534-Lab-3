# kPWM Kernel Driver

This project is an kernel module implementation of the zedboard's timer based PWM signal, which can be output to LED0 on the board.

## Installation instructions
1) Inside the folder `gpio_pwm`, type `make` into a Linux command line
2) Transfer the file (`kpwm.ko`) over to the Zedboard via SCP

## Usage
See [Example Run and Results](#example-run-and-results) for specific commands and results.
1) Write to the control file "on" or "off" to turn the PWM on or off
2) Write the period (in $\mu\text{s}$) to the period file.
3) Write the duty cycle (in %, no floating points) to the duty file.

## Sources
As a starting point we used Jared's code. The reasoning is because Jared finished his prelab and wanted to get a head start on the lab portion.
## Example Run and Results
Use the following lines to create a 1ms period 25% duty cycle PWM signal.
- `insmod kpwm.ko`
- `echo "1000">/sys/class/axitimer/axitimer0/control/period`
- `echo "25">/sys/class/axitimer/axitimer0/control/duty`
- `echo on>/sys/class/axitimer/axitimer0/control/control`

Then, using pulsecap to record the results we get the following:

![Beautiful PWM signal](/gpio_pwm/pulsecap/kpwm_data.png)

# AXI Timer Driver

This driver provides control over AXI Timer peripherals it allows users to manage timer functionalities

## Features

- Basic timer control: start, stop, and configure timer parameters.
- Support for pulse width modulation (PWM) functionality.
- Animation feature: smooth transition of timer parameters for visual effects.

## Branch: animation-feature

This branch includes the animation functionality and interface for smooth transitions of timer parameters. 
Users can control the animation duration and enable/disable animation mode through the sysfs interface.

## Animation Interface
The animation feature is available through the sysfs interface in the `animation` branch. Users can control the animation functionality using the following attributes:

- `an_duration`: Sysfs attribute to set the animation duration in milliseconds.
- `animation`: Sysfs attribute to enable/disable animation mode.

## Animation Functionality Overview:

The animation functionality allows for the smooth transition of timer parameters, such as duty cycle or period, over a specified duration. This feature enhances visual effects and enables gradual changes in timer behavior, making it suitable for applications requiring dynamic and visually appealing timing operations.


## Visualization



![Beautiful Duty PWM signal](/gpio_pwm/pulsecap_changing/changing_duty.png)

Visuals of changing the duty in animation

![Beautiful Period PWM signal](/gpio_pwm/pulsecap_changing/changing_period.png)

Visuals of changing the period in animation 


## Animation Visualization:

The animation visualization figure demonstrates how the timer parameters transition smoothly over time during animation.
It illustrates the gradual change from an initial value to a target value, creating a pulsing effect. 
The visualization aids in understanding the behavior of the animation feature and its impact on timer operations.


## Known Issues

- Race conditions are another possibility to be an issue if the flags are not separated properly. 
- Animation may introduce overhead and affect timer accuracy, especially with high-frequency animations.

















