# this is how to run this bitch
# chmod +x ./run.sh

# set up the env variables
export PATH="/Applications/ArmGNUToolchain/14.3.rel1/arm-none-eabi/bin:$PATH"
source ~/.zshrc
export PICO_SDK_PATH="~/documents/code/pico/pico-sdk"

# run the program
rm -rf build ; mkdir build ; cd build ; cmake .. ; make