# HelioBoard

This powers the lightboard component of the Helioz Soundnasium. Must be run in conjunction with the [AudioMixServer](https://github.com/helioz-camp/audiomixserver). This is crappy code, but hey, it works! Here's how you run everything:
```
sudo apt-get install cmake librtmidi-dev
touch sounds.txt # create a file with a sound filename on each line (320 of em)
cmake .
make
./helioboard [address of audioxmiserver] [prefix for sound files]
```
That's it!
