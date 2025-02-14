FROM ubuntu:20.04

ENV TZ Europe/Moscow
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update --fix-missing

RUN apt-get install -y software-properties-common

RUN add-apt-repository -y ppa:ubuntu-toolchain-r/test

RUN apt-get update --fix-missing
RUN apt-get install -y \
    build-essential \
    gcc-multilib \
    gcc-13 \
    g++-13

RUN update-alternatives \
    --install /usr/bin/gcc gcc /usr/bin/gcc-13 40 \
    --slave /usr/bin/g++ g++ /usr/bin/g++-13

RUN add-apt-repository ppa:deadsnakes/ppa
RUN apt-get install -y \
    python3.9 \
    python3-pip \
    python3.9-dev \
    git

RUN apt-get update --fix-missing
RUN apt-get install -y qemu-system-x86

RUN yes | unminimize

RUN apt-get install -y \
    man \
    manpages-dev \
    manpages-posix-dev

WORKDIR /workspace
