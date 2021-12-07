FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

WORKDIR /app
COPY . .

RUN apt-get update
RUN apt-get install -y build-essential git tclsh openssl libssl-dev
RUN git clone https://github.com/sqlcipher/sqlcipher

WORKDIR /app/sqlcipher

RUN ./configure --enable-tempstore=yes CFLAGS="-DSQLITE_HAS_CODEC" LDFLAGS="-lcrypto"
RUN make install
RUN ldconfig

WORKDIR /app

RUN gcc main.c -o sqlcipher-decrypt -I /usr/local/include/sqlcipher -L /usr/local/lib/libsqlcipher.a -l sqlcipher
RUN cp sqlcipher-decrypt /usr/bin
RUN mv /usr/bin/sqlcipher-decrypt /usr/bin/d

CMD ["bash"]
