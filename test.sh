#!/bin/zsh

mkdir -p test_tmp


echo "Summary: This project is a continuation of the previous encryption project. You will recode part of the OpenSSL program, specifically BASE64, DES-ECB and DES-CBC." > test_tmp/f1
for e in {0..100} ; do cat test_tmp/f1 | head -c $e > test_tmp/f_$e ; done


# # ECB
echo " ECB Test encode without salted and without base64"
for e in {0..100} ; do echo "$e :"; ./ft_ssl des-ecb -i test_tmp/f_$e -o test_tmp/ft_ssl_$e -k 10 ; openssl des-ecb -in test_tmp/f_$e -out test_tmp/openssl_$e -K 10 ; diff test_tmp/ft_ssl_$e  test_tmp/openssl_$e; done

echo " ECB Test encode with salted and without base64"
for e in {0..100} ; do echo "$e :"; ./ft_ssl des-ecb -i test_tmp/f_$e -o test_tmp/ft_ssl_$e -p password -s 10 ; openssl des-ecb -in test_tmp/f_$e -out test_tmp/openssl_$e -k password -S 10 ; diff test_tmp/ft_ssl_$e  test_tmp/openssl_$e; done

echo " ECB Test encode without salted and with base64"
for e in {0..100} ; do echo "$e :"; ./ft_ssl des-ecb -a -i test_tmp/f_$e -o test_tmp/ft_ssl_$e -k 10 ; openssl des-ecb -a -in test_tmp/f_$e -out test_tmp/openssl_$e -K 10 ; diff test_tmp/ft_ssl_$e  test_tmp/openssl_$e; done

echo " ECB Test encode with salted and with base64"
for e in {0..100} ; do echo "$e :"; ./ft_ssl des-ecb -a -i test_tmp/f_$e -o test_tmp/ft_ssl_$e -p password -s 10 ; openssl des-ecb -a -in test_tmp/f_$e -out test_tmp/openssl_$e -k password -S 10 ; diff test_tmp/ft_ssl_$e  test_tmp/openssl_$e; done

echo " ECB Test decode without salted and without base64"
for e in {0..100} ; do echo "$e :"; ./ft_ssl des-ecb -i test_tmp/f_$e -o test_tmp/ft_ssl_$e -k 10 ; ./ft_ssl des-ecb -d -i test_tmp/ft_ssl_$e -o test_tmp/ft_ssl_decode_$e -k 10; openssl des-ecb -d -in test_tmp/ft_ssl_$e -out test_tmp/openssl_decode_$e -K 10 ; diff test_tmp/ft_ssl_decode_$e  test_tmp/openssl_decode_$e; done

echo " ECB Test decode with salted and without base64"
for e in {0..100} ; do echo "$e :"; ./ft_ssl des-ecb -i test_tmp/f_$e -o test_tmp/ft_ssl_$e -p password -s 10 ; ./ft_ssl des-ecb -d -i test_tmp/ft_ssl_$e -o test_tmp/ft_ssl_decode_$e -p password -s 10; openssl des-ecb -d -in test_tmp/ft_ssl_$e -out test_tmp/openssl_decode_$e -k password -S 10 ; diff test_tmp/ft_ssl_decode_$e  test_tmp/openssl_decode_$e; done

echo " ECB Test decode without salted and with base64"
for e in {0..100} ; do echo "$e :"; ./ft_ssl des-ecb -a -i test_tmp/f_$e -o test_tmp/ft_ssl_$e -k 10 ; ./ft_ssl des-ecb -d -a -i test_tmp/ft_ssl_$e -o test_tmp/ft_ssl_decode_$e -k 10; openssl des-ecb -d -a -in test_tmp/ft_ssl_$e -out test_tmp/openssl_decode_$e -K 10 ; diff test_tmp/ft_ssl_decode_$e  test_tmp/openssl_decode_$e; done

echo " ECB Test decode with salted and with base64"
for e in {0..100} ; do echo "$e :"; ./ft_ssl des-ecb -a -i test_tmp/f_$e -o test_tmp/ft_ssl_$e -p password -s 10 ; ./ft_ssl des-ecb -d -a -i test_tmp/ft_ssl_$e -o test_tmp/ft_ssl_decode_$e -p password -s 10; openssl des-ecb -d -a -in test_tmp/ft_ssl_$e -out test_tmp/openssl_decode_$e -k password -S 10; diff test_tmp/ft_ssl_decode_$e  test_tmp/openssl_decode_$e; done

# # CBC
echo "CBC Test encode without salted and without base64"
for e in {0..100} ; do echo "$e :"; ./ft_ssl des-cbc -i test_tmp/f_$e -o test_tmp/ft_ssl_$e -k 10 -v 255445 ; openssl des-cbc -in test_tmp/f_$e -out test_tmp/openssl_$e -K 10 -iv 255445 ; diff test_tmp/ft_ssl_$e  test_tmp/openssl_$e; done

echo "CBC Test encode with salted and without base64"
for e in {0..100} ; do echo "$e :"; ./ft_ssl des-cbc -i test_tmp/f_$e -o test_tmp/ft_ssl_$e -p password -s 10 -v 255445 ; openssl des-cbc -in test_tmp/f_$e -out test_tmp/openssl_$e -k password -S 10 -iv 255445; diff test_tmp/ft_ssl_$e  test_tmp/openssl_$e; done

echo "CBC Test encode without salted and with base64"
for e in {0..100} ; do echo "$e :"; ./ft_ssl des-cbc -a -i test_tmp/f_$e -o test_tmp/ft_ssl_$e -k 10 -v 255445 ; openssl des-cbc -a -in test_tmp/f_$e -out test_tmp/openssl_$e -K 10 -iv 255445; diff test_tmp/ft_ssl_$e  test_tmp/openssl_$e; done

echo "CBC Test encode with salted and with base64"
for e in {0..100} ; do echo "$e :"; ./ft_ssl des-cbc -a -i test_tmp/f_$e -o test_tmp/ft_ssl_$e -p password -s 10 -v 255445 ; openssl des-cbc -a -in test_tmp/f_$e -out test_tmp/openssl_$e -k password -S 10 -iv 255445; diff test_tmp/ft_ssl_$e  test_tmp/openssl_$e; done

echo "CBC Test decode without salted and without base64"
for e in {0..100} ; do echo "$e :"; ./ft_ssl des-cbc -i test_tmp/f_$e -o test_tmp/ft_ssl_$e -k 10 -v 255445 ; ./ft_ssl des-cbc -d -i test_tmp/ft_ssl_$e -o test_tmp/ft_ssl_decode_$e -k 10 -v 255445; openssl des-cbc -d -in test_tmp/ft_ssl_$e -out test_tmp/openssl_decode_$e -K 10 -iv 255445; diff test_tmp/ft_ssl_decode_$e  test_tmp/openssl_decode_$e; done

echo "CBC Test decode with salted and without base64"
for e in {0..100} ; do echo "$e :"; ./ft_ssl des-cbc -i test_tmp/f_$e -o test_tmp/ft_ssl_$e -p password -s 10 -v 255445; ./ft_ssl des-cbc -d -i test_tmp/ft_ssl_$e -o test_tmp/ft_ssl_decode_$e -p password -s 10 -v 255445; openssl des-cbc -d -in test_tmp/ft_ssl_$e -out test_tmp/openssl_decode_$e -k password -S 10 -iv 255445; diff test_tmp/ft_ssl_decode_$e  test_tmp/openssl_decode_$e; done

echo "CBC Test decode without salted and with base64"
for e in {0..100} ; do echo "$e :"; ./ft_ssl des-cbc -a -i test_tmp/f_$e -o test_tmp/ft_ssl_$e -k 10 -v 255445 ; ./ft_ssl des-cbc -d -a -i test_tmp/ft_ssl_$e -o test_tmp/ft_ssl_decode_$e -k 10 -v 255445; openssl des-cbc -d -a -in test_tmp/ft_ssl_$e -out test_tmp/openssl_decode_$e -K 10 -iv 255445; diff test_tmp/ft_ssl_decode_$e  test_tmp/openssl_decode_$e; done

echo "CBC Test decode with salted and with base64"
for e in {0..100} ; do echo "$e :"; ./ft_ssl des-cbc -a -i test_tmp/f_$e -o test_tmp/ft_ssl_$e -p password -s 10 -v 255445 ; ./ft_ssl des-cbc -d -a -i test_tmp/ft_ssl_$e -o test_tmp/ft_ssl_decode_$e -p password -s 10 -v 255445; openssl des-cbc -d -a -in test_tmp/ft_ssl_$e -out test_tmp/openssl_decode_$e -k password -S 10 -iv 255445; diff test_tmp/ft_ssl_decode_$e  test_tmp/openssl_decode_$e; done


# # OFB
echo "OFB Test encode without salted and without base64"
for e in {0..100} ; do echo "$e :"; ./ft_ssl des-ofb -i test_tmp/f_$e -o test_tmp/ft_ssl_$e -k 10 -v 255445 ; openssl des-ofb -in test_tmp/f_$e -out test_tmp/openssl_$e -K 10 -iv 255445 ; diff test_tmp/ft_ssl_$e  test_tmp/openssl_$e; done

echo "OFB Test encode with salted and without base64"
for e in {0..100} ; do echo "$e :"; ./ft_ssl des-ofb -i test_tmp/f_$e -o test_tmp/ft_ssl_$e -p password -s 10 -v 255445 ; openssl des-ofb -in test_tmp/f_$e -out test_tmp/openssl_$e -k password -S 10 -iv 255445; diff test_tmp/ft_ssl_$e  test_tmp/openssl_$e; done

echo "OFB Test encode without salted and with base64"
for e in {0..100} ; do echo "$e :"; ./ft_ssl des-ofb -a -i test_tmp/f_$e -o test_tmp/ft_ssl_$e -k 10 -v 255445 ; openssl des-ofb -a -in test_tmp/f_$e -out test_tmp/openssl_$e -K 10 -iv 255445; diff test_tmp/ft_ssl_$e  test_tmp/openssl_$e; done

echo "OFB Test encode with salted and with base64"
for e in {0..100} ; do echo "$e :"; ./ft_ssl des-ofb -a -i test_tmp/f_$e -o test_tmp/ft_ssl_$e -p password -s 10 -v 255445 ; openssl des-ofb -a -in test_tmp/f_$e -out test_tmp/openssl_$e -k password -S 10 -iv 255445; diff test_tmp/ft_ssl_$e  test_tmp/openssl_$e; done

echo "OFB Test decode without salted and without base64"
for e in {0..100} ; do echo "$e :"; ./ft_ssl des-ofb -i test_tmp/f_$e -o test_tmp/ft_ssl_$e -k 10 -v 255445 ; ./ft_ssl des-ofb -d -i test_tmp/ft_ssl_$e -o test_tmp/ft_ssl_decode_$e -k 10 -v 255445; openssl des-ofb -d -in test_tmp/ft_ssl_$e -out test_tmp/openssl_decode_$e -K 10 -iv 255445; diff test_tmp/ft_ssl_decode_$e  test_tmp/openssl_decode_$e; done

echo "OFB Test decode with salted and without base64"
for e in {0..100} ; do echo "$e :"; ./ft_ssl des-ofb -i test_tmp/f_$e -o test_tmp/ft_ssl_$e -p password -s 10 -v 255445; ./ft_ssl des-ofb -d -i test_tmp/ft_ssl_$e -o test_tmp/ft_ssl_decode_$e -p password -s 10 -v 255445; openssl des-ofb -d -in test_tmp/ft_ssl_$e -out test_tmp/openssl_decode_$e -k password -S 10 -iv 255445; diff test_tmp/ft_ssl_decode_$e  test_tmp/openssl_decode_$e; done

echo "OFB Test decode without salted and with base64"
for e in {0..100} ; do echo "$e :"; ./ft_ssl des-ofb -a -i test_tmp/f_$e -o test_tmp/ft_ssl_$e -k 10 -v 255445 ; ./ft_ssl des-ofb -d -a -i test_tmp/ft_ssl_$e -o test_tmp/ft_ssl_decode_$e -k 10 -v 255445; openssl des-ofb -d -a -in test_tmp/ft_ssl_$e -out test_tmp/openssl_decode_$e -K 10 -iv 255445; diff test_tmp/ft_ssl_decode_$e  test_tmp/openssl_decode_$e; done

echo "OFB Test decode with salted and with base64"
for e in {0..100} ; do echo "$e :"; ./ft_ssl des-ofb -a -i test_tmp/f_$e -o test_tmp/ft_ssl_$e -p password -s 10 -v 255445 ; ./ft_ssl des-ofb -d -a -i test_tmp/ft_ssl_$e -o test_tmp/ft_ssl_decode_$e -p password -s 10 -v 255445; openssl des-ofb -d -a -in test_tmp/ft_ssl_$e -out test_tmp/openssl_decode_$e -k password -S 10 -iv 255445; diff test_tmp/ft_ssl_decode_$e  test_tmp/openssl_decode_$e; done

# # CTR ok
echo "CTR Test decode without salted and without base64"
for e in {0..100} ; do echo "$e :"; ./ft_ssl des-ctr -i test_tmp/f_$e -o test_tmp/ft_ssl_$e -k 10 -v 255445 ; ./ft_ssl des-ctr -d -i test_tmp/ft_ssl_$e -o test_tmp/ft_ssl_decode_$e -k 10 -v 255445; diff test_tmp/ft_ssl_decode_$e  test_tmp/f_$e; done

echo "CTR Test decode with salted and without base64"
for e in {0..100} ; do echo "$e :"; ./ft_ssl des-ctr -i test_tmp/f_$e -o test_tmp/ft_ssl_$e -p password -s 10 -v 255445; ./ft_ssl des-ctr -d -i test_tmp/ft_ssl_$e -o test_tmp/ft_ssl_decode_$e -p password -s 10 -v 255445; diff test_tmp/ft_ssl_decode_$e  test_tmp/f_$e; done

echo "CTR Test decode without salted and with base64"
for e in {0..100} ; do echo "$e :"; ./ft_ssl des-ctr -a -i test_tmp/f_$e -o test_tmp/ft_ssl_$e -k 10 -v 255445 ; ./ft_ssl des-ctr -d -a -i test_tmp/ft_ssl_$e -o test_tmp/ft_ssl_decode_$e -k 10 -v 255445; diff test_tmp/ft_ssl_decode_$e  test_tmp/f_$e; done

echo "CTR Test decode with salted and with base64"
for e in {0..100} ; do echo "$e :"; ./ft_ssl des-ctr -a -i test_tmp/f_$e -o test_tmp/ft_ssl_$e -p password -s 10 -v 255445 ; ./ft_ssl des-ctr -d -a -i test_tmp/ft_ssl_$e -o test_tmp/ft_ssl_decode_$e -p password -s 10 -v 255445; diff test_tmp/ft_ssl_decode_$e  test_tmp/f_$e; done


# # PCBC
echo "PCBC Test decode without salted and without base64"
for e in {0..100} ; do echo "$e :"; ./ft_ssl des-pcbc -i test_tmp/f_$e -o test_tmp/ft_ssl_$e -k 10 -v 255445 ; ./ft_ssl des-pcbc -d -i test_tmp/ft_ssl_$e -o test_tmp/ft_ssl_decode_$e -k 10 -v 255445; diff test_tmp/ft_ssl_decode_$e  test_tmp/f_$e; done

echo "PCBC Test decode with salted and without base64"
for e in {0..100} ; do echo "$e :"; ./ft_ssl des-pcbc -i test_tmp/f_$e -o test_tmp/ft_ssl_$e -p password -s 10 -v 255445; ./ft_ssl des-pcbc -d -i test_tmp/ft_ssl_$e -o test_tmp/ft_ssl_decode_$e -p password -s 10 -v 255445; diff test_tmp/ft_ssl_decode_$e  test_tmp/f_$e; done

echo "PCBC Test decode without salted and with base64"
for e in {0..100} ; do echo "$e :"; ./ft_ssl des-pcbc -a -i test_tmp/f_$e -o test_tmp/ft_ssl_$e -k 10 -v 255445 ; ./ft_ssl des-pcbc -d -a -i test_tmp/ft_ssl_$e -o test_tmp/ft_ssl_decode_$e -k 10 -v 255445; diff test_tmp/ft_ssl_decode_$e  test_tmp/f_$e; done

echo "PCBC Test decode with salted and with base64"
for e in {0..100} ; do echo "$e :"; ./ft_ssl des-pcbc -a -i test_tmp/f_$e -o test_tmp/ft_ssl_$e -p password -s 10 -v 255445 ; ./ft_ssl des-pcbc -d -a -i test_tmp/ft_ssl_$e -o test_tmp/ft_ssl_decode_$e -p password -s 10 -v 255445; diff test_tmp/ft_ssl_decode_$e  test_tmp/f_$e; done


# # CFB
echo "CFB Test decode without salted and without base64"
for e in {0..100} ; do echo "$e :"; ./ft_ssl des-cfb -i test_tmp/f_$e -o test_tmp/ft_ssl_$e -k 10 -v 255445 ; ./ft_ssl des-cfb -d -i test_tmp/ft_ssl_$e -o test_tmp/ft_ssl_decode_$e -k 10 -v 255445; diff test_tmp/ft_ssl_decode_$e  test_tmp/f_$e; done

echo "CFB Test decode with salted and without base64"
for e in {0..100} ; do echo "$e :"; ./ft_ssl des-cfb -i test_tmp/f_$e -o test_tmp/ft_ssl_$e -p password -s 10 -v 255445; ./ft_ssl des-cfb -d -i test_tmp/ft_ssl_$e -o test_tmp/ft_ssl_decode_$e -p password -s 10 -v 255445; diff test_tmp/ft_ssl_decode_$e  test_tmp/f_$e; done

echo "CFB Test decode without salted and with base64"
for e in {0..100} ; do echo "$e :"; ./ft_ssl des-cfb -a -i test_tmp/f_$e -o test_tmp/ft_ssl_$e -k 10 -v 255445 ; ./ft_ssl des-cfb -d -a -i test_tmp/ft_ssl_$e -o test_tmp/ft_ssl_decode_$e -k 10 -v 255445; diff test_tmp/ft_ssl_decode_$e  test_tmp/f_$e; done

echo "CFB Test decode with salted and with base64"
for e in {0..100} ; do echo "$e :"; ./ft_ssl des-cfb -a -i test_tmp/f_$e -o test_tmp/ft_ssl_$e -p password -s 10 -v 255445 ; ./ft_ssl des-cfb -d -a -i test_tmp/ft_ssl_$e -o test_tmp/ft_ssl_decode_$e -p password -s 10 -v 255445; diff test_tmp/ft_ssl_decode_$e  test_tmp/f_$e; done
