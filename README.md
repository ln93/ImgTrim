# ImgTrim
A tiny C++ program to combine several pictures into one bigger picture for print&amp;cut 

## 使用说明
解压后启动ImgTrim.exe。
点击“开始拼接”，选择一个充满了图片的文件夹，默认配置下，程序将把这些图片批量地按3X2的方式排列（为了使图片更大，有时程序会旋转它们）在3000x2000像素的图片上，并将结果保存到图片源文件夹/result下。每张图片具有一个10像素宽的白色边框。

你当然可以自由地配置软件的参数——参数们并不多。
最终结果类似下图：
![sample](https://github.com/ln93/ImgTrim/raw/master/sample.png)

## 程序性能
作者使用i7-4980hq拼接56张照片（600MB），耗时8秒。由于介质是机械硬盘，瓶颈基本就在硬盘速度上了。
## 为什么要使用本程序
冲印一张大照片比冲印6张小照片便宜多了————我们垃圾佬就是要省钱！
