
# GPIO PWM Controller

See the lab instructions [LabInstructions.md](/gpio_pwm/LabInstructions.md) 




Why would not separating the flags potentially generate a race
condition?

- Not separating the flags would lead to unpredictable behavior because the threads are being accessed at once without the same access time they may read different things. One thread may write while another is trying to read the same variable.

In the code, show two places where a race condition might arise.

- when you change the control flags ex: on,off,animation. because other methods check the flags
- changing the duty cycle/period and reading the duty cycle/period

What could you do to prevent a race condition, even if sharing
the same variable for storing all the flags?

-  To prevent a race condition we could put a lock on something so one thread accesses at a time
