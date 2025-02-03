# Playing around with OpenSSL certs

For the longest time I really didn't understand SSL certs. I understood at the highest level what they were used for but really didn't get the ins and outs

Recently for work we've been chatting about being able to trust everything explicitly, and because of that I've looked into how to sign and verify the integrity of a file. The idea being that we can use a public cert to verify the contents of a file to make sure it definitely comes from a trusted source.

## Useful note

You can use `base64` to encode the output from a terminal. I had a signature of a file and this is the output

```
richard@UKCARL-7LNZC44:~/temp/self-signed-ssl-cert$ cat testfile.txt.sig
4r�@�e;F+�E>v�',,������̅B;��O)P�kkff�W�JG���5pNK����M�V��a��
R}a�V���pǚ�XZ�s;�       ��B��{N��A[�Sr!���w�i-"��zK�a�=�Y��/R��{��oZH;ڮ2�me��a��f�s��͸UGS���tK*��d�C�z��a
���*�6��O���w|(G^u��_�@�L����^a�
?y�C��P����j�:�R�Vx_*�=
richard@UKCARL-7LNZC44:~/temp/self-signed-ssl-cert$ cat testfile.txt.sig | base64
NHLhQPZlO0YbJporr0U+dpInLCzKBQKE+szbARnum8yFQh07ju5PKVAOkWtrZmaPV5ZKRwfAj7I1
cE5Ludf+zU3IVp6vYefFClJ9YbVW0hioynDHmo9Yf1rrczvACQIHk7xCyfCpe07n0g5BW6RTciEO
mbzMd/dpLSLN53pL5GHTPR+vWb3wL1Km8Xuiuh9vWkg72q4yAdVtFmUW7PVh4IOHZrxz/6HNuFUP
RwRTh/GfkfJ0Syrr5GSwQ896qvRhCvuSuSq4NpjPT4urgnd8KEdedaKyXxTtQPVMjPOb2B79XmHu
Cj95iEP591C68MryaoU68lITEoBWeBvHXyrZPQ==
```
Not super useful but a good translator. I think there is a similar thing for `json`
## Why

SSL and TLS are used for 2 main reasons

* Authentication - is the site who they say they are? Can they be verified?
* Encryption - How to communicate with the site? What encryption do they use?

## Generating Certs

Mostly taken from [here](https://www.baeldung.com/openssl-self-signed-cert)

To generate a cert we need 2 things

* a private key
* a Certificate Signing Request

With these, we can create a self-signed certificate

### Private keys

`openssl genrsa -des3 -out [key-name].key 2048`

You can substitute the `-des3` for anything on the `openssl enc -list`

if you remove the `-des3` encryption flag then it will create an unencrypted one. If you encrypt then you will need a 4 or more character password

### CSR

A Certificate Signing Request (CSR) is basically a packaged up bundle of information to be sent to the CA for signing. it contains information about the user, domain etc that can be used to verify the authenticity of the cert. E.g. if you are using the cert for the wrong domain.

`openssl req -key [key-name].key -new -out [csr-name].csr`

You can bundle this into a single command

`openssl req -newkey rsa:2048 -keyout [key-name].key -out [csr-name].csr`

Be careful as this will automatically encrypt with the `-des3` encryption.

### Cert

The certificate takes the CSR and the private key and creates a cert from that

`openssl x509 -signkey [key-name].key -in [csr-name].csr -req -days 365 -out [cert-name].crt`

This is the cert that the website will use and contains the public key for the encryption.

At this point your cert is usable but it will still flag errors if you try and use a site with a self signed cert. You have to also hold the Certificate Authority (CA) that the cert is signed with.

## Certificate Authorities

Certificate authorities (CA) are the trusted entities that we can verify (trust, but verify) the holder of the cert.

You can use public CAs or you can self sign your own CA for internal purposes.

This creates a self signed root CA

`openssl req -x509 -sha256 -days 1825 -newkey rsa:2048 -keyout [root-ca-key-name].key -out [root-ca-name].crt`

This creates a cert using the self signed root CA in the previous command.

`openssl x509 -req -CA [root-ca-name].crt -CAkey [root-ca-key-name].key -in [csr-name].csr -out [cert-name].crt -days 365 -CAcreateserial`

Question: why does this not require the cert private key?

## Signing and verifying files

Taken from [here](https://kb.sos-berlin.com/display/JS7/JS7+-+How+to+check+Signatures+with+OpenSSL+using+X.509+Certificates)

Once you have a cert generated you can use the private key to sign files and the public key to verify them. 

This does mean that you have to have the private key accessible which is maybe why encrypting it is useful? But you still need the passcode.

You need the private key to create the signature

`openssl dgst -sign privatekey.pem -keyform pem -sha256 -out test.txt.sig -binary test.txt`

You can extract a public key from a cert

`openssl x509 -in certificate.pem -noout -pubkey > publickey.pem`

Question: can this be done from a remote cert? or do I have to copy the cert to my system.

You can verify using the public key

`openssl dgst -verify publickey.pem -keyform pem -sha256 -signature test.txt.sig -binary test.txt`

Question: Can the verify be easily done using a single command?

# Follow up

* Cert rotation, how to do this in an automated / semi-automated way
  * manually, and also in a deployed situation

