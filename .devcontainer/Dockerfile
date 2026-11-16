FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y --no-install-recommends \
        build-essential cmake ninja-build git ca-certificates gdb clang clang-format clangd \
    && rm -rf /var/lib/apt/lists/*

# Non-root user matching the default Ubuntu 24.04 'ubuntu' user (uid 1000)
USER ubuntu
