检索它所用第三方插件的下载地址: 
https://github.com/Microsoft/vscode-go/blob/master/src/goInstallTools.ts 
对于强迫症患者，可以使用下面的命令一次性把第三方应用全部安装(一共22个应用，前15个为 Tools used explicitly by the basic features of the extension ):

```
go get -u -v github.com/nsf/gocode
go get -u -v github.com/uudashr/gopkgs/cmd/gopkgs
go get -u -v github.com/ramya-rao-a/go-outline
go get -u -v github.com/acroca/go-symbols

go get -u -v golang.org/x/tools/cmd/guru
go get -u -v golang.org/x/tools/cmd/gorename
go get -u -v github.com/rogpeppe/godef
go get -u -v golang.org/x/tools/cmd/godoc
go get -u -v github.com/zmb3/gogetdoc
go get -u -v github.com/sqs/goreturns
go get -u -v golang.org/x/tools/cmd/goimports
go get -u -v github.com/golang/lint/golint
go get -u -v github.com/alecthomas/gometalinter
go get -u -v honnef.co/go/tools/...
go get -u -v github.com/derekparker/delve/cmd/dlv

go get -u -v github.com/haya14busa/goplay/cmd/goplay
go get -u -v github.com/josharian/impl
go get -u -v github.com/tylerb/gotype-live
go get -u -v github.com/cweill/gotests/...
go get -u -v github.com/sourcegraph/go-langserver
go get -u -v github.com/davidrjenni/reftools/cmd/fillstruct
go get -u -v github.com/fatih/gomodifytags

go get -u github.com/go-delve/delve/cmd/dlv
```

不能安装的包
git clone https://github.com/golang/tools.git
安装到本地
把tools整个文件夹放入 %GOPATH%/src/golang/x 路径底下，接着我们把tools文件夹底下的lint文件夹分别放入%GOPATH%/src/golang/x 和 %GOPATH%/src/github.com/ 如下目录结构所示：
```
src
├── github.com
|      ├── golang
|      |   └── lint
|      ...
└── golang.org
       └── x
           ├── tools
           └── lint
```


# 配置
1.GOPATH：这个是你的工作目录，请在系统新加一个GOPATH指定你的工作目录,并且在工作目录中新建
bin,pkg,src三个文件夹。

2.Git：将git安装目录下的bin目录加入Path环境变量。

