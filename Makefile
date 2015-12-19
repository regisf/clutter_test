#
# Makefile to compile the test program. 
#
# Pleasure ensure that clutter-devel or clutter-dev is installed on your system
#
all:
	gcc -o clutter_1000_sprites clutter_1000_sprites.c `pkg-config clutter-1.0 --libs --cflags`

