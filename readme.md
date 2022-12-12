# ValtCrypt

## Description
Vault Crypt is a program that can be used to encrypt/decrypt files using AES-CDC-256 algorithm. The encryption/decryption is performed using a user-generated password, hard coded salt and initialization vector. For simplicity, all you need to remember is your password :)

## Preview
![alt text](https://github.com/ImaraBradley001/VaultCrypt/raw/master/Preview/1.png)

## Getting Started

### Dependencies

* Windows 10
*  C++ 17
* Cryptopp
* Boost
* Visual Studio IDE

### Installing

* To install from this git repository, run the following commands
```
git clone https://github.com/ImaraBradley001/VaultCrypt.git
cd VaultCrypt
# Compile the project with visual studio 
```

* Or simply download the latest release binary

### Executing Vault Crypt
* To run VaultCrypt, simply run the following command from the downloaded repository after compiling the project.
```
start x64/release/DiskEncryptionUtility.exe
```
* Or simply run the downloaded binary VaultCrypt.exe 

### Possible Issues
* Do not attemp to decrypt files that have not been encrypted by this program as it may result in irreversible data loss

## Authors

Imara Bradley -> imarabradley2@gmail.com

## License

Check license.md for details.
