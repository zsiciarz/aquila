What is Aquila?
===============

Aquila is an open source and cross-platform DSP (Digital Signal Processing)
library for C++11.


Features
========

 * reading input files in WAVE format, 8 or 16-bit per sample, mono or stereo,
   with almost any sample frequency
 * dividing input signals into short frames and applying mathematical
   transformations to each frame
 * calculating energy, power, FFT and DCT of a signal
 * feature extraction, including MFCC and HFCC features, widely used in
   speech recognition
 * a simple DTW (dynamic time warping) pattern matching algorithm which
   also can be used for recognition


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
