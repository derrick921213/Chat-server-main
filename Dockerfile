FROM amd64/ubuntu


ENV DEBIAN_FRONTEND=noninteractive

# 安装基本工具
RUN apt-get update
RUN apt install -y git curl wget vim gdb gnupg software-properties-common build-essential zip unzip tar pkg-config openssl libssl-dev linux-libc-dev ninja-build rsync && rm -rf /var/lib/apt/lists/*
RUN wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | apt-key add -
RUN apt-add-repository 'deb https://apt.kitware.com/ubuntu/ bionic main'
RUN apt-get update
RUN apt install -y cmake

# 安装 Vcpkg
# RUN git clone https://github.com/Microsoft/vcpkg /chatserver/vcpkg
ENV PATH="/chatserver:${PATH}"
ENV VCPKG_ROOT="/chatserver/vcpkg"
ENV PATH="${VCPKG_ROOT}:${PATH}"
ENV CMAKE_TOOLCHAIN_FILE="/chatserver/vcpkg/scripts/buildsystems/vcpkg.cmake"
RUN git config --global core.autocrlf false
# 預設目錄
WORKDIR /chatserver
# COPY autobuild.sh /chatserver
# RUN chmod +x autobuild.sh
# 容器啟動時新增終端機
CMD ["CMD"]
