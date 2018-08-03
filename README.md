# File-Packer-Unpacker

Multiple file in Directory can be packed (merge) into a single file and then you can unpack that file to get all the files of that Directory back.

New file create will be in encrypt by using default key. so that know one can read our file data. You can also use your own key to encrypt and decrypt.

The main reason to do this project is to understand File system call like ( open() , creat() , read() , write() , opendir() , readdir() , lseek , stat)

---

## Project Statistic

__Platform :__ Linux

__Technology :__ C

__Front-end :__ C

__Back-end :__ C

__Type :__ CUI

---

## Features

1. You can merge many file into one file and split it again.
2. You can encrypt that merge file so that know one can read your data.
3. Use our own key to encrypt and decrypt.
4. You can get specfic files from merge file.

---

## How To Run This Project

1. Create executable file

        cc main.c filePacker.c fileUnpacker.c helpInfo.c helperFunction.c searchFile.c -o ExcuteData/PackUnpack

2. Different type of command

    1. Help

            ./PackUnpack -h

    2. With using Userdefined Encryption

        - To Merge(pack)

                ./PackUnpack -M        DirectoryName   FileName

        - To Split(unpack)

                ./PackUnpack -S        FileName     DirectoryName

        - To get the specfic File from pack

                ./PackUnpack -S  -get  packFileName    Foldername    getFileName1 getFileName2 ...

    3. User defined encryption

        - To Merge(pack)

                ./PackUnpack -M        DirectoryName   FileName     key(numberical key)

        - To split(unpack)

                ./PackUnpack -S        FileName    DirectoryName    key

        - To get the specfic File from pack

                ./PackUnpack -S  -get  -e  key   packFileName   Foldername   getFileName1 getFileName2 ...

---

## More To Add

1. compression.