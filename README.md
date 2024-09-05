contest 文件夹是存放所有比赛的题目
目录下每一个文件夹都是一个独立的比赛
每个比赛文件夹下面都是ABCDE等题目
题目中包含 同名的cpp文件 以及相对应的test文件

problem set 是codeforces的problem set的题目
每个题目都有编号
文件名以编号+题目难度命名
目录下的结构同样与上面相同

根目录下有一个python文件
该代码 传入一个路径 (具体到题目的文件夹)
然后代码会找到build/bin目录下的可执行文件
同时运行代码中的test文件夹下的测试用例

命令行的执行步骤
1. 创建build (如果有可以删除干净) 然后配置conan 以及 cmake
   1. conan install .. --build=missing -s build_type=Debug
   2. cmake .. -DCMAKE_TOOLCHAIN_FILE=./Debug/generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles"
2. 编译 cmake --build . or make
3. 使用python运行测试样例 
   1. 如果回到根目录 python test.py contest/cf_971_div4/E
   2. 如果在build目录 python ../test.py ../contest/cf_971_div4/E