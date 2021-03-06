Keystroke
=========

This is my keystroke visualization tool for Linux.

Status
------

This is an early prototype, it is not really released yet, but it is working for
me.
I provide it in the sense of "release early, release often", because I hope it
might be useful for somebody and to get some feedback.

Things that are missing at the moment:

* more intelligent key display
    * what should be displayed as key-combination and what as a composed key: SHIFt + a = A, CTRL  + c = CTRL-C
    * enable backspace key: this way by pressing backspace the previous typed key will be removed
      instead of simply displaying the backspace symbol
* add keyboard device selection to GUI
* add mouse display. It's named keystroke, but showing mouse buttons is even
  easier than that.

Changelog
---------

14-01-31 - V0.0.1: This version was the first version. It didn't really had a version number, but I made this
    public available to get some first feedback.

14-02-02 - V0.0.2: First real release.

* add version info
* add about dialog
* improved error handling
* add example keyboard mapping for US keyboard
* make the config dialog working (not yet completed). Add "yet not implemented" messages were functionality is
  missing.
* add commandline option to specify keyboard device. This way you can make other keyboards working.
  Default: /dev/input/by-path/platform-i8042-serio-0-event-kbd
* add commandline option to specify keyboard layout (default=de).



Examples:

    # example for USB keyboard
    $ /usr/local/bin/keystroke-gui -d /dev/input/by-path/pci-0000:00:1d.0-usb-0:1.3:1.2-event-kbd

    # example for US keyboard layout
    $ /usr/local/bin/keystroke-gui -l us

Background / Motivation
-----------------------

After searching for a while I didn't find anything that
really works as expected. I wanted something that is not using python, ruby or
any other scripting language with tons of dependencies which just cause runtime
problems. Without going into details, I really prefer compiled languages.
That's why I used C for the key logging part, C++/Qt with QML
to create a nice user interface. (Ok QML is also interpreted, I know. But it works reliable.)

The tricky parts is really key logging which is necessary for this kind of
applications. Normally a key logger is bad thing, at least when it runs without
notice in the background. That's why you need root privileges to start this
program. (more precisely the program must be owned by root with setuid bit set,
it will drop root privileges directly after opening the keyboard device. )

I first investigated KDE and Qt libraries to implement key logging, but there is
no API which supports this. Then I tried X11, but this API is really weired and
I'm not sure if it would be a good idea to use X11, knowing that Wayland is
coming sooner or later. So I thought it could not be too difficult to get the
necessary info directly from the kernel.

Right, this was to solution. Keystroke directly reads the input events from
/dev/input/eventX, which is documented in /usr/src/linux/Documentation/input/input.txt
and other documents in this folder.
Getting this to work was really easy. The kernel provides the scancodes and
already the translated keycodes. The only remaining problem was mapping the
English keycodes to other keyboard layouts, a German qwertz keyboard in my case.
I looked again into X11 for this part but finally came to a much simpler solution.
Providing my own mapping file, e.g. de.map.

This may sound like duplicating code that exists elsewhere, but it isn't.

1. It's a simple plain text file which is easy to understand, so creating other
mappings is easy.
2. For our application we need some other kind of mapping anyway. It's not all
about mapping single characters like 'z' to 'y'.
E.g. if you want to map the keyname "SPACE" to "Leerzeichen".


Screenshots
-----------
![gergap's Vim example screenshot][screenshot]


License
-------

GPLv3

[screenshot]: https://raw.github.com/gergap/keystroke/master/screenshot.png

