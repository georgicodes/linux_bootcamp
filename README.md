# Linux Bootcamp: From Casual Linux User to Kernel Hacker (Workshop)

Session Info:
[OSCON:Linux Bootcamp: From Casual Linux User to Kernel Hacker](http://www.oscon.com/open-source-2015/public/schedule/detail/41300)

Monday, July 20th 2015 at 9:00am to 12:30pm

## How to use these materials
This GitHub repo contains an Ubuntu installation guide as well as all the workshop exercises.

All workshop exercises can be found [here](workshop).

## Ubuntu Setup
For this workshop, we will use a program called Vagrant to run a full copy of Ubuntu Desktop version 15.04 (the latest and greatest). Vagrant requires that VirtualBox be pre-installed and is a handy tool which allows users to load pre-installed software. If we didn't use Vagrant we'd have to spend a good chunk of the class just installing Ubuntu on VirutalBox which is pretty boring :)

## Prerequsites
1. Free up around 10GB's on your laptop to get started.
1. **Download and install** VirtualBox 4.3.26 for your OS: https://www.virtualbox.org/wiki/Downloads
1. **Download and install** Vagrant for your OS: http://www.vagrantup.com/downloads.html

## Setting up Ubuntu with Vagrant

#### Check Vagrant is installed
Check that you have Vagrant installed successfully by running `vagrant --version`. You should see something like `Vagrant 1.7.2`.

#### Download the Ubuntu vagrant image
Download and unzip the Ubuntu_15.04 image that we have already pre-built from [here](https://www.dropbox.com/s/b1zqdjyka9udkfv/package.box.zip?dl=0).
You should see a file called package.box.

#### Install the Ubuntu box in Vagrant
Open up a terminal and run the below command. This installs an Ubuntu box called `Ubuntu-Desktop-15.04` with Vagrant.

```bash
$ vagrant box add {boxname} package.box
```
in our case:
```
$ vagrant box add Ubuntu-Desktop-15.04 package.box
```

#### Init the Vagrant box
Go to a different folder and type:

```
$ vagrant init {boxname}
```
in our case:
```
$ vagrant init Ubuntu-Desktop-15.04
```
If you list the contents of this directory (`ls`), you'll now see a new file that was created `Vagrantfile`.

#### Enable GUI
We now need to enable the GUI, to do this either replace the `Vagrantfile` created with the one here: XXX TODO or edit the generated `Vagrantfile` by uncommenting the following lines and saving the file:

```bash
    config.vm.provider "virtualbox" do |v|
    v.gui = true
    end
```

#### Spin it up!
```bash
$ vagrant up
```
You should now see this:
![](images/Vagrant_Ubuntu_Box.png)

This should launch a Ubuntu 15.04 Desktop for use throughout the tutorial! When you want to shut it down run:
```bash
$ vagrant halt
```



====
# OLD INSTRUCTIONS PRE VAGRANT DELETE ME
## Install Ubuntu

### Prerequsites
1. Free up around 10GB's on your laptop to get started.
1. **Download and install** VirtualBox 4.3.26 for your OS: https://www.virtualbox.org/wiki/Downloads
1. **Download** the latest Ubuntu Desktop iso image (v 14.x): http://www.ubuntu.com/download/desktop. (this is about 1GB so may take a while to download)

### Installation
There are two guides you can follow to setup Ubuntu, the quick setup guide or the detailed guide with step by step screenshots.

#### Quick Setup Guide
1. In VirutalBox, click on the New button and name you system "Ubuntu".
1. Select your "Ubuntu" system and click start then at the prompt point VirtualBox to the downloaded Ubuntu iso image.
Complete the Ubuntu installation process.
1. All done - you should now be able to boot into your Ubuntu virtual system!

#### Detailed Setup Guide with a picture for each step
![](images/1.png)

![](images/2.png)

![](images/3.png)

![](images/4.png)

![](images/5.png)

![](images/6.png)

![](images/7.png)

![](images/8.png)

![](images/9.png)

![](images/10.png)

![](images/11.png)

![](images/12.png)

![](images/13.png)

![](images/14.png)

After this, your system should install and then reboot into Ubuntu!
