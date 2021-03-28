# Playfair cipher

#### Author: Tommaso Catervi

This code has been written for the attainment of the laboratory part of the ["Operating Systems"](http://didattica.cs.unicam.it/doku.php?id=didattica:triennale:so:ay_2021:lab) exam at the [Bacheleror Degree in Computer Science](http://www.cs.unicam.it) at [University of Camerino](http://www.unicam.it/).

It consists of an implementation of the famous [Playfair Cipher](https://en.wikipedia.org/wiki/Playfair_cipher), a manual symmetric encryption technique invented in 1854 by Charles Wheatstone bearing the name of Lord Playfair for promoting its use.

This application allows the user to encode and decode multiple files using a certain KEYFILE, producing correspondent ".pf" files as a result of the encoding and ".dec" files as a result of the decoding.

The correct syntax of the command to encode/decode is:\
```<playfair> <encode|decode> <keyfile> <outputdir> <file1> ... <filen>```

where:
- ```<encode|decode>``` is the desired action to execute on the input file(s).
- ```<keyfile>``` is the file containg the alphabet and the special chars required for the encoding/decoding.
- ```<outputdir>``` is the output directory where the encoded or decode files will be stored in.
- ```<file1> ... <filen>``` are the files to encode or decode, separated by a space.
