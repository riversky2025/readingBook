#  minio分布式

版本：20210715 服务端

[下载地址](https://dl.min.io/server/minio/release/)

场景描述 挂载了4块盘提供分布式文件服务，中间进行了文件存储，桶的增删改查等操作，然后删除其中一个盘后重启看数据是否会重新恢复（已测试当4块盘中坏了一块时，重新部署后数据会自动恢复），后续磁盘扩增，再进行分布式文件系统的扩展

##  windows 

1.  分布式启动方式

```
SET MINIO_ROOT_USER = zzu
SET MINIO_ROOT_PASSWORD = zzufree123456
minio server   --console-address 192.168.0.88:9001 --address "192.168.0.88:19001" ^
http://192.168.0.88:19001/E:/miniodata ^
http://192.168.0.88:19002/E:/miniodata1 ^
http://192.168.0.88:19003/D:/miniodata  ^
http://192.168.0.88:19004/D:/miniodata1 
```

1. 扩展方案

   不支持

   

## linux

扩展方案一 两个机器  每次需要添加4块盘（raid0 即可）每次扩展4个盘（20T）太频繁不建议

192.168.0.20{1..2} /miniodata{1...2} 

->

192.168.0.20{1..2} /miniodata{1...2}   192.168.0.20{1..2} /miniodata{3...4} 

-> 

192.168.0.20{1..2} /miniodata{1...2}   192.168.0.20{1..2} /miniodata{3...4}  192.168.0.20{1..2} /miniodata{5...6}  192.168.0.20{1..2} /miniodata{7...8}  192.168.0.20{1..2} /miniodata{9...10}  

-> 

磁盘扩展

192.168.0.20{1..2} /miniodata{1...2}   192.168.0.20{1..2} /miniodata{3...4}  192.168.0.20{1..2} /miniodata{5...6}  192.168.0.20{1..2} /miniodata{7...8}  192.168.0.20{1..2} /miniodata{9...10}  

扩展方案二  两个机器->4个机器  每次扩展8个盘  40T    8口方案

192.168.0.20{1..2} /miniodata{1...4} 

->

192.168.0.20{1..2} /miniodata{1...4}  192.168.0.20{1..2} /miniodata{5...8} 

-> 扩机器

192.168.0.20{1..2} /miniodata{1...4}  192.168.0.20{1..2} /miniodata{5...8}  192.168.0.20{3..4} /miniodata{1...4}  

-> 扩磁盘

192.168.0.20{1..2} /miniodata{1...4}  192.168.0.20{1..2} /miniodata{5...8}  192.168.0.20{3..4} /miniodata{1...4}  192.168.0.20{3..4} /miniodata{5...8}  

扩展方案三  两个机器->4个机器  每次扩展12个盘  60T   12口方案

192.168.0.20{1..2} /miniodata{1...6} 

->

192.168.0.20{1..2} /miniodata{1...6}  192.168.0.20{1..2} /miniodata{7...12} 

-> 扩机器

192.168.0.20{1..2} /miniodata{1...6}  192.168.0.20{1..2} /miniodata{7...12}  192.168.0.20{3..4} /miniodata{1...6}  

-> 扩磁盘

192.168.0.20{1..2} /miniodata{1...6}  192.168.0.20{1..2} /miniodata{7...12}  192.168.0.20{3..4} /miniodata{1...6}  

192.168.0.20{3..4} /miniodata{7...12}  

方案2实验

```
sudo rm -rf /miniodata*


sudo mkdir -p /miniodata1
sudo mkdir -p /miniodata2
sudo mkdir -p /miniodata3
sudo mkdir -p /miniodata4
sudo mkdir -p /miniodata5
sudo mkdir -p /miniodata6
sudo mkdir -p /miniodata7
sudo mkdir -p /miniodata8






sudo chmod 777 /miniodata*
sudo chmod 777 /miniodata2
sudo chmod 777 /miniodata4
sudo chmod 777 /miniodata3
sudo chmod 777 /miniodata5
sudo chmod 777 /miniodata6
sudo chmod 777 /miniodata7
sudo chmod 777 /miniodata8


```



方案二测试过程：

两个机器的配置

步骤一  两个机器分别挂载4个磁盘 进行数据丢失与性能测试

```
cd /usr/local/bin
sudo vim start26.sh

#!/bin/sh

export MINIO_ROOT_USER=zzu
export  MINIO_ROOT_PASSWORD=zzufree123456
minio server --console-address 192.168.0.201:9001 --address "192.168.0.201:19001" http://192.168.0.20{0...1}/miniodata{1...4}  

sudo chmod +x start26.sh

./start26.sh
```

步骤二  每个电脑再添加4个磁盘 然后扩展

```
sudo fdisk /dev/sdb


sudo mkfs -t ext3 /dev/sdb1
sudo mkfs -t ext3 /dev/sdb2
sudo mkfs -t ext3 /dev/sdb3
sudo mkfs -t ext3 /dev/sdb4

sudo mount  /dev/sdb1  /miniodata1
sudo mount  /dev/sdb2  /miniodata2
sudo mount  /dev/sdb3  /miniodata3
sudo mount  /dev/sdb4  /miniodata4


sudo fdisk /dev/sdc




sudo mkfs -t ext3 /dev/sdc1
sudo mkfs -t ext3 /dev/sdc2
sudo mkfs -t ext3 /dev/sdc3
sudo mkfs -t ext3 /dev/sdc4


sudo mount  /dev/sdc1  /miniodata5
sudo mount  /dev/sdc2  /miniodata6
sudo mount  /dev/sdc3  /miniodata7
sudo mount  /dev/sdc4  /miniodata8

start28.sh

#!/bin/sh

export MINIO_ROOT_USER=zzu
export  MINIO_ROOT_PASSWORD=zzufree123456
minio server --console-address 192.168.0.201:9001 --address "192.168.0.201:19001" http://192.168.0.20{0...1}/miniodata{1...4}  http://192.168.0.20{0...1}/miniodata{5...8} 
```

![image-20220821163952939](D:\lkj\个人\readingBook\container\img\image-20220821163952939.png)

扩展机器

```
start34.sh

#!/bin/sh

export MINIO_ROOT_USER=zzu
export  MINIO_ROOT_PASSWORD=zzufree123456
minio server --console-address 192.168.0.201:9001 --address "192.168.0.201:19001" http://192.168.0.20{0...1}/miniodata{1...4}  http://192.168.0.20{0...1}/miniodata{5...8} http://192.168.0.20{2...3}/miniodata{1...4} 
```

![image-20220821164229294](D:\lkj\个人\readingBook\container\img\image-20220821164229294.png)

第三次扩展成4主机32磁盘

```
start38.sh
cd /usr/local/bin
sudo cp ./start34.sh ./start38.sh
sudo vim ./start38.sh
#!/bin/sh

export MINIO_ROOT_USER=zzu
export  MINIO_ROOT_PASSWORD=zzufree123456
minio server --console-address 192.168.0.201:9001 --address "192.168.0.201:19001" http://192.168.0.20{0...1}/miniodata{1...4}  http://192.168.0.20{0...1}/miniodata{5...8} http://192.168.0.20{2...3}/miniodata{1...4} http://192.168.0.20{2...3}/miniodata{5...8} 

/usr/local/bin/start38.sh
```

![image-20220821171305538](D:\lkj\个人\readingBook\container\img\image-20220821171305538.png)



	挂载

```
sudo vim  /etc/fstab
/dev/sdb1   /miniodata1        ext3    defaults        0 0
/dev/sdb2   /miniodata2        ext3    defaults        0 0
/dev/sdb3   /miniodata3        ext3    defaults        0 0
/dev/sdb4   /miniodata4        ext3    defaults        0 0
/dev/sdc1   /miniodata5        ext3    defaults        0 0
/dev/sdc2   /miniodata6        ext3    defaults        0 0
/dev/sdc3   /miniodata7        ext3    defaults        0 0
/dev/sdc4   /miniodata8        ext3    defaults        0 0
```



进行扩展

```
#!/bin/sh

export MINIO_ROOT_USER=zzu
export  MINIO_ROOT_PASSWORD=zzufree123456
minio server --console-address 192.168.0.201:9001 --address "192.168.0.201:19001" http://192.168.0.20{0...1}/miniodata{1...4}  
```



## 客户端

### 配置管理

```
$mc config host add minio http://127.0.0.1:19001 zzu zzufree123456
# 配置minio 是 server 给的名字，url 是 endpoint，zzu  zzufree123456是用户名，密码
$ mc config host add minio-server http://minio.lvzhenjiang.com
# 添加
# 回车输入Access Key、Secret Key
$ mc config host remove minio-server
# 删除
$mc config host list
```

### 桶的管理

```
$ mc ls minio
# 查看桶
$ mc mb minio/da/ofd
$ mc mb minio/aidata/DUTS
$ mc mb minio/img/test
# 创建桶

$ mc rb minio/img/test
# 删除 没有文件的bucket
$ mc rb minio/img/test --force
# 删除 有文件的bucket
# 删除桶

```

### 文件操作

```
$ mc cp C:\Users\Administrator\Pictures\background\192110-1568028070e5ea.jpg  minio/img/test
#上传一个文件到桶
$ mc cp E:\zzu\pynet\data\DUTS minio/aidata/DUTS --recursive
#上传一个目录到桶
$ mc rm minio/img/test/192110-1568028070e5ea.jpg
# 删除文件
$ mc rm minio/aidata/DUTS --recursive --force
# 删除目录
```

### 问题汇总

> > 1  Q:数据恢复问题
> >
> > 数据可以恢复，当磁盘格式化后重新启动minio ，会自动生成冗余数据
> >
> > ![image-20220820105017621](D:\lkj\个人\readingBook\container\img\image-20220820105017621.png)
> >
> > 2  磁盘扩展（本机扩展实验）
> >
> > window不支持扩展
> >
> > ![image-20220820105448015](D:\lkj\个人\readingBook\container\img\image-20220820105448015.png)
> >
> > ![image-20220820144000853](D:\lkj\个人\readingBook\container\img\image-20220820144000853.png)