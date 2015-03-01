# Kernel   

## Kernel architecture 101
TBD

In a Unix system, several concurrent processes attend to different tasks. Each process
asks for system resources, be it computing power, memory, network connectivity, or
some other resource. The kernel is the big chunk of executable code in charge of handling
all such requests. 

## How to build your own kernel module

### What are Loadable Kernel Module's (LKMs)?
Now we have some idea of what the kernel does, let's look briefly at its physical organisation. Early versions of the Linux kernel were monolithic - that is, all the bits and pieces were statically linked into one (rather large) executable file.

But today modern Linux kernels are modular: a lot of the functionality is contained in modules that are loaded into the kernel dynamically. This keeps the core of the kernel small and makes it possible to load or replace modules in a running kernel without rebooting.

```bash
lsmod	# lists currently loaded modules
insmod my_module.ko	# loads module
rmmod my_module	# unloads module
modinfo	# info about module

# kernel messages
/var/log/messages OR dmesg | tail

/lib/modules/`uname -r`/	# module files
```

### Anatomy of a LKM
TODO
* describe header files and how you build against kernel tree
* describe log levels

#### EXERCISE: Build a kernel module

TODO: code stub

1. checkout base LKM code from [here]()
1. update the code to print "hello world" upon load and "goodbye world" upon unload
1. build it (hint `make`)
1. verify your module works

### Syscalls
TODO
* describe me

#### EXERCISE: Load an LKM on boot

TODO
* describe me

#### EXERCISE: Build a kernel module - part x

1. build upon the kernel module in part 1
1. TODO - more interesting exercies
1. verify your module works

## Patching the kernel
TODO checkstyle

## How to build and run your own kernel


## How to build your own kernel
TODO all sections

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