# 说明

这里是rainboy整理的题目仓库,题目列表

 - `1000-1675`为一本通的题目,注意题目编号不连续
 - `1671-1999`为我(Rainboy)平时做的题目的添加
 - `2000-2096`为usaco training的题目
 - `3000-3224`为《算法竞赛进阶指南》上的题目
 - `3498-4000`历年noip题目
 - `5000-6000` 为rbook上的题目

- [一本通入门篇题目列表](./list/一本通入门篇题目列表.md) PS. 数据为我自己生成
- [usacoTrainning题目列表](./list/usacoTrainning题目列表.md)
- [一本通提高篇题目列表](./list/一本通提高篇题目列表.md)
- [noip题目列表](./list/noip题目列表.md)
- [《算法竞赛进阶指南》题目列表](./list/算法竞赛进阶指南.md)
    

如果哪个题目侵权,请在 Issues 中提出,我会删除

## 如何使用 upload.js 上传/更新题目

安装nodejs,yarn,然后`yarn install`安装依赖

```
./upload.js --help
```

**上传**

准备: 登录admin,保存Cookie到cookie文件

```
./upload.js 1001            # 上传一个题目
./upload.js 1002 1004       # 上传3个题目 1002->1003
./upload.js -d 1005         # 显示debug信息
```

```
./upload.js -u 1001            # 更新一个题目
./upload.js -u 1002 1004       # 更新3个题目 只更新题面
./upload.js -u -f 1002 1004    # 上传3个题目 强制上传覆盖原数据
./upload.js -uf 1002 1004      # 同上
```

### 如何评测

### 方法一： 在ROJ上评测
### 方法二： 手动评测
 
1. 需要 `node.js >= 14.0`
2. `cd bin; yarn (or npm install)`
3.  安装 https://github.com/rainboyOJ/testlib 下的 fcmp2

```
git clone https://github.com/rainboyOJ/testlib
cd testlib
mkdir build
cmake ..
make
cd ../output
sudo install fcmp2 /usr/bin
```

4. 创建一个 `tmp`文件夹，在里面写入`1.cpp`

```c++
#include <cstdio>
int main(){
    int a,b;
    scanf("%d%d",&a,&b);
    printf("%d",a+b);
    return 0;
}
```

5. 执行 `./bin/singleJudge.js 1000 tmp/1.cpp`

6. 评测其它编号的题目替换1000


## [LICENSE](https://github.com/anak10thn/WTFPL)

```
            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
                    Version 2, December 2004

 Copyright (C) 2012 Romain Lespinasse <romain.lespinasse@gmail.com>

 Everyone is permitted to copy and distribute verbatim or modified
 copies of this license document, and changing it is allowed as long
 as the name is changed.

            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

  0. You just DO WHAT THE FUCK YOU WANT TO.
```
