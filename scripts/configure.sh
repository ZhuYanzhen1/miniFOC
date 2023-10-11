#!/bin/bash
sudo apt-get update && sudo apt-get -y upgrade && sudo apt-get install -y cmake gcc g++ make build-essential wget p7zip-full

retry_count=10
for ((i=1; i<=$retry_count; i++)); do
    wget -c https://github.com/ZhuYanzhen1/miniFOC/releases/download/toolchain/GCC_Linux_x64.7z
    if [ $? -eq 0 ]; then
        echo "Download succeeded"
        break
    else
        echo "Download failed"
        if [ $i -eq $retry_count ]; then
            echo "Maximum number of retries reached"
            exit 1
        fi
        echo "Retrying..."
        sleep 1
    fi
done

for ((i=1; i<=$retry_count; i++)); do
    wget -c https://github.com/ZhuYanzhen1/miniFOC/releases/download/toolchain/OpenOCD_Linux_x64.7z
    if [ $? -eq 0 ]; then
        echo "Download succeeded"
        break
    else
        echo "Download failed"
        if [ $i -eq $retry_count ]; then
            echo "Maximum number of retries reached"
            exit 1
        fi
        echo "Retrying..."
        sleep 1
    fi
done

7z x GCC_Linux_x64.7z && rm -f GCC_Linux_x64.7z
7z x OpenOCD_Linux_x64.7z && rm -f OpenOCD_Linux_x64.7z

echo "Copy libraries and register"
cd openocd-ch32v/libs
sudo cp -P ./lib* /usr/lib
sudo ldconfig
echo "Copy and reload rules"
sudo cp ./50-wch.rules /etc/udev/rules.d
sudo cp ./60-openocd.rules  /etc/udev/rules.d
sudo udevadm control  --reload-rules
cd ../..

compiler_path="export CH32_DEV=$(pwd)/gcc-ch32v-riscv/"
SHELL_NAME=$(echo $SHELL)
if [ "$SHELL_NAME" = "/bin/bash" ]; then
    echo "Using bash terminal"
    echo "${compiler_path}" >> ~/.bashrc
elif [ "$SHELL_NAME" = "/usr/bin/zsh" ]; then
    echo "Using zsh terminal"
    echo "${compiler_path}" >> ~/.zshrc
else
    echo "Unknown terminal, please add '${compiler_path}' command to your rc file muanually"
    exit 1
fi

echo "Configure success!!!"

