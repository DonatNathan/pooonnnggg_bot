# Pong Bot

I'll recreate the game pong and implement a bot to destroy everybody!

## How to install dependencies (Ubuntu)

```
sudo apt update
sudo apt install git cmake -y
sudo apt-get install build-essential
sudo apt install \
    libharfbuzz-dev \
    libxrandr-dev \
    libxcursor-dev \
    libxi-dev \
    libudev-dev \
    libfreetype-dev \
    libflac-dev \
    libvorbis-dev \
    libgl1-mesa-dev \
    libegl1-mesa-dev
```

## How to clone

```
git clone git@github.com:DonatNathan/pooonnnggg_bot.git
cd pooonnnggg_bot
```

## How to compile

```
mkdir build
cd build
cmake -DCMAKE_PREFIX_PATH=~/libtorch ..
make -j
./bin/PongBot
```

## How to run

```
./build/bin/PongBot
```

## How to compile training

```
cd training
mkdir build
cd build
cmake ..
make -j
./pong_train
```
