/* LAB 3 PWM Controller kernel module reference implementation */
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sysfs.h>
#include <linux/of_device.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <asm/io.h>

// define driver/module name
#define DRIVER_NAME "axitimer"

// INSTANCE flags
#define INSTANCE_FLAG_RUNNING 0x01

// maximum number of instances
#define MAX_INSTANCE_NUMBER 16
#define TIMER_MAX_COUNT 0xFFFFFFFF

// define structure for device instance data
struct esl_axitimer_instance
{
  void __iomem *regs; // memory-mapped registers
  unsigned int flags; // instance flags
  dev_t devno;        // device number

  unsigned long period; // micro seconds
  unsigned long duty;   // duration of high in constant PWM
};

// define structure for class data (common across all instances)
struct esl_axitimer_global
{
  u32 dev_major; // device major number
  dev_t devt;

  unsigned int instance_number; // ever-increasing number for instances
};

// Instantiate class data
static struct esl_axitimer_global driver_data;

// Utility method to read registers
static inline u32 reg_read(struct esl_axitimer_instance *inst, u32 reg)
{
  return ioread32(inst->regs + reg);
}

// Utility method to write registers
static inline void reg_write(struct esl_axitimer_instance *inst, u32 reg,
                             u32 value)
{
  iowrite32(value, inst->regs + reg);
}

// initialize device
static void axitimer_initialize(struct esl_axitimer_instance *inst) //TODO add register ti=o create pwm timer
{
}

/*this function is linked to writing to the duty file that gets created
it is called when something is written to that file
use echo 10 > duty to set duty cycle to 10%
*/
static ssize_t esl_axitimer_duty_store(struct device *dev,
                                       struct device_attribute *attr,
                                       const char *buf, size_t count)
{
  struct esl_axitimer_instance *inst = dev_get_drvdata(dev);

  unsigned long res = -1;//TODO update register duty cycle
  int stat = kstrtoul(buf, 0, &res); // Returns 0 on success,

  if (res > -1 && res < 0xFFFFFFFF && stat == 0)
  {
    inst->duty = res;
  }

  else
  {
    printk(KERN_ERR "kPWM: %ld not written to duty", res);
    return -EINVAL;
  }

  return count;
}

/*this function is called by the duty file when it is being read
it prints the duty cycle
 use the command cat duty to show duty
*/
static ssize_t esl_axitimer_duty_show(struct device *dev,
                                      struct device_attribute *attr,
                                      char *buf)
{
  struct esl_axitimer_instance *inst = dev_get_drvdata(dev);

  return sprintf(buf, "Duty cycle: %ld\n", inst->duty);
}

/*
this function is linked to writing to the period file that gets created
it is called when something is written to that file
use echo 10 > period to set peropd to 10ms
*/
static ssize_t esl_axitimer_period_store(struct device *dev,
                                         struct device_attribute *attr,
                                         const char *buf, size_t count)
{
  struct esl_axitimer_instance *inst = dev_get_drvdata(dev);

  unsigned long res = -1;//TODO update register period
  int stat = kstrtoul(buf, 0, &res); // Returns 0 on success,

  if (res > -1 && res < 0xFFFFFFFF && stat == 0)
  {
    inst->period = res;
  }

  else
  {
    printk(KERN_ERR "kPWM: %ld not written to period", res);
    return -EINVAL;
  }

  return count;
}

/*
this function is called by the period file when it is being read
it prints the period
 use the command cat period to show period

*/

static ssize_t esl_axitimer_period_show(struct device *dev,
                                        struct device_attribute *attr,
                                        char *buf)
{
  struct esl_axitimer_instance *inst = dev_get_drvdata(dev);

  return sprintf(buf, "Period: %ld\n", inst->period);
}

/*
Katherine Cloutier
PRE3.3


the function esl_axitimer_state_show() gets called when the user reads the specific attribute from the device hardware
this function provides the current state of the esl_axi timer
when the PWM controller is idle the function returns a string "idle"
when the PWM controller is running it returns a string "running"
both states will also send out "buf" which is an output that is the read system attribute


*/
static ssize_t esl_axitimer_state_show(struct device *dev,
                                       struct device_attribute *attr,
                                       char *buf)
{
  struct esl_axitimer_instance *inst = dev_get_drvdata(dev);

  if (inst->flags & INSTANCE_FLAG_RUNNING)
  {
    return sprintf(buf, "running\n");
  }

  return sprintf(buf, "idle\n");
}

/*
Katherine Cloutier
PRE3.4


the function function esl_axitimer_control_store() is called when the user writes an attribute to the PWM controller on or off
this function handles controls based on users input
the sysfs file is represented in the initialization by the device_attribute *attr which holds informain about the attribute
it is linked during device initialiation aswell


*/
static ssize_t esl_axitimer_control_store(struct device *dev,
                                          struct device_attribute *attr,
                                          const char *buf, size_t count)
{
  struct esl_axitimer_instance *inst = dev_get_drvdata(dev);

  if (!strncmp(buf, "on", count))
  {
    inst->flags |= INSTANCE_FLAG_RUNNING;
  }
  else if (!strncmp(buf, "off", count))
  {
    inst->flags &= ~INSTANCE_FLAG_RUNNING;
  }
  else
  {
    return -EINVAL;
  }

  return count;
}

// define our own class for proper and automatic sysfs file group creation

static struct device_attribute esl_axitimer_period = {
    .attr = {
        .name = "period",
        .mode = S_IRWXU, // write only
    },
    .store = esl_axitimer_period_store,
    .show = esl_axitimer_period_show,

};

static struct device_attribute esl_axitimer_duty = {
    .attr = {
        .name = "duty",
        .mode = S_IRWXU,
    },
    .show = esl_axitimer_duty_show,
    .store = esl_axitimer_duty_store,

};

// start / stop control
static struct device_attribute esl_axitimer_control = {
    .attr = {
        .name = "control",
        .mode = S_IWUSR, // write only
    },
    .store = esl_axitimer_control_store,
};

// current state
static struct device_attribute esl_axitimer_state = {
    .attr = {
        .name = "status",
        .mode = S_IRUGO,
    },
    .show = esl_axitimer_state_show,
};

// array of attributes
static struct attribute *esl_axitimer_attrs[] = {
    &esl_axitimer_control.attr,
    &esl_axitimer_state.attr,
    NULL};

// Group all attributes to "control" folder,
// this creates /sys/class/axitimer/axitimerX/control
static struct attribute_group esl_axitimer_attr_group = {
    .name = "control", // control folder
    .attrs = esl_axitimer_attrs,
};

// array of attribute groups (sysfs files and folders)
static const struct attribute_group *esl_axitimer_attr_groups[] = {
    &esl_axitimer_attr_group, // the "control" folder
    NULL};

// define the class, creates /sys/class/axitimer
static struct class esl_axitimer_class = {
    .name = "axitimer",
    .owner = THIS_MODULE,
};

// probe, or add an instance
static int esl_axitimer_probe(struct platform_device *pdev)
{
  struct esl_axitimer_instance *inst = NULL; // new instance
  struct resource *res;                      // for reading resources from device tree
  struct device *dev;
  const void *property;
  // make new device; we need device a number (major, minor)
  // use instance count as the minor, which we increase each time
  // major has already been allocated in init function
  // to take a look at majors, do cat /proc/devices
  dev_t devno = MKDEV(driver_data.dev_major, driver_data.instance_number);

  // verify if timer is marked as PWM timer, get resource from device tree
  // PRELAB: Modify the driver code so that this restriction is ignored for debugging on QEMU.
  property = of_get_property(pdev->dev.of_node, "esl,pwm-timer", NULL);
  if (!property)
  {
    // timer is not marked for PWM, fail probe
    printk(KERN_INFO "kPWM: %s not marked as PWM timer.\n",
           pdev->name);
    printk(KERN_WARNING "kPWM: error skipped for debugging\n");
    // return -EPERM;
  }
  else
  {
    printk(KERN_INFO "kPWM: %s accurately marked as PWM timer.\n",
           pdev->name);
  }

  // allocate new instance. explanation for this:
  //  1. we use devm_kzalloc instead of kzalloc because it has the nice property
  //     of freeing unused resources automatically when the platform driver is
  //     removed (devm = dev managed and attached to pdev->dev so when it is
  //     destroyed, data is garbage collected)
  //  2. GFP_KERNEL means we are allocating KERNEL memory, otherwise it should be
  //     GFP_USER
  inst = devm_kzalloc(&pdev->dev, sizeof(struct esl_axitimer_instance),
                      GFP_KERNEL);

  if (!inst)
  {
    // ran out of memory
    return -ENOMEM;
  }

  /*
  Katherine Cloutier
  PRE3.1

the function deffinition is:
struct resource *platform_get_resource(struct platform_device *pdev, unsigned int type, unsigned int n);

the resouce array can be used to learn where various resources can be found on the hardware
sort of like a catalog of memory-mapped I/O registers and interups
the "pdev" is the heardware devide
the "type" is the type of resource bging requested
the "n" parameter says which resource/region of that type is desired

so res = platform_get_resource(pdev, IORESOURCE_MEM, 0) takes the hardware pdev and looks for the first  IORESOURCE_MEM rsource


  */
  res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
  if (IS_ERR(res))
  {
    return PTR_ERR(res);
  }

  /*
Katherine Cloutier
PRE3.2

  the function deffinition:
void __iomem *devm_ioremap_resource(struct device *dev, const struct resource *res);
devm_ioremap_resource() checks the requests IO memory region by requesting it from the kernel and remaps it
it is necessary to access memory mapped registers that are associated with the hardware device controlled

inst->regs = devm_ioremap_resource(&pdev->dev, res);
"&pdev->dev" refers to the device
"res" is the resource
maped the I/O resouce "res" into the kernels address space and adsisignes the mapped address to "inst->regs"


  */
  inst->regs = devm_ioremap_resource(&pdev->dev, res);
  if (IS_ERR(inst->regs))
  {
    // error mapping
    return PTR_ERR(inst->regs);
  }

  // set platform driver data (our instance struct)
  platform_set_drvdata(pdev, inst);

  // create the character device, this will create:
  // 1. /dev/axitimerX
  // 2. all the sysfs stuff
  dev = device_create_with_groups(&esl_axitimer_class, &pdev->dev,
                                  devno, inst, esl_axitimer_attr_groups,
                                  "axitimer%d", driver_data.instance_number);

  if (IS_ERR(dev))
  {
    return PTR_ERR(dev);
  }

  // set dev number
  inst->devno = devno;

  // increment instance counter
  driver_data.instance_number++;

  // initialize timer
  axitimer_initialize(inst);

  printk(KERN_INFO "probed kPWM with timer %s\n", pdev->name);

  return 0;
}

// remove an instance
static int esl_axitimer_remove(struct platform_device *pdev)
{
  struct esl_axitimer_instance *inst = platform_get_drvdata(pdev);

  // cleanup and remove
  device_destroy(&esl_axitimer_class, inst->devno);//TODO remove device 

  return 0;
}

// matching table
// list of strings that indicate what platform
// device is compatible with
static struct of_device_id esl_axitimer_of_ids[] = {
    {.compatible = "xlnx,xps-timer-1.00.a"}, // Kat: device driver xlnx,xps-timer-1.00.a mathes with timer3: 0x41290000
    {}};

// platform driver definition
static struct platform_driver esl_axitimer_driver = {
    .probe = esl_axitimer_probe,
    .remove = esl_axitimer_remove,
    .driver = {
        .name = DRIVER_NAME,
        .of_match_table = of_match_ptr(esl_axitimer_of_ids),
    },
};

// module initialization
static int esl_axitimer_init(void)
{
  int err;
  // allocate character device region, /dev/axitimerX
  err = alloc_chrdev_region(&driver_data.devt, 0, MAX_INSTANCE_NUMBER,
                            DRIVER_NAME);
  if (err)
  {
    return err;
  }

  // initialize our data
  driver_data.instance_number = 0;
  driver_data.dev_major = MAJOR(driver_data.devt);

  // register class
  class_register(&esl_axitimer_class);

  // register platform driver
  platform_driver_register(&esl_axitimer_driver);

  return 0;
}

// module removal
static void esl_axitimer_exit(void)
{
  // cleanup
  platform_driver_unregister(&esl_axitimer_driver);
  class_unregister(&esl_axitimer_class);
  unregister_chrdev_region(driver_data.devt, MAX_INSTANCE_NUMBER);
}

module_init(esl_axitimer_init);
module_exit(esl_axitimer_exit);

MODULE_DESCRIPTION("AXI Timer driver");
MODULE_LICENSE("GPL");
