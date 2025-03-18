FROM debian:bookworm

RUN useradd -ms /bin/bash vscode

RUN apt update && apt upgrade -y
RUN apt install -y \
      build-essential \
      libcunit1 \
      libcunit1-doc \
      libcunit1-dev \
      cmake \
      wget \
      python3-full \
      python3-pip \
      pipx \
      curl

# INSTALL DOTNET / MUST NOT BE ON FUCKING CLOUDFLARE VPN
RUN wget https://packages.microsoft.com/config/debian/12/packages-microsoft-prod.deb -O packages-microsoft-prod.deb && \
    dpkg -i packages-microsoft-prod.deb && \
    rm packages-microsoft-prod.deb && \
    apt-get update && \
    apt-get install -y dotnet-sdk-8.0

RUN curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y

RUN PATH=$PATH:/home/root/.cargo/bin