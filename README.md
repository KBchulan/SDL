# LowrProtect - 塔防游戏

## 项目简介

LowrProtect 是一款基于 C++ 和 SDL2 开发的塔防游戏，玩家需要在地图上建造不同类型的防御塔来阻止敌人到达基地。

## 游戏特性

### 🏰 防御塔系统

- **弓箭塔 (Archer Tower)**: 射程远，攻击频率快，适合对付轻装敌人
- **斧头塔 (Axeman Tower)**: 攻击力高，适合对付重装敌人
- **火炮塔 (Gunner Tower)**: 范围伤害，攻击力强，但攻击间隔较长

### 👹 敌人类型

- **史莱姆 (Slime)**: 基础敌人，血量较低
- **骷髅兵 (Skeleton)**: 中等血量和速度
- **哥布林 (Goblin)**: 快速移动的敌人
- **哥布林牧师 (Goblin Priest)**: 具有特殊能力的敌人
- **史莱姆王 (King Slime)**: Boss级敌人，血量极高

### 🎮 游戏系统

- **塔防升级系统**: 每座防御塔可升级10个等级
- **金币系统**: 击败敌人获得金币，用于建造和升级防御塔
- **波次系统**: 敌人分波次进攻，难度逐渐增加
- **生命值系统**: 玩家有限的生命值，敌人到达基地会扣除生命
- **音效系统**: 完整的背景音乐和音效支持

## 环境配置

本游戏基于 Ubuntu 22.04 进行开发，具体环境如下：

### 1. CMake 3.25.3

下面进入下载地址并解压（此处不介绍），由于下载的是二进制文件，下面我们仅需要配置cmake的全局环境：

```bash
# 执行下面两行
sudo mv ./cmake-3.25.3-linux-x86_64 /usr/local/cmake/
sudo vim ~/.bashrc

# 按下i进入插入模式，并将下面这句话写到此文件最后，随后按下ESC进入命令模式，并输入:wq退出
export PATH=/usr/local/cmake/bin:$PATH

# 显示对应版本号即表示成功
cmake --version

# 若是没有安装make等：
sudo apt install build-essential
```

### 2. SDL2 全家桶

包括 SDL2、SDL2_image、SDL2_mixer、SDL2_ttf（此处我们均选择版本2），上述四个配置方式一样，此处以 SDL2_image 为例:

```bash
# 在本地运行终端，输入：
git clone https://github.com/libsdl-org/SDL_image.git

cd SDL_image
mkdir build
cd build
../configure
make -j{nproc}
sudo make install
# 剩下三个一样，至此安装完成
```

或者使用包管理器安装：

```bash
sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev
```

### 3. SDL2_gfx 安装配置

由于此项目无cmake管理，使用传统的makefile，在安装上与2一模一样，但是在CMakeList.txt的编写却是不同：

```bash
# 安装SDL2_gfx
sudo apt install libsdl2-gfx-dev
```

在CMakeLists.txt中需要通过pkg来寻找：

```cmake
find_package(PkgConfig REQUIRED)
pkg_search_module(SDL2_GFX REQUIRED SDL2_gfx)
target_include_directories(lowr_protect PUBLIC ${SDL2_GFX_INCLUDE_DIRS})
target_link_libraries(lowr_protect PUBLIC ${SDL2_GFX_LIBRARIES})
target_compile_options(lowr_protect PUBLIC ${SDL2_CFLAGS_OTHER})
```

### 4. 音频驱动

事实上Ubuntu无法直接使用SDL_init(SDL_INIT_EVERYTHING)，以及对应mixer的Open都无法使用，此处直接给出解决方案:

```bash
# 先安装如下两个音频库
sudo apt-get install libasound2-dev libpulse-dev
# 第二步重新构建SDL2
cd SDL
cd build && sudo make uninstall
cd ..
rm build -r
mkdir build && cd build
cmake .. && make && sudo make install
# 这样就能正常使用了
```

### 5. cJSON

用于管理json文件信息：

```bash
sudo apt install libcjson-dev
```

## 构建与运行

### 构建项目

```bash
git clone https://github.com/KBchulan/LowrProtect.git
cd LowrProtect

mkdir build
cd build

cmake ..
make -j{nproc}
```

### 运行游戏

```bash
./lowr_protect
```

## 项目结构

```
LowrProtect/
├── src/                    # 源代码文件
│   ├── main.cpp           # 主程序入口
│   └── begin_animation.cpp # 开场动画
├── include/               # 头文件
│   ├── game_manager.hpp   # 游戏管理器
│   ├── tower*.hpp         # 防御塔相关
│   ├── enemy*.hpp         # 敌人相关
│   ├── bullet*.hpp        # 子弹相关
│   └── ...               # 其他组件
├── resources/             # 游戏资源
│   ├── *.png             # 图像资源
│   ├── *.wav/*.mp3       # 音频资源
│   └── *.ttf             # 字体文件
├── data/                  # 游戏数据
│   ├── config.json       # 游戏配置
│   ├── level.json        # 关卡数据
│   └── map.csv           # 地图数据
├── doc/                   # 文档
├── CMakeLists.txt         # 构建配置
└── README.md             # 项目说明
```

## 游戏操作

- **鼠标左键**: 选择/建造防御塔
- **鼠标右键**: 取消选择
- **ESC**: 暂停/退出游戏

## 技术特性

- **C++17**: 使用现代C++特性
- **SDL2**: 跨平台多媒体库
- **JSON配置**: 使用cJSON进行配置管理
- **模块化设计**: 清晰的代码架构和组件分离
- **资源管理**: 统一的资源加载和管理系统

## 开发说明

### 添加新的防御塔类型

1. 在 `include/` 目录下创建新的塔类头文件
2. 继承 `Tower` 基类
3. 在 `config.json` 中添加配置数据
4. 在资源目录添加对应的图像资源

### 添加新的敌人类型

1. 在 `include/` 目录下创建新的敌人类头文件
2. 继承 `Enemy` 基类
3. 在 `config.json` 和 `level.json` 中添加配置数据
4. 在资源目录添加对应的图像和动画资源

