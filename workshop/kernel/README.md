# Kernel   

## How to configure and build your own kernel

#### EXERCISE: Fetch kernel source and create a kernel config file
This first way to create a config file, is to use the `make localmodconfig` build target. It runs `lsmod` to find all the modules loaded on the current running system and initializes the config with those modules. 

1. Fetch the latest kernel source from kernel.org into `/usr/src`
1. Unpack it
1. Run `make localmodconfig` This oldconfig process will carry over your previous settings, and prompt you if there are new features not covered by your earlier .config file. You will be asked lots of questions, if you just keep pressing (or holding down) enter, the default answer will be selected.
1. Confirm that a file called `.config` was created
1. Note down the value of the following configuration setting `CONFIG_LOCALVERSION_AUTO`. HINT: `cat` the config file and `grep` for this setting.

#### EXERCISE: Customize the kernel config
We are now going to update this .config file with some custom settings. For this config file we want to set the `CONFIG_LOCALVERSION_AUTO=y` and to turn on support for thunderbolt.

The second method of creating a config file is to uses the menu UI. It will read from the `.config` file already created in the previous step and allow you to further customize.

1. Firstly install `libncurses5-dev` as this is needed for the GUI to work.
1. Run `make menuconfig`
1. Turn on 'Automatically append version information...' under the `General Setup` menu.
1. Search for and select Thuderbolt support under `Device Drivers` menu. Ensure to turn this on as a `built-in` kernel option not a `module` option.
1. Spend some time poking around and looking at all the different options. Its dizzying how many there are, setting each on individually would take you all day!
1. Save and exit
1. Note down the value of the following configuration setting `CONFIG_LOCALVERSION_AUTO`. Make sure its set to `CONFIG_LOCALVERSION_AUTO=y`. (Setting to be explained in next exercise)

#### EXERCISE: Customizing your kernel release string
It's always fun to personalize things. The `CONFIG_LOCALVERSION_AUTO=y` config option we set previously allows us to append a version name to our kernel version string.

1. Update the `EXTRAVERSION` field in the `Makefile` found in the root of the kernel source tree. Adding your name here or something silly like `-rainbow-unicorns-rule`. This will be appended to your kernel version name string. Note, start this with a dash `-`.
1. Now find out what the final kernel release string will be by running `make kernelrelease`.

#### EXERCISE: Configuring for another architecture
Let's take a brief look at how you would configure your kernel for building on another architecture.

1. `ls arch` lists out all the supported architectures.
1. `make ARCH=blackfin menuconfig`
NOTE: you can't actually build a kernel for any other architecture until you install the appropriate cross-compiler toolchain.
1. Exit and Save but rename the file to be `.config-blackfin`

#### EXERCISE: Buliding your kernel - TO DO AT HOME!!
There are multiple ways that you can build and install your own kernel, here I have presented one way. This will install the new (compressed) kernel image into the `/boot` directory so that GRUB can find it at boot time

1. Run the following commands and wait for victory!
```bash
make 	# builds a kernel ready to be installed
make modules_install: # Installs all of the newly-built modules. They will now show up under a directory in `/lib/modules`
make install 	#  Install the new (compressed) kernel image into the `/boot` directory so that GRUB can find it at boot time. And it also create a new initrd initial ram disk that goes along with that kernel to support the early part of the boot process
```

#### EXERCISE: Install a pre-built kernel
As it will take too long build a kernel in this workshop as asked in exercies "Buliding your kernel", we have gone ahead and built a kernel for you and packaged it up as a debian package. We are going to install this instead.

```bash
cd /usr/src
# get the pre-built kernel package
curl -O https://s3-us-west-1.amazonaws.com/jesss/kernels/3.17.3/linux-image-3.17.3_3.17.3_amd64.deb
# install the new kernel
dpkg -i ../linux-image-3.17.4_3.17.4_amd64.deb
```

#### EXERCISE: Confirm your build and install worked
1. Check for your custome kernel release string with `uname -a`
1. Take a look at `/boot` and confirm that there is a new vmlinuz, initrd image file and config file corresponding to your build verison.
1. Take a look at `/lib/modules` has your new modules.

### Boot into your new kernel
TODO is this correct?
Now your new kernel is built, let's boot into it!
1. `vim /etc/default/grub` 	# update with any boot loader changes
1. `grub2-mkconfig -o /boot/grub2/grub.config` # regenerate grub.conf if you made changes

## 2. How to build your own kernel module

### What are Loadable Kernel Module's (LKMs)?
SLIDES

**Helpful module Commands**
```bash
lsmod	# lists currently loaded modules
modinfo	# info about module

# loading/unloading
modprobe my_module	# loads module and its dependencies
modprobe -r my_module	# unloads module at its dependencies
OR
insmod my_module.ko # loads just the module (no dependencies)
rmmod my_module.ko # unloads just the module

# view kernel messages with either of:
/var/log/messages
dmesg | tail

uname -r 	# displays currently running kernel version
/lib/modules/`uname -r`/	# where module files are stored
```

#### EXERCISE: lsmod

1. Find out what file `lsmod` reads from

#### EXERCISE: Loading and unloading modules

1. Install the Linux kernel headers `apt-get install linux-headers-$(uname -r)`. We need this so that we can build our own modules later on.
1. Load `btrfs` and its dependencies
1. Unload `btrfs`
1. Prove its unloaded
1. Find out the names of the other modules that `btrfs` depends on. 
1. What does  `/lib/modules/`uname -r`/modules.dep` and verify the dependencies listed are the same as in `modinfo`.

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

#### EXERCISE: Checkstyle

1. find the `checkstyle.pl` script in the kernel source tree (HINT: `checkstyle.pl --file foo.c --no-tree is a good way to check a single file)
1. run it on your c module file and make updates as suggested

#### EXERCISE: Load a character device driver
1. build and load `hello_char.c` TODO give dir URL
1. Prove its been loaded by checking `dmesg`
1. Check `/proc/devices` and `/proc/modules` for further proof its been loaded

##### References
* [http://www.tldp.org/HOWTO/Module-HOWTO/index.html](http://www.tldp.org/HOWTO/Module-HOWTO/index.html)
* [http://www.cyberciti.biz/tips/compiling-linux-kernel-module.html](http://www.cyberciti.biz/tips/compiling-linux-kernel-module.html)
* [http://www.linuxvoice.com/be-a-kernel-hacker/](http://www.linuxvoice.com/be-a-kernel-hacker/)
* [http://kernelnewbies.org/FirstKernelPatch](http://kernelnewbies.org/FirstKernelPatch)
