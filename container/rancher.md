#  Rancher 

##  虚拟机配置

centos7 基础上

```
yum 源更新
1. 备份本地yum源

 mv /etc/yum.repos.d/CentOS-Base.repo /etc/yum.repos.d/CentOS-Base.repo_bak 

2.获取阿里yum源配置文件
 wget -O /etc/yum.repos.d/CentOS-Base.repo http://mirrors.aliyun.com/repo/Centos-7.repo 

3.更新cache
 yum makecache 
4.查看

 yum -y update 
```

两台主机

|ip||
| :--           | :--  |
| 192.168.1.158 |      |
|  192.168.1.65||



## 安装
### docker 
#### 安装
脚本安装
```
$ curl -fsSL https://get.docker.com -o get-docker.sh
$ sudo sh get-docker.sh
$ sudo usermod -aG docker your-user

启动
 sudo service docker start  
 
 开机启动
 # systemctl enable docker
```

####  镜像加速器




```
sudo mkdir -p /etc/docker
sudo tee /etc/docker/daemon.json <<-'EOF'
{
  "registry-mirrors": ["https://n8qxasfb.mirror.aliyuncs.com"]
}
EOF
sudo systemctl daemon-reload
sudo systemctl restart docker
```
#### 时间同步
```
sudo rm /etc/localtime

cat << EOM > /etc/sysconfig/clock
Zone=Asia/Shanghai
EOM

sudo ln -sf /usr/share/zoneinfo/Asia/Shanghai /etc/localtime

hwclock -w

sudo reboot

yum install -y ntp ntpdate  

ntpdate -u ntp2.aliyun.com

```

###  linux 
```
sudo docker run -d --restart=unless-stopped -v /dockervolume:/var/lib/rancher/ -p 80:80 -p 443:443 rancher/rancher:stable
```

如果是多台主机,需要注意
1. 时间同步
2. 主机名不能相同( hostnamectl set-hostname NAME )
3. 必须有一台为主(安装etcd,其他的为control,work)

![1591188313697](.\img\1591188313697.png)

#### linux时间同步定时任务
```
yum install crontabs   
yum -y install utp ntpdate  
 ntpdate -u ntp2.aliyun.com  
 
service crond start  
service crond stop  
service crond restart 
service crond reload //重新载入配置

查看crontab服务状态：service crond status
手动启动crontab服务：service crond start
chkconfig crond on  //开机启动

```
配置
```
1 在命令行输入: crontab -e 然后添加相应的任务，wq存盘退出

2 直接编辑/etc/crontab 文件，即vi /etc/crontab，添加相应的任务


```
基于cron语法demo
```
30 21 * * * /etc/init.d/nginx restart             //每晚的21:30重启 nginx。
45 4 1,10,22 * * /etc/init.d/nginx restart        //每月1、 10、22日的4 : 45重启nginx。
10 1 * * 6,0 /etc/init.d/nginx restart            //每周六、周日的1 : 10重启nginx。
0,30 18-23 * * * /etc/init.d/nginx restart        //每天18 : 00至23 : 00之间每隔30分钟重启nginx。
0 23 * * 6 /etc/init.d/nginx restart              //每星期六的11 : 00 pm重启nginx。
* */1 * * * /etc/init.d/nginx restart             //每一小时重启nginx
* 23-7/1 * * * /etc/init.d/nginx restart          //晚上11点到早上7点之间，每 隔一小时重启nginx
0 11 4 * mon-wed /etc/init.d/nginx restart        //每月的4号与每周一到周三 的11点重启nginx
0 4 1 jan * /etc/init.d/nginx restart             //一月一号的4点重启nginx
*/30 * * * * /usr/sbin/ntpdate ntp2.aliyun.com      //每半小时同步一下时间
```




### registry部署
镜像：registry:2.7.1  

端口  5000->30000



docker 仓库
一定注意存储卷的映射
容器内: /var/lib/registry  
容器外:/dockervolume/register

![1591247468828](.\img\1591247468828.png)

验证  http://192.168.1.158:30000/v2/_catalog

![1591247625556](.\img\1591247625556.png)

后续更新所有docker 容器的代理,添加该私有仓库

```

{
"registry-mirrors":["https://dockerhub.azk8s.cn","https://reg-mirror.qiniu.com"],
"insecure-registries":["192.168.1.158:30000"]
}
```

然后重启docker

```
service docker restart
```



## 常见基础设施

### 共享存储pvc

需要保证nfs服务已经安装

```
rpm -qa nfs-utils rpcbind
# 如果没有安装需要安装并且开启服务
yum -y install nfs-utils 

systemctl status rpcbind 
systemctl stop rpcbind
systemctl stop nfs-utils
systemctl start rpcbind
systemctl start nfs-utils  
systemctl enable rpcbind
systemctl enable nfs-utils  
# 启动服务  

systemctl restart nfs-config
systemctl restart nfs-idmap
systemctl restart nfs-lock
systemctl restart nfs-server

systemctl enable nfs-config
systemctl enable nfs-idmap
systemctl enable nfs-lock
systemctl enable nfs-server

# 设置共享
$ vim /etc/exports
$ /dockerpvc/       192.168.1.0/24(rw,async,no_root_squash,no_subtree_check)
$ mkdir /dockerpvc
$chmod 777  /dockerpvc
#重新加载配置
$ exportfs -a 
$ exportfs 
# 客户端检测
showmount -e 192.168.1.158


修改/etc/exports后可以执行

参数说明：
/docker/pvc/：nfs共享的目录
192.168.1.0/24：*所有IP ，示例为192.168.1.0-192.168.1.254区间的IP可以访问;
rw：read-write，可读写；
ro：read-only，只读；
sync：同步写入（文件同时写入硬盘和内存），适用在通信比较频繁且实时性比较高的场合
async：异步写入（文件先写入内存，稍候再写入硬盘），性能较好（速度快），适合超大或者超多文件的写入，但有数据丢失的风险，比如突然断电等情况；
root_squash（默认）：将来访的root用户映射为匿名用户或用户组；
no_root_squash：来访的root用户保持root帐号权限（可能会不安全）；
no_all_squash（默认）：访问用户先与本机用户匹配，匹配失败后再映射为匿名用户或用户组；
all_squash：将来访的所有用户映射为匿名用户或用户组；
secure（默认）：限制客户端只能从小于1024的tcp/ip端口连接服务器；
insecure：允许客户端从大于1024的tcp/ip端口连接服务器；
anonuid：匿名用户的UID值，通常是nobody或nfsnobody，可以在此处自行设定；
anongid：匿名用户的GID值；
no_subtree_check：如果NFS输出的是一个子目录，则无需检查其父目录的权限（可以提高效率）
```

nfs除了主程序端口2049与rpcbind的端口111是固定的意外还会随机使用一些,这里配置成固定的

```
vi /etc/sysconfig/nfs
# 文件末尾追加配置
MOUNTD_PORT=4001
STATD_PORT=4002
LOCKD_TCPPORT=4003
LOCKD_UDPPORT=4003
RQUOTAD_PORT=4004

然后重启
systemctl stop rpcbind
systemctl stop nfs-utils
systemctl start rpcbind
systemctl start nfs-utils  
```



然后在Rancher中添加储存卷

![1591349864396](.\img\1591349864396.png)



  然后在添加pvc(Default空间中添加)  

![1591406123785](.\img\1591406123785.png)

### 单机部署方案

注意这里的需要绑定pvc

![1591349514544](.\img\1591349514544.png)



![1591349752188](.\img\1591349752188.png)

 

### redis集群部署

该部署为集群方案

1. 数据在配置的Rancher存储卷中
2. 镜像在镜像库中(192.168.1.158)



```
$ docker pull redis:5.0.5-alpine3.10  
$ docker image inspect redis:5.0.5-alpine3.10 
$ docker tag redis:5.0.5-alpine3.10  192.168.1.158:30000/redis:5.0.5-alpine3.10 
$ docker push  192.168.1.158:30000/redis:5.0.5-alpine3.10 
```

[验证]:http://192.168.1.158:30000/v2/_catalog

 在Rancher上部署redis集群，需要对每个节点的配置和数据做持久化，并且要确保节点pod重建以后，配置和数据不变，并可以自动将新的pod ip注册到集群。   

 因此需要结合StatefulSets（有状态集）服务和持久卷来确保redis集群的正确运行。   

 **Statefulset 的设计原理模型:**   

1.  拓扑状态:  应用的多个实例之间不是完全对等的关系,这个应用实例的启动必须按照某些顺序启动,比如应用的主节点 A 要先于从节点 B 启动。而如果你把 A 和 B 两个Pod删除掉,他们再次被创建出来是也必须严格按照这个顺序才行,并且,新创建出来的Pod,必须和原来的Pod的网络标识一样,这样原先的访问者才能使用同样的方法,访问到这个新的Pod。 
2.  存储状态:  应用的多个实例分别绑定了不同的存储数据.对于这些应用实例来说,Pod A第一次读取到的数据,和隔了十分钟之后再次读取到的数据,应该是同一份,哪怕在此期间Pod A被重新创建过.一个数据库应用的多个存储实例。 

 使用statefulset服务部署，无论是Master 还是 slave都作为statefulset的一个副本,通过pv/pvc进行持久化,对外暴露一个service 接受客户端请求。   

 部署StatefulSets类型的负载需要安装NFS client provisioner， 利用 NFS Server 给 Kubernetes 作为持久存储的后端，并且动态提供PV。 

#### 部署方案

 65两个 158一个 三个都是主

远程共享夹的方案,在158上提供服务  

端口分别为7001  7002  7003

对应的数据卷以及配置位于共享目录下的/redis/7001  

|ip|端口|卷位置|
|:--|:--|:--|
|192.168.1.158|7001|/redis/7001/data  /redis/7001/config |
|192.168.1.65|7002|/redis/7002/data  /redis/7002/config |
|192.168.1.65|7003|/redis/7003/data  /redis/7003/config |

```

[root@localhost redis]# mkdir -p  /dockerpvc/redis/7001/data
[root@localhost redis]# mkdir -p  /dockerpvc/redis/7001/config
[root@localhost redis]# mkdir -p  /dockerpvc/redis/7002/config
[root@localhost redis]# mkdir -p  /dockerpvc/redis/7002/data
[root@localhost redis]# mkdir -p  /dockerpvc/redis/7003/data
[root@localhost redis]# mkdir -p  /dockerpvc/redis/7003/config
[root@localhost redis]# exportfs -r
[root@localhost redis]# exportfs
/dockerpvc    	192.168.1.0/24
```
配置文件配置(不要带中文的#注释)
```
# bind 127.0.0.1 
protected-mode no
port 7003 
tcp-backlog 511
timeout 0
tcp-keepalive 300
daemonize no
supervised no
pidfile /var/run/redis.pid
loglevel notice
logfile "/data/redis.log"
databases 16
always-show-logo yes
save 900 1
save 300 10
save 60 10000
stop-writes-on-bgsave-error yes
rdbcompression yes
rdbchecksum yes
dbfilename dump.rdb
dir ./
replica-serve-stale-data yes
replica-read-only yes
repl-diskless-sync no
repl-diskless-sync-delay 5
repl-disable-tcp-nodelay no
replica-priority 100
lazyfree-lazy-eviction no
lazyfree-lazy-expire no
lazyfree-lazy-server-del no
replica-lazy-flush no
appendonly yes
appendfilename "appendonly.aof"
appendfsync everysec
no-appendfsync-on-rewrite no
auto-aof-rewrite-percentage 100
auto-aof-rewrite-min-size 64mb
aof-load-truncated yes
aof-use-rdb-preamble yes
lua-time-limit 5000
cluster-enabled yes 
cluster-config-file /data/nodes.conf 
cluster-node-timeout 15000 
slowlog-log-slower-than 10000
slowlog-max-len 128
latency-monitor-threshold 0
notify-keyspace-events ""
hash-max-ziplist-entries 512
hash-max-ziplist-value 64
list-max-ziplist-size -2
list-compress-depth 0
set-max-intset-entries 512
zset-max-ziplist-entries 128
zset-max-ziplist-value 64
hll-sparse-max-bytes 3000
stream-node-max-bytes 4096
stream-node-max-entries 100
activerehashing yes
client-output-buffer-limit normal 0 0 0
client-output-buffer-limit replica 256mb 64mb 60
client-output-buffer-limit pubsub 32mb 8mb 60
hz 10
dynamic-hz yes
aof-rewrite-incremental-fsync yes
rdb-save-incremental-fsync yes
```

然后将配置文件分别复制到其他的pv配置里面,记得修改端口号



**部署工作负载** 

镜像:192.168.1.158:30000/redis:5.0.5-alpine3.10
前置条件
1.  保证docker-entrypoint 存在,如果不存在需要使用(所有主机都需要保证)
>>这里先做查询后再进行赋值
```
cd /usr/local/bin 
find / -name docker-entrypoint.sh
cp /var/lib/docker/overlay2/1cd5d84973b09dd3444f08c5a8336d3fdde18c7f4aac8dbc749ad28a511f72a1/diff/usr/local/bin/docker-entrypoint.sh .
```
2. 添加  redis-cluster命名空间,以及对应的的pv和pvc
3. 158 添加标签 redis=redisM 65 redis=redisS

然后部署
1.  镜像192.168.1.158:30000/redis:5.0.5-alpine3.10  命名空间选择(redis-cluster)
2. 端口映射出去7001 17001  
3. 主机调度选择 redis=redisM
4. 存储卷-pvc设置,,/data  ->  7001/data    /etc/redis/redis.conf  -> 7001/config/redis.conf
5. 存储卷-主机映射卷 /etc/localtime  ->/etc/localtime 
6. 存储卷-主机映射卷 /usr/local/bin/docker-entrypoint.sh  -> /usr/local/bin/docker-entrypoint.sh
7. 高级选项-命令  命令CMD:   redis-server /etc/redis/redis.conf
8. 高级选项-网络  使用主机网络:是



![1591411084843](.\img\1591411084843.png)

![1591411116266](.\img\1591411116266.png)

![1591411147211](.\img\1591411147211.png)

然后使用克隆的方式克隆出其他两个

克隆的时候需要修改的地方

1. 名称
2. pod调度(选择器)
3. 端口
4. 数据卷

**使用客户端进行集群关联**  

客户端镜像仓库私有打包

```
docker pull goodsmileduck/redis-cli:v5.0.3
docker tag goodsmileduck/redis-cli:v5.0.3 192.168.1.158:30000/goodsmileduck/redis-cli:v5.0.3
docker push 192.168.1.158:30000/goodsmileduck/redis-cli:v5.0.3
docker rmi goodsmileduck/redis-cli:v5.0.3
docker rmi 192.168.1.158:30000/goodsmileduck/redis-cli:v5.0.3
```

在rancher中进行部署  

![1591412858622](.\img\1591412858622.png)

然后成功后直接执行命令行,执行集群设置命令即可

![1591412911095](.\img\1591412911095.png)

```
/ # ls
bin    dev    etc    home   lib    media  mnt    opt    proc   root   run    sbin   srv    sys    tmp    usr    var
/ # cd bin
/bin # redis-cli --cluster create 192.168.1.65:7001  192.168.1.158:7002 192.168.1.158:7003 --cluster-replicas 0
```

> > 如果--cluster-replicas 1 表示为集群中每一个主节点指定一个从节点,即一比一的复制  

![1591412807174](.\img\1591412807174.png)



查看集群情况

/bin # redis-cli -c -h 192.168.1.65 -p 7001
192.168.1.65:7001> cluster nodes
1f7236e4e8f1f8ec0cc7150eb5c97924ee182413 192.168.1.65:7001@17001 myself,master - 0 1591441858000 1 connected 0-5460
7d074ef34680ba691d047bb535d64b94bd498adb 192.168.1.158:7003@17003 master - 0 1591441860604 3 connected 10923-16383
d230154519d064cdffc1e9ccdcea6adeb13991f4 192.168.1.158:7002@17002 master - 0 1591441861626 2 connected 5461-10922
192.168.1.65:7001> 



### mysql 部署

镜像私有仓库

```
docker pull mysql:8.0.17  
docker tag  mysql:8.0.17 192.168.1.158:30000/mysql:8.0.17
docker push 192.168.1.158:30000/mysql:8.0.17
docker rmi 192.168.1.158:30000/mysql:8.0.17
docker rmi  mysql:8.0.17
```

创建标签命名空间  ,以及pv,pvc  

标签 mysql=mysqlM   mysql=mysqlS

命名空间mysql-ns

```
# mysql 单机部署  mysqlM 写库  mysqlS读库
[root@localhost redis]# mkdir -p  /dockerpvc/mysql/mysqlS/data
[root@localhost redis]# mkdir -p  /dockerpvc/mysql/mysqlS/config
[root@localhost redis]# mkdir -p  /dockerpvc/mysql/mysqlM/config
[root@localhost redis]# mkdir -p  /dockerpvc/mysql/mysqlM/data
[root@localhost redis]# mkdir -p  /dockerpvc/mysql/mysql/data
[root@localhost redis]# mkdir -p  /dockerpvc/mysql/mysql/config
```



#### 单机部署

my.cnf配置

```
[client]
default-character-set=utf8mb4
[mysql]
default-character-set=utf8mb4
[mysqld]
pid-file        = /var/run/mysqld/mysqld.pid
socket          = /var/run/mysqld/mysqld.sock
datadir         = /var/lib/mysql
max_connections=10000
default-time_zone='+8:00' 
character-set-client-handshake=FALSE
character_set_server=utf8mb4
collation-server=utf8mb4_unicode_ci
init_connect='SET NAMES utf8mb4 COLLATE utf8mb4_unicode_ci'
wait_timeout=2147483

secure-file-priv= NULL
# Disabling symbolic-links is recommended to prevent assorted security risks
symbolic-links=0

# Custom config should go here
!includedir /etc/mysql/conf.d/
```



部署时一般是不具备外网访问权限的,  

```
mysql -u root -p 

use mysql; 
ALTER USER 'root'@'%' IDENTIFIED WITH mysql_native_password BY 'riversky';
flush privileges;
```





因此部署时

1.  镜像   192.168.1.158:30000/mysql:8.0.17  命名空间:mysql-ns
2. 端口 3306->3306
3. 环境变量MYSQL_ROOT_PASSWORD=riversky
4. 主机调度 mysql=mysqlM
5. 数据卷 /var/lib/mysql  ->  mysql/data  /etc/mysql/my.cnf  ->   mysql/config/my.cnf  
6. 网络  使用主机网络







#### 读写分离  

3310(主)  3311(从)

配置文件中添加一行port=3310

> > 读写分离时,server-id 需要不同

配置文件

```

[client]
default-character-set=utf8

[mysql]
default-character-set=utf8

[mysqld]
port = 3310
pid-file        = /var/run/mysqld/mysqld.pid
socket          = /var/run/mysqld/mysqld.sock
datadir         = /var/lib/mysql
max_connections=10000
default-time_zone='+8:00' 
character-set-client-handshake=FALSE
character_set_server=utf8
init-connect='SET NAMES UTF8'
wait_timeout=2147483
skip-host-cache
skip-name-resolve
general_log_file=/var/lib/mysql/query.log
slow_query_log_file=/var/lib/mysql/slow.log
log-error=/var/lib/mysql/error.log
log-bin=mysql-bin
server-id=10000

secure-file-priv= NULL
# Disabling symbolic-links is recommended to prevent assorted security risks
symbolic-links=0

# Custom config should go here
!includedir /etc/mysql/conf.d/
```

从

```
[client]
default-character-set=utf8

[mysql]
default-character-set=utf8

[mysqld]
port = 3311
pid-file        = /var/run/mysqld/mysqld.pid
socket          = /var/run/mysqld/mysqld.sock
datadir         = /var/lib/mysql
max_connections=10000
default-time_zone='+8:00' 
character-set-client-handshake=FALSE
character_set_server=utf8
init-connect='SET NAMES UTF8'
wait_timeout=2147483
skip-host-cache
skip-name-resolve
general_log_file=/var/lib/mysql/query.log
slow_query_log_file=/var/lib/mysql/slow.log
log-error=/var/lib/mysql/error.log
log-bin=mysql-bin
server-id=10001

secure-file-priv= NULL
# Disabling symbolic-links is recommended to prevent assorted security risks
symbolic-links=0

# Custom config should go here
!includedir /etc/mysql/conf.d/
```



**然后设置支持网络访问权限** 

```
mysql -u root -p 

use mysql; 
ALTER USER 'root'@'%' IDENTIFIED WITH mysql_native_password BY 'riversky';
flush privileges;
```

> >  ERROR 2002 (HY000): Can't connect to local MySQL server through socket '/var/run/mysqld/mysqld.sock' (2) 如果除下该错误,那么等一会再试,那是该服务还没开启完成

**集群化**  

```
GRANT REPLICATION SLAVE ON *.*  TO 'root'@'%';
flush privileges;
show master status;
查看主库状态  

从库执行
CHANGE MASTER TO 
MASTER_HOST ='192.168.1.158',
MASTER_PORT=3310,
MASTER_USER='root',
MASTER_PASSWORD='riversky',
MASTER_LOG_FILE='mysql-bin.000003',
MASTER_LOG_POS=1001;
# log部分要看主库的
启动从库,并且查看状态
start slave;
show slave status;
两个yes就成功了
```

![1591428559703](.\img\1591428559703.png)

![1591428900333](.\img\1591428900333.png)

### elk支持
>> 配置文件
ELK_VERSION=7.8.0  

根据github的docker部署方式进行部署 
[原项目](https://github.com/deviantony/docker-elk.git)  
#### es部署
镜像:  docker.elastic.co/elasticsearch/elasticsearch:${ELK_VERSION}  

**elasticsearch.yml配置**
```
---
## Default Elasticsearch configuration from Elasticsearch base image.
## https://github.com/elastic/elasticsearch/blob/master/distribution/docker/src/docker/config/elasticsearch.yml
#
cluster.name: "docker-cluster"
network.host: 0.0.0.0

## X-Pack settings
## see https://www.elastic.co/guide/en/elasticsearch/reference/current/setup-xpack.html
#
xpack.license.self_generated.type: trial
xpack.security.enabled: true
xpack.monitoring.collection.enabled: true
```
**存储卷**
```
配置绑定
source: /dockerv/elk/es/config/elasticsearch.yml
target: /usr/share/elasticsearch/config/elasticsearch.yml

存储volume
source: /dockerv/elk/es/data
target: /usr/share/elasticsearch/data
```
**网络** 
```
  - "9200:9200"
  - "9300:9300"
```
**环境变量**  
```
ES_JAVA_OPTS: "-Xmx256m -Xms256m"
ELASTIC_PASSWORD: changeme
discovery.type: single-node
​```
ES_JAVA_OPTS="-Xmx256m -Xms256m"
ELASTIC_PASSWORD= riversky
discovery.type= single-node
​```
```
#### logstash部署
镜像:  docker.elastic.co/logstash/logstash:7.8.0

**配置**
```logstash.yml

http.host: "0.0.0.0"
xpack.monitoring.elasticsearch.hosts: [ "http://elasticsearch:9200" ]

## X-Pack security credentials
#
xpack.monitoring.enabled: true
xpack.monitoring.elasticsearch.username: elastic
xpack.monitoring.elasticsearch.password: riversky
```

```pipeline/logstash.conf
input {
	tcp {
		port => 5000
	}
}

## Add your filters / logstash plugins configuration here

output {
	elasticsearch {
		hosts => "192.168.1.158:9200"
		user => "elastic"
		password => "riversky"
	}
}
```
**存储卷**
```
配置绑定
source: /dockerv/elk/logstash/config/logstash.yml
target: /usr/share/logstash/config/logstash.yml

存储volume
source: /dockerv/elk/logstash/pipeline
target: /usr/share/logstash/pipeline
```
**网络** 
```
  - "5000:5000/tcp"
  - "5000:5000/udp"
  - "9600:9600"
```
**环境变量**  
```
LS_JAVA_OPTS: "-Xmx256m -Xms256m"
```
#### kibana 
镜像:docker.elastic.co/kibana/kibana:7.8.0

**配置** 
```kibana.yml
server.name: kibana
server.host: 0.0.0.0
elasticsearch.hosts: [ "http://elasticsearch:9200" ]
monitoring.ui.container.elasticsearch.enabled: true

## X-Pack security credentials
#
elasticsearch.username: elastic
elasticsearch.password: riversky
```
**存储卷**
```
配置绑定
 source: /dockerv/elk/kibana/config/kibana.yml
 target: /usr/share/kibana/config/kibana.yml
```
**网络**
```
 - "5601:5601"
```
### rabbit支持  
#### 原始compose
```https://github.com/micahhausler/rabbitmq-compose
rabbit1:
  image: "rabbitmq:3-management"
  hostname: "rabbit1"
  environment:
    RABBITMQ_ERLANG_COOKIE: "SWQOKODSQALRPCLNMEQG"
    RABBITMQ_DEFAULT_USER: "rabbitmq"
    RABBITMQ_DEFAULT_PASS: "riversky"
    RABBITMQ_DEFAULT_VHOST: "/"
  ports:
    - "15672:15672"
    - "5672:5672"
  labels:
    NAME: "rabbitmq1"
  volumes:
    - "./enabled_plugins:/etc/rabbitmq/enabled_plugins"
    - "./rabbitmq.config:/etc/rabbitmq/rabbitmq.config"
  
```
#### rancher 

镜像: rabbitmq:3-management
配置

```rabbitmq.conf
loopback_users.guest = false
listeners.tcp.default = 5672
default_pass = riversky
default_user = rabbitmq
default_vhost = /
management.tcp.port = 15672
```
```enabled_plugins
[rabbitmq_management, rabbitmq_management_visualiser].
```
**存储卷** 
```
config-文件
source: /dockerv/mq/rabbit/config/rabbitmq.conf
target: /etc/rabbitmq/rabbitmq.conf
插件-文件 
source: /dockerv/mq/rabbit/config/enabled_plugins
target: /etc/rabbitmq/enabled_plugins


database
source: /dockerv/mq/rabbit/data
target: /var/lib/rabbitmq/mnesia

```
**网络** 
```
15672:15672
5672:5672
```
**环境变量** 
```
 RABBITMQ_ERLANG_COOKIE=SWQOKODSQALRPCLNMEQG
    RABBITMQ_DEFAULT_USER= rabbitmq
    RABBITMQ_DEFAULT_PASS=riversky
    RABBITMQ_DEFAULT_VHOST=/
```
###  nginx 支持
镜像:    nginx:1.19.0

配置
**卷** 
```
配置
source: /dockerv/nginx/config/nginx.conf

target :/etc/nginx/nginx.conf
日志 

source /dockerv/nginx/logs
target: /var/log/nginx

```
**端口映射** 
```
根据自己配置的代理需求进行映射
```

###  zipkin支持

镜像： openzipkin/zipkin

端口  9411:9411





### rocketmq 支持


```
version: '2'
services:
  namesrv:
    image: apacherocketmq/rocketmq:4.5.0
    container_name: rmqnamesrv
    ports:
      - 9876:9876
    volumes:
      - ./data/namesrv/logs:/home/rocketmq/logs
    command: sh mqnamesrv
  broker:
    image: apacherocketmq/rocketmq:4.5.0
    container_name: rmqbroker
    ports:
      - 10909:10909
      - 10911:10911
      - 10912:10912
    volumes:
      - ./data/broker/logs:/home/rocketmq/logs
      - ./data/broker/store:/home/rocketmq/store
      - ./data/broker/conf/broker.conf:/home/rocketmq/rocketmq-4.5.0/conf/broker.conf
    command: sh mqbroker -n namesrv:9876 -c ../conf/broker.conf
    depends_on:
      - namesrv
```

```broker.conf
brokerClusterName = DefaultCluster
brokerName = broker-b
brokerId = 0
deleteWhen = 04
fileReservedTime = 48
brokerRole = ASYNC_MASTER
flushDiskType = ASYNC_FLUSH

# Set self-defined brokerIP address (e.g. the host node's) 
#brokerIP1=30.25.90.82
```
#### rancher
镜像 apacherocketmq/rocketmq:4.5.0
##### namesrv
**网络** 
```
9876:9876
```
**卷** 
```
source: /dockerv/mq/rocket-names/logs
target: /home/rocketmq/logs
```
**命令行**
```
sh mqnamesrv
```
##### broker 
**网络** 
```
  10909:10909
  10911:10911
  10912:10912
```
**卷** 
```
logs
source: /dockerv/mq/rocket-broker/logs
target:/home/rocketmq/logs

store
source: /dockerv/mq/rocket-broker/store
target: /home/rocketmq/store

conf
source: /dockerv/mq/rocket-broker/config//broker.conf
target: /home/rocketmq/rocketmq-4.5.0/conf/broker.conf
```
**命令行** 
```
sh mqbroker -n 192.168.1.158:9876 -c ../conf/broker.conf
```
## java项目的镜像打包与docker 运行  

对于java项目,一般宿主机为windows.

jenkins的宿主机linux居多,不排除windows.  

但是运行docker的环境肯定linux居多,因此镜像打包方案  

windows开发,触发jenkins任务,jenkins,进行编译,成功后,并通过ssh远程linux进行镜像打包.(其实还有一种方便的方式,就是使用maven的docker插件,但是该方式有一定的弊端,比如开发机需要安装docker)  





### jenkins 组合使用
#### 基础环境
[jenkins rancher 官网插件 ]( https://plugins.jenkins.io/redeploy-rancher2-workload/ )

1. 获取Rancher2 Bearer Token

   ![1592641103886](.\img\1592641103886.png)

   ```
   API访问地址:
   https://192.168.1.158/v3 
   Access Key(用户名):
   token-ln9xd 
   Secret Key(密码):
   6jbxj87xvmwgcvwx6c2gdqbvdkgq8rmjgwwlc4pqmq8q78zsqqc5bz 
   Access Key和Secret Key可以作为HTTP基本身份验证的用户名和密码发送，以授权请求。您也可以将它们组合为Bearer Token:
   
   Bearer Token:
   token-ln9xd:6jbxj87xvmwgcvwx6c2gdqbvdkgq8rmjgwwlc4pqmq8q78zsqqc5bz 
   
   ```

   

2.  jenkins 添加凭据

![1592641495331](.\img\1592641495331.png)
#### 使用
利用pipeline 的方式
```
node {
    stage('Prepare') {
        echo "1.Prepare Stage"
        checkout scm
        pom = readMavenPom file: 'pom.xml'
        docker_host = "192.168.1.158:30000"
        img_name = "${pom.artifactId}"
        //img_name = "${pom.groupId}-${pom.artifactId}"
        docker_img_name = "${docker_host}/${img_name}"
        echo "group: ${pom.groupId}, artifactId: ${pom.artifactId}, version: ${pom.version}"
        echo "docker-img-name: ${docker_img_name}"
        script {
            build_tag = sh(returnStdout: true, script: 'git rev-parse --short HEAD').trim()
            if (env.BRANCH_NAME != 'master' && env.BRANCH_NAME != null) {
                build_tag = "${env.BRANCH_NAME}-${build_tag}"
            }
        }
    }


    stage('Test') {
        echo "2.Test Stage"
        sh "mvn test"
    }
    stage('Build') {
        echo "3.Build Docker Image Stage"
        sh "mvn package  -Dmaven.test.skip=true"
        sh "docker build -t ${docker_img_name}:${build_tag} " +
                " --build-arg SPRING_PROFILE=prod " +
                " --build-arg JAR_FILE=target/finanace-admin-${pom.version}.jar " +
                " ./finanace-admin"
    }

    stage('Push') {
        echo "4.Deploy jar and Push Docker Image Stage"
        sh "docker tag ${docker_img_name}:${build_tag} ${docker_img_name}:latest"
        sh "docker tag ${docker_img_name}:${build_tag} ${docker_img_name}:${pom.version}"
       // withCredentials([usernamePassword(credentialsId: 'docker-register', passwordVariable: 'dockerPassword', usernameVariable: 'dockerUser')]) {
         //   sh "docker login -u ${dockerUser} -p ${dockerPassword} docker.ryan-miao.com"
            sh "docker push ${docker_img_name}:latest"
            sh "docker push ${docker_img_name}:${pom.version}"
            sh "docker push ${docker_img_name}:${build_tag}"
            sh "docker rmi ${docker_img_name}:latest"
            sh "docker rmi ${docker_img_name}:${pom.version}"
            sh "docker rmi ${docker_img_name}:${build_tag}"

        //}
    }
    stage("Deploy"){
        echo "Deploy to rancher"
        rancherRedeploy alwaysPull: true, credential: 'rancher', images: '192.168.1.158:30000/finanace', workload: '/project/c-rdrjx:p-2n4nd/workloads/deployment:default:finance'
    }
    //stash 'complete-build'

}
```



阶段视图如下

![1592644377256](.\img\1592644377256.png)

关键步骤是Deploy这一步骤

```
For Jenkins Free Style Job
1. create a freestyle job in Jenkins
2. at Build section, click "Add build step" drop-down menu
3. you should see a menu it named: "Redeploy Rancher2.x Workload", click it!
4. click each field help button to see document
对于Pipeline job
node {
   rancherRedeploy alwaysPull: true, credential: 'rancher', images: 'busybox:lastest', workload: '/project/c-rdrjx:p-2n4nd/workloads/deployment:default:finance'
}
```



