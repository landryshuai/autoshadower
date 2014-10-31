#翻墙找 shadowsocks，帐号问 autoshadower：自动、自动、以及自动
yangyang.gnu@gmail.com  
http://yangyangwithgnu.github.io/  
2014-10-31 22:30:33


##公告

**捐赠：如果觉得 autoshadower 有用，可以考虑捐赠点碎银，支付宝 yangyang.gnu@gmail.com （https://shenghuo.alipay.com/send/payment/fill.htm ），不好意思，$_$**

**讨论**：任何意见建议移步 XXXXXXXXXXXXXXXXXXXXXXXXXXX

**注意**  

+ autoshadower 内部将调用 shadowsocks 的客户端程序 sslocal 进行帐号（证书）有效性的验证，你得先自行安装（https://github.com/clowwindy/shadowsocks ）。另外，autoshadower 当前只支持原版 shadowsocks，并不支持 shadowsocks-go、shadowsocks-nodejs、shadowsocks-gui 等等衍生版。
+ 你，真的可以帮到大家！如果你知道可以获取免费 shadowsocks 帐号的网站，请 email 我，一方面，我会将其加入 autoshadower 让它自动为你更新可用帐号，一方面，每个人都能享受免费 SS 带来的网络自由。


##版本

**[v0.1.0，新增，2014-10-31]**：发布初始版本。


##演示  
<div align="center">
<img src="https://github.com/yangyangwithgnu/autoshadower/raw/master/pics/running.gif" alt=""/><br />
</div>



##man
autoshadower is so sweet, she will find many free shadowsocks accounts for you, do her best! but, first of all, your system has installed sslocal by yourself. you can get it from https://github.com/clowwindy/shadowsocks. 

ok, now enjoy it. autoshadower is easy and simple to use. Usually, you can issue it as follow: 

```
  $ autoshadower
```
or

```
  $ autoshadower --mode all --path ~/downloads
```

--help  
\---------------  
Show this help infomation what you are seeing. 

--version  
\---------------  
Show current version. 

--path  
\---------------  
Set the path to save SS certificate files. the rule of subdir is SS_certs@@mmddhhmmss, the rule of shadowsocks certificate file is localport.json or localport-[avarspeed]-[region].json. 
The default directory is home directory or C:\ 

--mode  
\---------------  
Set the mode which how to find SS certificate. there are four modes: 
  0) a (available). just find which SS certificate is available;  
  1) r (region). find which SS certificate is available, and the region of certificate out ip;  
  2) s (averspeed). find which SS certificate is available, and the average speed of certificate out ip;  
  3) all. included a, r, and s. 
default a

That's all. Any suggestions let me know by yangyang.gnu@gmail.com or http://yangyangwithgnu.github.io/ , big thanks to you.


##【背景】
你知道，shadowsocks (SS) 是一款优秀的翻墙工具，相较 goagent、PPTP-VPN、openVPN、SSH 等其他工具的最大优点就是速度，再加之，近期 GFW 对其他工具干扰加剧，SS 便成了我的最爱。要使用 SS 得现有帐号或者证书，找遍各大搜索引擎，终于找到几个公益网站提供免费 SS 帐号，一方面为留住访问量，一方面避免流量滥用，通常这些网站会定期更新免费帐号的服务端端口、密码等信息，导致我在用的 SS 帐号是不是失效，我又不得不登录这些网站重新获取新帐号，如此往返持续了有大半年，真是麻烦。我，作为一个发育成熟的成年男性懒人，不能再这样过下去了，所以，基本上，我需要一个自动化工具，它得帮我做几件事：

* 自动登录 SS 帐号提供网站获取所有帐号并测试帐号的可用性、代理出口所在区域、代理网速；
* 将可用帐号转换成 sslocal 的命令行选项并输出至屏幕，让我复制后可直接运行；
* 将可用帐号转保存成 sslocal 的 \*.json 证书文件。

##【安装】
0）唯一依赖 libcurl，请自行安装；  
1）代码采用 C++11 编写，gcc 版本不低于 4.7.1。  
2）运行：  

```
$ cd autoshadower/build/
$ cmake .
$ make && make install
```

##【使用】  
从上面的 man 中你可以了解到 autoshadower 的全部能力。基本上，--mode 是重点，它有四个枚举参数：

* a 模式（available），查找所有可用证书，该模式耗时短；
* r 模式（region），查找所有可用证书，并核实证书的出口 IP 所在区域，该模式耗时较短；
* s 模式（avarspeed），查找所有可用证书，并核实证书的访问速度，该模式耗时较长；
* all 模式，包含 available、region、avarspeed 等模式，该模式耗时长；

默认为 available。

你可以不带任何命令行选项直接运行：

```
$ autoshadower
```
如上所说，autoshadower 为你测试它能获取的帐号是否可用，若可用它会在屏幕上输出 sslocal 的命令行选项，你自己复制运行即可，类似

>
\\(\^o\^)/. this SS certificate available. now you can issue SS proxy as follow:  
  sslocal -s "la11.wfg.pw" -p 47265 -k "efmoe.panny" -b "127.0.0.1" -l 1080 -m "AES-128-CFB" -t 512
>

你将第二行复制粘贴至命令行中运行即可：

```
sslocal -s "la11.wfg.pw" -p 47265 -k "efmoe.panny" -b "127.0.0.1" -l 1080 -m "AES-128-CFB" -t 512
```
或者，采用 autoshadower 为你生成的证书文件：

```
sslocal -c ~/1080.json
```

同理，要想测试帐号的速度，--mode 指定为 s 即可。简单得很。

```
$ autoshadower --mode s --path ~/downloads
```
