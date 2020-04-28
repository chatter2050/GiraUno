
Debian
====================
This directory contains files used to package giraunod/girauno-qt
for Debian-based Linux systems. If you compile giraunod/girauno-qt yourself, there are some useful files here.

## girauno: URI support ##


girauno-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install girauno-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your girauno-qt binary to `/usr/bin`
and the `../../share/pixmaps/girauno128.png` to `/usr/share/pixmaps`

girauno-qt.protocol (KDE)

