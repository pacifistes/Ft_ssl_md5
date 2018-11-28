options are
MD5 / SHA256
-c   to output the digest with separating colons
-d   to display blocs's info
-p   echo STDIN to STDOUT and append the checksum to STDOUT
-q   quiet mode
-r   reverse the format of the output
-s   print the sum of the given string

 getpass (or readpassphrase or getch)


 Base64

base 64 -o file  fileToReadOrStrind
base 64 -i fileToRead
• -d, decode mode
• -e, encode mode (default)
• -i, input file
• -o, output file


 Data Encryption Standard (DES) 
 des is an alias for des-cbc in OpenSSL.
 -a, decode/encode the input/output in base64, depending on the encrypt mode
• -d, decrypt mode
• -e, encrypt mode (default)
• -i, input file for message
• -k, key in hex is the next arguement.
(Behave like openssl des -K not openssl des -k)
• -o, output file for message
• -p, password in ascii is the next argument.
(Behave like a modifiedd openssl des -pass not like openssl des -p or -P)
(A verbose explanation is given in the next section)
• -s, the salt in hex is the next argument.
(Behave like openssl des -S)
• -v, initialization vector in hex is the next argument.
(Behave like openssl des -iv not openssl des -v)