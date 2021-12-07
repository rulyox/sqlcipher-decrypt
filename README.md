# SQLCipher Decrypter

Decrypt a SQLCipher DB and save to a plaintext DB.

## Requirements

[SQLCipher](https://github.com/sqlcipher/sqlcipher) must be installed to build and execute.

## Build

### Using CMake

```
cmake -S . -B build
make -C build
```

### Using GCC

```
gcc main.c -o sqlcipher-decrypt -I /usr/local/include/sqlcipher -L /usr/local/lib/libsqlcipher.a -l sqlcipher
```

### Execute

```
./sqlcipher-decrypt /some/path/sqlite.db password
```

Decrypted file will be saved to `/some/path/sqlite.db-decrypted.db`.

## Using Docker

```
docker build -t sqlcipher-decrypt .
docker run -it --rm -v /some/path/db:/db sqlcipher-decrypt d /db/sqlite.db password
```
