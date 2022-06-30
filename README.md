# snow\_crash

This is a CTF made in 42. The flags, you gotta catch them all. At each level
there is a way to hack yourself to the next level by finding the flag which is
the password for the next user.

## Setup

```shell
# launch the snow_crash vm with qemu
./vm_lauch.bash
# connect to it with ssh (pass: level00)
ssh -p 2222 level00@localhost
```

> The vm\_launch.bash script takes an optional parameter for the ISO path.

## Caesar Cipher (level00)

The password for the user flag00 is located in the file `/usr/sbin/john`. It is
a plaintext file containing a string encrypted with a
[caesar cipher](https://en.wikipedia.org/wiki/Caesar_cipher). This is a classic
and simple symetric encryption scheme which uses a key for rotating the
characters in a text. Here the key is 11. This is means that each letter in the
text has been shifted on the right eleven times. To decrypt the password we need
to do the inverse operation, which is a left shift of the same value.

| Cipher | c | d | i | i | d | d | w | p | g | s | w | t | g | t |
|:------:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| Plain  | n | o | t | t | o | o | h | a | r | d | h | e | r | e |

## Broken DES (level01)

The second level is as simple as running john on flag01's password hash, as it
is subtly hinted at by the first level's password filename.

```shell
# copy the passwd file from the virtual machine
scp -P 2222 level00@localhost:/etc/passwd .
# pass it through john the ripper
john --show passwd
```

This should output something like that:

```
flag01:abcdefg:3001:3001::/home/flag/flag01:/bin/bash

1 password hash cracked, 0 left
```

Where `abcdefg` is password for flag01. It works because here the legacy unix
password hashing function `crypt` is used for encrypting the user's password. It
is based on a modified version of DES to turn it into a one-way function but it
is not secure anymore, especially when the password is as simple as it is here.
