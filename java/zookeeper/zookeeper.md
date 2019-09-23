[官网文档](http://zookeeper.apache.org/doc/current/index.html)  
# 简介
ZooKeeper是一种用于分布式应用程序的高性能协调服务。它在一个简单的界面中公开了常用服务 - 例如命名，配置管理，同步和组服务 - 因此您不必从头开始编写它们。您可以使用现成的方法来实现共识，组管理，领导者选举和在线协议。您可以根据自己的特定需求进行构建。
## 概述
**ZooKeeper：分布式应用程序的分布式协调服务**      
ZooKeeper是一种用于分布式应用程序的分布式开源协调服务。它公开了一组简单的原语，分布式应用程序可以构建这些原语，以实现更高级别的服务，以实现同步，配置维护以及组和命名。它被设计为易于编程，并使用在熟悉的文件系统目录树结构之后设计的数据模型。它在Java中运行，并且具有Java和C的绑定。  
众所周知，协调服务很难做到。他们特别容易出现比赛条件和死锁等错误。ZooKeeper背后的动机是减轻分布式应用程序从头开始实施协调服务的责任。  
TODO:  
## 入门
**入门：使用ZooKeeper协调分布式应用程序**    

[下载](http://zookeeper.apache.org/releases.html)   
**单独使用**  
在独立模式下设置ZooKeeper服务器非常简单。服务器包含在单个JAR文件中，因此安装包括创建配置。  
下载完一个稳定的ZooKeeper版本后，将其解压缩并cd到root  
要启动ZooKeeper，您需要一个配置文件。这是一个示例，在conf / zoo.cfg中创建它：  
```
tickTime=2000
dataDir=/var/lib/zookeeper
clientPort=2181
```
这个文件可以被称为任何东西，但为了这个讨论，请将其命名为conf / zoo.cfg。更改dataDir的值以指定现有（从空开始）目录。以下是每个字段的含义：   
*  tickTime：ZooKeeper使用的基本时间单位（以毫秒为单位）。它用于做心跳，最小会话超时将是tickTime的两倍。
*  dataDir：存储内存数据库快照的位置，除非另有说明，否则为数据库更新的事务日志。
*  clientPort：侦听客户端连接的端口

现在您已创建配置文件，您可以启动ZooKeeper：  
```
bin/zkServer.sh start
```
**存储管理**  
对于长期运行的生产系统，必须在外部管理ZooKeeper存储（dataDir和logs）。
**连接**  
```
$ bin/zkCli.sh -server 127.0.0.1:2181
```
这使您可以执行简单的文件操作。  
**编程**  

**运行复制**  


# 开发者
## API
## 程序员指南
## Java实例
## 教程
## 
