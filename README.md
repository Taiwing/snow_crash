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
