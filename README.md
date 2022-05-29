# walrus-ransomware

walrus - the harmless ransomware. It **encrypts a given list of files** by shifting bits within the files. It is of course open source, you can compile yourself.

**intent**<br/>
The intent of the software is to test and verify the operational readyness of our own cyber security defense systems. <font color="red">Use at you own risk</font> and don't encrypt production files.

# Usage

## create file list
Create a list of files, that should be encrypted (i.e. c:\temp\filelist.txt)

Contents:

```
c:\temp\fileToEncrypt1.txt
c:\temp\fileToEncrypt2.txt
...
```

## run walrus
Ideally, your cyber defense system should block the activity of walrus at some point.
```
walrus.exe /encrypt c:\temp\filelist.txt
```
```
walrus.exe /decrypt c:\temp\filelist.txt
```