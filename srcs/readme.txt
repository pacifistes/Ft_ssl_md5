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
• -d, decode mode
• -e, encode mode (default)
• -i, input file
• -o, output file
base 64 -o file  fileToReadOrStrind
base 64 -i fileToRead
base 64 -o fileToRead -i file
base 64 -i file -o fileToRead
quand tu encode :
    in  rajoute un \n tout les 64 character ecrit
quand tu decode ;
    lis de 64 en 64 et reaffiche sans le \n supprime les espace, tab etc
    affiche le bloc de 64,Si il y a un probleme sur un bloc (charactere incorrect) on arrete

Invalid character in input stream.


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

Key FF12CD0000000000

salt 64 bit
key 64bit
KeyLonger are trunc
kEYSHOer FF1 becomes FF10000000000000

A 64-bit long block. If a block is too short, pad it with the size difference byte
padding scheme, the same as OpenSSL.






Si base64 :
	encode de 48 en 48 et return 64 char
	decode de 64 en 64 et return 48 char

Si	des :
    Si pas de cle
        si pas de password
            AskPasswors
        Si cbc et pas de iv
            generate iv
        else
            si iv incorect
            sinon register
        si pas de salt
            generate  salt
        else
            si salt incorect
            sinon register
        generate cle
        
    else
        Si cle incorect
    register cle
    while (64 en 64)
    {

    }
