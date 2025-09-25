# maybe you also need to run git submodule update --init inside the /pico-sdk to enable USB features

# set up the env variables
export PATH="/Applications/ArmGNUToolchain/14.3.rel1/arm-none-eabi/bin:$PATH"
source ~/.zshrc
export PICO_SDK_PATH="~/documents/code/pico/pico-sdk"

# run the program
rm -rf build ; mkdir build ; cd build ; cmake .. ; make