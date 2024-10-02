## 环境配置

​	本游戏基于ubuntu22.04进行开发，具体环境如下：

 1. cmake-3.25.3

    进入https://cmake.org/files/v3.25/
    选择下图所示压缩包下载：

    ![cmake](/home/whx/图片/截图/cmake.png)

    下面进入下载地址并解压（此处不介绍）,由于下载的是二进制文件，下面我们仅需要配置cmake的全局环境：

    ```bash
    # 执行下面两行
    sudo mv ./cmake-3.25.3-linux-x86_64 /usr/local/cmake/
    sudo vim ~/.bashrc
    
    # 按下i进入插入模式，并将下面这句话写道次文件最后，随后按下ESC进入命令模式，并输入：wq退出（":"也要输入）
    export PATH=/usr/local/cmake/bin:$PATH
    
    # 打开一个新终端，输入
    cmake --version
    # 显示对应版本号即表示成功
    
    # 若是没有安装make等：
    sudo apt install essential
    ```

 3. SDL全家桶，包括SDL，SDL_image，SDL_mixer，SDL_ttf（此处我们均选择版本2）

    上面四个配置方式一样，此处以SDL_image为例:

    ```bash
    # 在本地运行终端，输入(未安装git者先输入sudo apt install git)：
    git clone https://github.com/libsdl-org/SDL_image.git
    
    # 随后切换分支到版本2
    cd SDL_image
    mkdir build
    cd build
    ../configure  # 或者cmake ..
    make -j4
    sudo make install
    # 剩下三个一样，至此安装完成
    ```

3.SDL_gfx安装配置：

​	由于此项目无cmake管理，使用传统的makefile，在安装上与2一模一样，但是在CMakeList.txt的编写却是不同：

```bash
# 需要通过pkg来寻找
find_package(PkgConfig REQUIRED)

pkg_search_module(SDL2_GFX REQUIRED SDL2_gfx)

target_include_directories(lowr_protect PUBLIC ${SDL2_GFX_INCLUDE_DIRS})
    
target_link_libraries(lowr_protect PUBLIC ${SDL2_GFX_LIBRARIES})

target_compile_options(lowr_protect PUBLIC ${SDL2_CFLAGS_OTHER})
```

4.音频驱动：

​	事实上ubuntu无法直接使用SDL_init(SDL_INIT_EVERYTHING)，以及对应mixer的Open都无法使用，此处直接给出解决方案:

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

