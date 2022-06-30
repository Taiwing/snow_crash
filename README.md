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
characters in a text. Here the key is -11. This is means that each letter in the
text has been shifted on the left eleven times. To decrypt the password we need
to do the inverse operation, which is a right shift of the same value.

| Cipher | c | d | i | i | d | d | w | p | g | s | w | t | g | t |
|:------:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| Plain  | n | o | t | t | o | o | h | a | r | d | h | e | r | e |

## Broken DES (level01)

The second level is as simple as running john the ripper on flag01's password
hash, as it is subtly hinted at by the first level's password filename.

```shell
# copy the passwd file from the virtual machine (with level00 as a password)
scp -P 2222 level00@localhost:/etc/passwd .
# pass it through john the ripper
john --show passwd
```

This should output something like that:

```
flag01:abcdefg:3001:3001::/home/flag/flag01:/bin/bash

1 password hash cracked, 0 left
```

Where `abcdefg` is the password for flag01. It works because here the legacy
unix password hashing function `crypt` is used for encrypting the user's
password. It is based on a modified version of
[DES](https://en.wikipedia.org/wiki/Data_Encryption_Standard) to turn it into a
one-way function but it is not secure anymore, especially when the password is
as simple as it is here.

## Wireshark packet dump (level02)

Here you have a .pcap file at the root of the home directory. This contains a
list of TCP packets captured with wireshark. The password is contained in the
payloads of the TCP packets after the `Password:` string (which is really a
prompt). Each TCP payload is one byte long and represents an input from the user
logging into this insecure online service. The input ends with a 0x0d, which is
a form feed character meaning that the input is done.

To read the file simply copy it from the virtual machine and open it with
wireshark.

```shell
# copy the file from the vm (with the flag from the last level)
scp -P 2222 level02@localhost:~/level02.pcap .
# change its permissions to open it
chmod 644 level02.pcap
# read it with wireshark
wireshark level02.pcap
```

> If you dont have wireshark or cannot install it (like on 42's machines), just
> use the tshark.bash script in level02's Resources directory. It will read it
> and print each TCP payload from the pcap file: `./tshark.bash`.

Note that some of the payloads of the password are 0x7f. This is the DEL
character, which means the user screwed up and deleted part of his input. So _n_
preceding characters need to be deleted, where _n_ is the number of DEL in a
row. The final password is: `ft_waNDReL0L`.
