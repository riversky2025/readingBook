# 修改模块以及缓存路径
查看
```
npm config ls
```
配置
```
npm config set prefix "D:\devsoft\nodejs"

npm config set cache "D:\devsoft\nodejs\node_cache"
```
新增环境变量 NODE_HOME 
NODE_HOME D:\devsoft\nodejs
Path 新加
```
%NODE_HOME%\;%NODE_HOME%\node_modules;
```
```
npm install -g cnpm --registry=https://registry.npm.taobao.org
```
# npm -g 安装路径
C:\Users\RS\AppData\Roaming\npm