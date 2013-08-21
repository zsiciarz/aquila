What is Aquila?
===============

Aquila is an open source and cross-platform DSP (Digital Signal Processing)
library for C++11.


Features
========

 * various signal sources (generators, text/binary/WAVE files)
 * signal windowing and filtering
 * performing operations on a frame-by-frame basis
 * calculating energy, power, FFT and DCT of a signal
 * feature extraction, including MFCC and HFCC features, widely used in
   speech recognition
 * pattern matching with DTW (dynamic time warping) algorithm


Requirements
============

The following dependencies are required to build the library from source.

 * CMake > 2.6


License
=======

The library is licensed under the MIT (X11) license. A copy of the license
is distributed with the library in the LICENSE file.


Authors
=======

Zbigniew Siciarz <antyqjon@interia.pl>

This library includes code from Takuya Ooura's mathematical software packages,
which are available at http://www.kurims.kyoto-u.ac.jp/~ooura/.
