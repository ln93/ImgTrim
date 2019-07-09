# ImgTrim
A tiny C++ program to combine several pictures into one bigger picture for print&amp;cut 

## 使用说明
解压后启动ImgTrim.exe。

点击“开始拼接”，选择一个充满了图片的文件夹，默认配置下，程序将把这些图片批量地按3X2的方式排列（为了使图片更大，有时程序会旋转它们）在3000x2000像素的图片上，并将结果保存到图片源文件夹/result下。每张图片具有一个10像素宽的白色边框。

程序拥有可观的可调参数——分辨率，拼接规则，配置图像拉伸或是按比例缩放，边框宽度，jpg压缩比等。

最终结果类似下图：
![sample](https://github.com/ln93/ImgTrim/raw/master/sample.PNG)

## 程序性能
作者使用i7-4980hq拼接56张照片（600MB），耗时8秒。由于介质是机械硬盘，瓶颈基本就在硬盘速度上了。
## 为什么要使用本程序
冲印一张大照片比冲印6张小照片便宜多了————我们垃圾佬就是要省钱！
当然，如果你需要给照片批量重命名，添加白框，批量缩放等等，使用本软件也是可以的。
