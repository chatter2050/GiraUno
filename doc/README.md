Girauno 0.9.4 BETA
=====================

Copyright (c) 2009-2015 Girauno Developers


Setup
---------------------
[Girauno Core](http://girauno.org/en/download) is the original Girauno client and it builds the backbone of the network. However, it downloads and stores the entire history of Girauno transactions (which is currently several GBs); depending on the speed of your computer and network connection, the synchronization process can take anywhere from a few hours to a day or more. Thankfully you only have to do this once. If you would like the process to go faster you can [download the blockchain directly](bootstrap.md).

Running
---------------------
The following are some helpful notes on how to run Girauno on your native platform. 

### Unix

You need the Qt4 run-time libraries to run Girauno-Qt. On Debian or Ubuntu:

	sudo apt-get install libqtgui4

Unpack the files into a directory and run:

- bin/32/girauno-qt (GUI, 32-bit) or bin/32/giraunod (headless, 32-bit)
- bin/64/girauno-qt (GUI, 64-bit) or bin/64/giraunod (headless, 64-bit)



### Windows

Unpack the files into a directory, and then run girauno-qt.exe.

### OSX

Drag Girauno-Qt to your applications folder, and then run Girauno-Qt.

### Need Help?

* See the documentation at the [Girauno Wiki](https://en.girauno.it/wiki/Main_Page)
for help and more information.
* Ask for help on [#girauno](http://webchat.freenode.net?channels=girauno) on Freenode. If you don't have an IRC client use [webchat here](http://webchat.freenode.net?channels=girauno).
* Ask for help on the [GiraunoTalk](https://giraunotalk.org/) forums, in the [Technical Support board](https://giraunotalk.org/index.php?board=4.0).

Building
---------------------
The following are developer notes on how to build Girauno on your native platform. They are not complete guides, but include notes on the necessary libraries, compile flags, etc.

- [OSX Build Notes](build-osx.md)
- [Unix Build Notes](build-unix.md)
- [Windows Build Notes](build-msw.md)

Development
---------------------
The Girauno repo's [root README](https://github.com/girauno/girauno/blob/master/README.md) contains relevant information on the development process and automated testing.

- [Coding Guidelines](coding.md)
- [Multiwallet Qt Development](multiwallet-qt.md)
- [Release Notes](release-notes.md)
- [Release Process](release-process.md)
- [Source Code Documentation (External Link)](https://dev.visucore.com/girauno/doxygen/)
- [Translation Process](translation_process.md)
- [Unit Tests](unit-tests.md)

### Resources
* Discuss on the [GiraunoTalk](https://giraunotalk.org/) forums, in the [Development & Technical Discussion board](https://giraunotalk.org/index.php?board=6.0).
* Discuss on [#girauno-dev](http://webchat.freenode.net/?channels=girauno) on Freenode. If you don't have an IRC client use [webchat here](http://webchat.freenode.net/?channels=girauno-dev).

### Miscellaneous
- [Assets Attribution](assets-attribution.md)
- [Files](files.md)
- [Tor Support](tor.md)

License
---------------------
Distributed under the [MIT/X11 software license](http://www.opensource.org/licenses/mit-license.php).
This product includes software developed by the OpenSSL Project for use in the [OpenSSL Toolkit](http://www.openssl.org/). This product includes
cryptographic software written by Eric Young ([eay@cryptsoft.com](mailto:eay@cryptsoft.com)), and UPnP software written by Thomas Bernard.
