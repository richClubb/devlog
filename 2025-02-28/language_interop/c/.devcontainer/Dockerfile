FROM debian:bookworm

RUN useradd -ms /bin/bash vscode

RUN apt update && apt upgrade -y
RUN apt install -y \
      build-essential \
      libcunit1 \
      libcunit1-doc \
      libcunit1-dev \
      cmake 
