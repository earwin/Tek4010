[![Build Status](https://travis-ci.org/rricharz/Tek4010.svg?branch=master)](https://travis-ci.org/rricharz/Tek4010)

# Tektronix 4010 and 4014 Storage Tube Terminal Emulator

This is a [Tektronix 4010 and 4014](https://en.wikipedia.org/wiki/Tektronix_4010) terminal emulator
for the Raspberry Pi (Raspberry Pi 3 or faster) and other Linux systems.

![screen_shot](screendump.png?raw=true "tek4010 screendump")

It can also display historical data for the
[MIT Project MAC](https://en.wikipedia.org/wiki/MIT_Computer_Science_and_Artificial_Intelligence_Laboratory#Project_MAC)
's ARDS (Advanced Remote Display Station):

![ARDS_screen_shot](trek.png?raw=true "tek4010 ARDS screendump")

It makes an effort to emulate the [storage tube display](https://en.wikipedia.org/wiki/Storage_tube)
of the Tektronix 4010, including the bright drawing spot. If the look and feel is not important, you can
use ["xterm"](https://en.wikipedia.org/wiki/Xterm) instead. "xterm" does not support all
graphics modes of the 4014.

It can be used to log into a historical Unix system such as
[2.11 BSD](https://en.wikipedia.org/wiki/Berkeley_Software_Distribution) on the
[PiDP-11](http://obsolescence.wixsite.com/obsolescence/pidp-11)
or a real historical system. It can also be used to display historical plot data.

This [video of a tek4010 demo](https://youtu.be/ioYiu6oUT88) was generated using
[simplescreenrecorder](https://www.maartenbaert.be/simplescreenrecorder). There is also a
video of a an [animation using the tek4010](https://youtu.be/7FMewaoEOmk) and a video showing
[tek4010 alongside the PiDP-11](https://youtu.be/4jZzypvxoHU).

Install the tek4010 emulator from this repo on a Raspberry Pi or Ubuntu. I propose using

	sudo apt-get install git
	git clone git://github.com/rricharz/Tek4010
	cd Tek4010

This allows you to get updates later easily as follows:

	cd Tek4010
	git pull

If you just want the "tek4010" program for the Raspberry Pi, without the source, the original plot files
and the original manuals, you can also go to the
[releases page](https://github.com/rricharz/Tek4010/releases), and just download the latest
"tek4010" program.
        
The compiled "tek4010" program is for a Raspberry Pi. If you are on Ubuntu, do the following to recompile
the program. On the Raspberry Pi you can skip this step.

        sudo apt-get install libgtk-3-dev
        rm tek4010
        make
        
Thanks to Lars Brinkhoff (lars@nocrew.org) to pointing out how easy it is to compile tek4010
on Ubuntu. He also helped me to fix some bugs and proposed many nice features. Don't forget to
recompile the program each time you update from the repository if you are using Ubuntu. In this
case, you will also have to delete the compiled "tek4010" program before you can do a new pull.

There is a file "dodekagon.plt" in the repo, which you can use to test the tek4010 emulator.
"dodekagon.plt" was produced in 2.11 BSD using my program "dodekagon". Type

	./tek4010 -noexit cat dodekagon.plt

Or, for a ARDS display example, type

	./tek4010 -noexit -ARDS cat ardsfiles/trek.pic

If you want to test text output, type for example

	./tek4010 -noexit head -n 32 tek4010.c

If you want to test an animation, type

	./tek4010 cat animation.plt

Don't forget the option "-noexit", which tells tek4010 to stay alive after cat or
head has finished so that you have a chance to look at the output. For a list of
all possible options, see the chapter "Options of the command tek4010" below.

If you want to see a demo of historical Tektronix 4014 plot files, type

	./tek4010 ./demo.sh

There are more Tektronix 4014 plot files in pltfiles/More_pltfiles in this repo. You can find more
ARDS plot files at [larsbrinkhoff/ards-files](https://github.com/larsbrinkhoff/ards-files) in the
folder pictures.

The emulator does use "rsh" or "telnet", because historical Unix systems do not support
the secure ssh protocol, and because ssh does not allow using a virtual emulator such as tek4010
for security reasons. You need therefore to install rsh or telnet on the Raspberry Pi
or Ubuntu running the tek4010 emulator:

	sudo apt-get install rsh-client
or

	sudo apt-get install telnet

If you want to use this emulator together with 2.11 BSD Unix, look also at
[Using the historical Unix 2.11 BSD operating system on the PiDP-11](https://github.com/rricharz/pidp11-2.11bsd.git)

**Log directly into a remote historical Unix operating system**

This can either be a real historical computer, or a virtual system using simh such
as the PiDP-11.

First, you need to test the remote login from your client machine into your historical
system, using

	rsh -l user_name system
or

	telnet system

where "user_name" is the name of the user on the historical operating system, and "system"
is the hostname of this system. If the historical operating system is running using an
emulator, this is NOT the hostname of the system, on which the emulator is running. See
the chapter below if you prefer to log into the system, on which the emulator is
running. For example, type

	rsh -l rene pdp11
or

	telnet pdp11

If this works properly, you can use the tek4010 emulator as follows:

	./tek4010 rsh -l user_name system
or

	./tek4010 telnet system

If the terminal window is closed right away, there is a problem with your rsh or
telnet call. Test it first without tek4010.

The following keys are not transmitted to the Unix system, but are executed locally
in the terminal emulator and clear the persistent screen:

	home
	page up
	page down
	ctrl arrow up
	ctrl arrow left

These keys emulate the "page" key of the Tektronix 4010. You need to use one of these
keys frequently to avoid to get a mess on the screen, as on a real Tektronix 4010.

The hardcopy function on the Tektronix 4010 is emulated with a screen dump.

	ctrl-w	Make a screen dump in current directory using scrot
		Can be typed on the keyboard or sent by the computer during alpha mode

You can also use the following ctrl key function to close tek4010:

	ctrl-q	Close tek4010 window and quit tek4010.

**Log into the system running simh (same or different Raspberry Pi)**

This makes sense, if you have set up a virtual DZ11 for multiple user login, opening a
telnet port for multiplexed terminals. On the PiDP-11 using 2.11 BSD, the distribution software has
already set up port 4000 for 8 multiuser terminals. First, you need to install and test
telnet (2.11 BSD needs to be up and running in multiuser mode):

	sudo apt-get install telnet
	telnet raspi_hostname 4000

or

	telnet localhost 4000

where "raspi_hostname" is the hostname of your system running simh. If you are using telnet
and tek4010 on the same system as the system running simh, use "localhost" instead of
"raspi_hostname". You can even use VNC viewer on your laptop in this case, instead of an
attached keyboard and mouse.

Once this works, you can start tek4010 as follows:

	tek4010 telnet raspi_hostname 4000

or

	tek4010 telnet localhost 4000	

**Log into PiDP-11 running on the same Raspberry Pi, using the console**

This is the least preferred setup, only to be used if you cannot use one of the setups
above. You cannot use the tek4010 emulator running screens, as it is done in the standard setup
of the PiDP using the console, because screens filters the output stream of simh and is
therefore unsuitable for graphics terminals such as the tek4010 emulator. If you don't
want to change the standard setup, use ctrl-e to stop simh, and then "exit" to quit simh.

Because tek4010 needs rsh, you need to install rsh-server and rsh-client on
the Raspberry Pi. You cannot use telnet here.

	sudo apt-get install rsh-server
	sudo apt-get install rsh-client

Now start tek4010 as follows:

	./tek4010 rsh -l pi localhost

This should give you a login prompt into your Raspberry Pi. If not, test the rsh call first.

Once your password has been accepted, be prepared to use the "home" key or any of the other
keys described above frequently to avoid to get a mess on the dump 4010 terminal emulator!
The following will start the PiDP software without using screens:

	cd /opt/pidp11/bin
	./pidp11.sh

Everything should run as expected, and you should be able to use the tek4010 terminal emulator with any of
the historical operating systems.

One word of caution! If you run the PiDP-11 software this way without using screens, you SHOULD
NOT detach or quit the terminal while your historical operating system is running, because
this will kill the PiDP-11 simh emulator right away. First run down your historical operating
system and simh properly, before detaching the terminal emulator!

**Options of the command tek4010**

Call the command tek4010 using the following syntax:

	tek4010 [options of tek4010] command [options of command]

"command" is a mandatory command to be run by tek4010, such as telnet, rsh or cat.

tek4010 has the following options:

	-noexit		do not close window after completion of "command"

	-raw		do not execute an automatic CR (carriage return) after a LF (line feed)

	-tab1		execute a blank	instead of a tab to the next 8-character column

	-b9600, -b4800, -b2400, -b1200, -b600, -b300
			Emulate a baud rate. Without one of these arguments, the baud rate
			is 19200 baud. The original Tektronix 4010 had a maximal baud rate
			of 9600 baud. With the small baud rates you can emulate 1970s 
			style modem performance. Early modems had a baud rate of 300.

	-full		in this mode the tek4010 emulator creates a full screen window, and
			uses the full resolution of the 4014 with the enhanced graphics module
			installed, scaled down to the actual window size. Use ctrl-q to
			close the tek4010 window.

	-ARDS		display ARDS data

	-APL		emulate Tektronix 4013/4015 with alternative APL character set.
			This mode is experimental. Details see below.

**APL mode**

If tek4010 is called with the -APL argument, a Tektronix 4013 and Tektronix 4015 is emulated
with the alternative APL character set. In this mode, the following ctrl keyboard characters
are active:

	ctrl-n	Switch to APL character set
	ctrl-o	Switch to normal character set

In this case one can also send "ESC ctrl-n" and "ESC ctrl-o" from the computer to switch
the character set.

If you want to use the APL mode, you need to install the Apl385 font. Starting from the Tek4010
directory, type

	cd apl
	sudo install_apl

You should see the following line displayed:

        /usr/share/fonts/truetype/apl385/Apl385.ttf: APL385 Unicode:style=Regular

While still being in the apl directory, you can test the APL character set using

	../tek4010 -APL -noexit ./apltest
        
While the second (APL) character set is displayed, it is also possible to translate any key
on your keyboard displaying a printable character (ASCII codes between 32 and 127) to any other
printable character. The file "aplkeys" in the folder "apl" provides an example of such a conversion
table. The first row in this file is the ASCII code of the key, and the second the translated code.
It is even possible to produce overstike glyphs by adding a second code multiplied by 256. You
can modify this table to match your keyboard and country code. You can obtain the codes from the
screenshot below. To install the "aplkeys" table, type

        mkdir ~/.tek4010conf
        cp aplkeys ~/.tek4010conf

![character sets](characterset.png?raw=true "tek4010 character sets")

**Reporting problems**

If everything works properly for you, but your graphics application produces garbage on the
tek4010 emulator, you can send me your data as follows: On a historical Unix system, type

	your_graphics_program > captured_data.plt

I don't know how this can be done on other operating systems. You can then mail your
captured_data file together with a description of the problem to rricharz77@gmail.com.
Pack it with zip or something else to make sure that the mailing program does not alter it.

If you are registered on github, you can also open an issue.

**Screen resolution**

This tek4010 emulator creates a graphics window of 1024x780 points, which is the display size
of the Tektronix 4010 terminal and the Tektronix 4014 terminal without enhanced graphics module.
The Raspberry Pi can handle
sufficiently high refresh rates at this resolution. This emulator executes
Tektronix 4014 graphics code with the enhanced graphics module installed, so that such
graphics codes can be displayed using this terminal emulator, but the lowest two bits of
each axis are not used in this case, as in the Tektronix 4014 without the enhanced graphics
module.

If called with the -full option, the tek4010 emulator creates creates a full screen window,
and uses the full 4K resolution of the 4014 with enhanced graphics
module installed, scaled down to the actual window size.
Use ctrl-q to close the tek4010 window.

**Compiling the tek4010 project**

If you want to compile the project, you need to install "libgtk-3-dev":

	sudo apt-get install libgtk-3-dev

There is a make file in the repo.

**Using tek4010 on OSX and Windows using VirtualBox and Ubuntu**

It is possible to run tek4010 in a virtual Ubuntu environment on OSX or Windows. I found that in
such virtual environments the raw CPU speed is usually higher than on a Raspberry Pi, but the
actual frame rates are sometimes slower. I have made a substantial effort to make sure that the bright
spot animations also look good in environments with rather slow frame rates, but do not expect a
miracle. Emulating a storage tube display on a machine with limited frame rate has its limitations.

**Version**

See [versions.txt](versions.txt)

**Manuals**

The manuals of the historical terminals are available in the [manuals folder](manuals)

**Historically interesting facts about the ARDS terminal**

The ARDS was a pioneering storage tube display terminal. It could already use a 3 button
mouse as the graphical input device, as this 1971 thesis shows:
Rhine, George Irvin Jr., "A hardware and software interface between a graphics
terminal and the SCC 650 computer" (1971), Masters Theses, 5508, page 21,
http://scholarsmine.mst.edu/masters_theses/5508

A picture of an ARDS I display with a quite modern looking mouse was published in Computing
Surveys, Vol. 2, No. 4, December 1970, page 272,
http://sci-hub.tw/https://dl.acm.org/citation.cfm?id=356582&dl=ACM&coll=DL

Detailed pictures of the terminal and the original mouse built by CDI can be found in the 1968
ARDS manual (see manuals folder)

**Help wanted**

I am interested to find any recoverable original software using the graphical input modes of the
Tektronix 4010, 4014 or the ARDS. Please open an issue in this repository or write to
rricharz77@gmail.com if you are able to help.

**Contributors**

The storage tube emulator and the Tektronix 4010/4014 decoder were witten by Rene Richarz.
The ARDS decoder was written by Lars Brinkhoff. He also provided some interesting historical documents
and the ARDS plot files.
The historical plot data for the Tektronix 4014 was obtained from Jos Dreesen.
Thanks to Ian Schofield for his critical comments and a code snippet for drawing dashed and dotted lines,
and to Oscar Vermeulen for his support.
The manuals were obtained from bitsavers.org.
Thanks also to all others who contributed important ideas, helped with the debugging and preserved
the historical data. This program is the result of a community effort.


