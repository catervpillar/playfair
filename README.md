# Playfair Cipher

### Author: Tommaso Catervi

This code has been written for the attainment of the laboratory part of the ["Operating Systems"](http://didattica.cs.unicam.it/doku.php?id=didattica:triennale:so:ay_2021:lab) exam at the [Bacheleror Degree in Computer Science](http://www.cs.unicam.it) at [University of Camerino](http://www.unicam.it/).

It consists of an implementation in the C language of the famous [Playfair Cipher](https://en.wikipedia.org/wiki/Playfair_cipher), a manual symmetric encryption technique invented in 1854 by Charles Wheatstone bearing the name of Lord Playfair for promoting its use.

## Functionalities
This application allows the user to:
- **encode** multiple files using a certain KEYFILE struct
- **decode** multiple files using a certain KEYFILE struct

It can handle large files in short time too (over 50 Mbyte) without any congestion.

## Prerequisites
The required data to build the KEYFILE structure must be stored in a text file with the following format and indenting:

```<alphabet>\r\n```\
```<replacementChar>\r\n```\
```<specialChar>\r\n```\
```<key>\r\n```

where:
- ```<alphabet>``` is a sequence of 25 distinct letters which represent the alphabet to use in the encoding/decoding.
- ```<replacementChar>``` is the replacement char used to replace possible occurrences of the missing character from the alphabet (which is long 25 and not 26).
- ```<specialChar>``` is the special char to use to divide equal letters when forming the digraphs or to add at the end of the message if it has odd length.
- ```<key>``` is the encryption key required for the construction of the Playfair matrix.

The message to encode or decode must be stored in a text file (any occurrences of blank spaces, numbers or special characters will not be considered for the encoding/decoding and therefore will be deleted).

## Encoding and decoding
The correct syntax of the command to encode/decode multiple files is:\
```<playfair> <encode|decode> <keyfile> <outputdir> <file1> ... <filen>```

where:
- ```<encode|decode>``` is the desired action to execute on the input file(s).
- ```<keyfile>``` is the file containg the alphabet and the special chars required for the encoding/decoding.
- ```<outputdir>``` is the output directory where the encoded or decode files will be stored in.
- ```<file1> ... <filen>``` are the files to encode or decode, separated by a blank space.

The result of the encoding process will be a file with the same name of the input file but with the addition of the ```.pf``` extension.\
It will contain the encoded message whose digraphs will be separated by a blank space.
- Example of the encoded file name: ```message -> message.pf```
- Example of the encoded file content: ```AB CD EF GH...```

The result of the decoding process will be a file with the same name of the input file but with the addition of the ```.dec``` extension.\
If the name of the input file contains the ```.pf``` extension, it is deleted.\
The decoded file will contain the decoded message whose digraphs will be separated by a blank space.
- Example of the decoded file name: ```message.pf -> message.dec```
- Example of the decoded file content: ```PD DG MA HB...```

## Additional features
The user can also know the program's version with one of the following commands:
- ```playfair --version```
- ```playfair -v```

Also, a useful quick guide to the program can be displayed with one of the following commands:
- ```playfair --help```
- ```playfair -h```
