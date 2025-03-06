FROM debian:bookworm

RUN useradd -ms /bin/bash vscode

RUN apt update && apt upgrade -y
RUN apt install -y \
      build-essential \
      libcunit1 \
      libcunit1-doc \
      libcunit1-dev \
      cmake 

RUN wget https://packages.microsoft.com/config/debian/12/packages-microsoft-prod.deb -O packages-microsoft-prod.deb && \
    dpkg -i packages-microsoft-prod.deb && \
    rm packages-microsoft-prod.deb

RUN apt update && apt install -y dotnet-sdk-8.0 dotnet-runtime-8.0