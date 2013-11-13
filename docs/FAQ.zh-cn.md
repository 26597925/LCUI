## LCUI相关的常见问题

如果在这里没有找到你想要了解的问题，请查看 LCUI的主页 http://lcui.org ，这里可能有
更多的最新信息。

### 我该怎样才能生成共享库 ?

默认情况下，会建立一个共享库（静态库）， 因此:

    make distclean
	./configure
	make


### 我该如何在 GNU/Linux 系统上安装 LCUI 共享库?

先用上面的，然后:

	make install



### 哪里有 LCUI 的文档 (man手册，等等)?

你可以访问LCUI的项目主页浏览开发文档，开发文档也托管在GitHub上，地址：https://github.com/lc-soft/LCUI-Documentation

如果你通过LCUI的源代码和示例程序领悟到了一些些有趣的东西，可以帮助我们完善开发文档，这样就能与其他人分享你的成果。

你也可以参考这些头文件，源代码，以及测试程序
中的代码和注释来了解 LCUI 。


### 我在 LCUI 里找到了一个BUG.
 
大部分时间，这些问题都是由于不正确使用的 LCUI 而造成的。
请尝试编写一个能重现问题的小程序，并发送相应的源代码至 lc-soft@live.cn 给我们。
未经事先同意，请勿发送上兆（MB）的数据文件。


### LCUI会侵犯任何专利吗？

据我们所知，没有。


### 运行configure脚本时中途异常退出。
	
请检查 LCUI 的依赖库是否已安装，如果已安装，可在网上搜索相关解决方法。


### LCUI 程序无法运行，错误信息：Permission denied 。

如果当前账户权限不够，会导致帧缓冲设备无法正常打开，可以使用 sudo 命令在运行 
LCUI 时临时提升权限。


### 为什么运行程序后屏幕上没有显示任何东西？

请先切换至字符控制台模式，并在此模式下运行程序，如果还是有此问题，请确定您的系统
是否支持FrameBuffer。
 
 
### 为什么图形界面上的文字会显示成 “□□”？

请查看程序在初始化时打印的信息，该问题主要由两种原因导致：LCUI 没有字体引擎支持，或者字体文件无法正常打开。

在没有字体引擎或无可用字体文件的情况下，LCUI 会使用内置的字体位图，但只限ASCII编码范围内的字符，对于中文字符，只能显示成 “□□”。

对于第一种情况，LCUI 的字体引擎由 FreeType 提供支持，请先确认 FreeType 函数库已经正确安装，再重新运行configure脚本，并重新编译整个项目。 而第二种情况，可以通过修改源代码，在初始化前设定默认字体文件的位置，也可以添加环境变量 LCUI_FONTFILE 指定字体文件位置。


### 为什么我已经安装了FreeType2函数库，configure脚本却没有检测到它？

这是FreeType2头文件路径的问题，如果你的FreeType2头文件是安装在 /usr/local/include/ 目录下，请将 /usr/local/include/freetype2 添加至编译器的头文件搜索目录，可使用如下命令：

	export C_INCLUDE_PATH=$C_INCLUDE_PATH:/usr/local/include/freetype2