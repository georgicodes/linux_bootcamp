# Kernel   

## Kernel architecture 101
![](images/linkux_kernel.png)
SLIDES

## How to build your own kernel module

### What are Loadable Kernel Module's (LKMs)?
SLIDES

**LKM Commands**
```bash
lsmod	# lists currently loaded modules
modprobe my_module	# loads module and its dependencies
modprobe -r my_module	# unloads module at its dependencies
modinfo	# info about module

# view kernel messages with either of:
/var/log/messages
dmesg | tail

uname -r 	# displays currently running kernel version
/lib/modules/`uname -r`/	# where module files are stored
```

#### EXERCISE: lsmod

1. Find out what file `lsmod` reads from

#### EXERCISE: Loading and unloading modules

1. Load `btrfs`
1. Unload `btrfs`
1. Prove its unloaded
1. Find out the info of the `btrfs` module
1. Take a look at `/lib/modules/`uname -r`/modules.dep` and verify the dependencies listed are the same as in `modinfo`

### Anatomy of a LKM
SLIDES

#### EXERCISE: Finding out about the kernel tree

TODO find command for a kernel function used?
eg `module_exit`

#### EXERCISE: Build a kernel module

TODO: code stub

1. checkout base LKM code from [here]()
1. update the code to print ">>> Hello World! <<<" upon load and ">>> Goodbye Cruel World... <<<" upon unload
1. build it (HINT: `make`)
1. verify your module works

#### EXERCISE: Returning negative number

1. modify your init method to return -7
1. build and load it
1. what happens? check `dmesg` as you are trying this

#### EXERCISE: Returning positive number

1. modify your init method to return 7
1. build and load it
1. what happens? check `dmesg` as you are trying this

### Syscalls
SLIDES

#### EXERCISE: Load an LKM on boot

1. Add an entry for our module to `/etc/modules` and reboot
1. Prove its loaded

#### EXERCISE: Build a kernel module - part x

1. build upon the kernel module in part 1
1. TODO - more interesting exercies
1. verify your module works

## Patching the kernel
SLIDES

#### EXERCISE: Checkstyle

1. find the `checkstyle.pl` script in the kernel source tree (HINT: `checkstyle.pl --file foo.c --no-tree is a good way to check a single file)
1. run it on your c module file and make updates as suggested

## How to build and run your own kernel

## How to build your own kernel
SLIDES (makeconfig)

### Hows does Linux get updated?

### Where to retrive the Linux source?

### Configure your kernel

### Compile your kernel

### Boot your kernel

##### References
* [http://www.tldp.org/HOWTO/Module-HOWTO/index.html](http://www.tldp.org/HOWTO/Module-HOWTO/index.html)
* [http://www.cyberciti.biz/tips/compiling-linux-kernel-module.html](http://www.cyberciti.biz/tips/compiling-linux-kernel-module.html)
* [http://www.linuxvoice.com/be-a-kernel-hacker/](http://www.linuxvoice.com/be-a-kernel-hacker/)
* [http://kernelnewbies.org/FirstKernelPatch](http://kernelnewbies.org/FirstKernelPatch)