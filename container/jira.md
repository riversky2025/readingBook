# jira安装

容器可视化

```
sudo docker run -d  --restart=unless-stopped -p 9000:9000  -v /var/run/docker.sock:/var/run/docker.sock -v /dockerv/portainer/data:/data -v /dockerv/portainer/public:/public --name prtainer  portainer/portainer
```



##  数据库mysql

```sql
docker pull mysql:5.7.24

sudo docker run -d  --restart=unless-stopped -p 3306:3306  -v /var/run/docker.sock:/var/run/docker.sock -v /dockerv/mysql/data:/var/lib/mysql -e  MYSQL_ROOT_PASSWORD=root -v /dockerv/mysql/config/my.cnf:/etc/mysql/my.cnf --name mysql  mysql:5.7

docker run -d  --restart=unless-stopped -p 3306:3306  -v /var/run/docker.sock:/var/run/docker.sock -v D:/dockerv/mysql/data:/var/lib/mysql -e  MYSQL_ROOT_PASSWORD=root -v D:/dockerv/mysql/config/my.cnf:/etc/mysql/my.cnf --name mysql  mysql:5.7
```

设置事务隔离级别

```
#设置事务隔离级别
set global transaction isolation level  READ COMMITTED;
#新建  jira_data  confluence_data 数据库 类型 utf8  utf8_bin
```

## jira镜像制作

###  代理包下载

```
链接：https://pan.baidu.com/s/1xGagbDMECezR3yCbptUCiQ 
提取码：qwer
```

### 构建jira的dockerfile

```
FROM cptactionhank/atlassian-jira-software:7.13.0

USER root

# 将代理破解包加入容器

COPY "atlassian-agent.jar" /opt/atlassian/jira/

# 设置启动加载代理包

RUN echo 'export CATALINA_OPTS="-javaagent:/opt/atlassian/jira/atlassian-agent.jar ${CATALINA_OPTS}"' >> /opt/atlassian/jira/bin/setenv.sh
```



### 构建制作镜像(在jira目录中)

```
sudo docker build -t jira:7.13.0 .
```

jira大概需要3G的运行内存才会不卡，所以指定内存

```
sudo docker run -d --name jira  --restart always -p 80:8080   -e TZ="Asia/Shanghai"    -v /dockerv/jira/data:/var/atlassian/jira -v /dockerv/jira/lib:/opt/atlassian/jira/atlassian-jira/WEB-INF/lib  -v /dockerv/jira/atlassian-bundled-plugins:/opt/atlassian/jira/atlassian-jira/WEB-INF/atlassian-bundled-plugins   jira:7.13.0



```

然后访问内网地址:18009



破解

```
cd /opt/atlassian/jira/
java -jar atlassian-agent.jar -d -m test@test.com -n BAT -p jira -o http://192.168.66.206 -s 刚上面截图的服务器ID
```

# Confluence

dockerfile 

```
docker build -t confluence:7.4.0  .
```



## 启动部署

```
docker run -d --name confluence1 --restart always -p 8090:8090 -e TZ="Asia/Shanghai"  -v /dockerv/confluence:/var/atlassian/confluence confluence:7.4.0
```

#  破解命令

```
java -jar atlassian-agent.jar -d -m test@test.com -n BAT -p conf -o http://192.168.66.206 -s 服务器ID

```

# 数据库配置文件

  配置

```

jdbc:mysql://192.168.66.206:3306/confluence_data?useSSL=false&amp;useUnicode=true&amp;characterEncoding=UTF8
```

插件激活

```
java -jar atlassian-agent.jar -p "com.kanoah.test-manager" -m test@test.com -n BAT -o http://192.168.66.206 -s AAAA-BBBB-CCCC-DDDD -d com.kanoah.test-manager
```

##  问题

> >  Q: confluence 中文？
> >
> > A: 操作过程
> >
> > 1.   字体安装：从windows系统上的C:\Windows\Fonts目录下拷贝缺少的字体文件或者从网络下载对应的字体文件到服务器上的指定路径下。
> >     linux上字体文件一般在/usr/share/fonts目录下，我们添加额外的字体，一般都需要新建一个独立的目录来存放字体文件。**window下拷贝C:\Windows\Fonts  -> dockerv/confluence/font**
> >
> >    cp -rf /var/atlassian/confluence/font /usr/share/fonts/msttcore
> >
> > 2.  环境配置：在confluence的安装路径下的bin目录中找到`setenv.sh`文件，在文件最后追加"CATALINA_OPTS="-Dconfluence.document.conversion.fontpath=/usr/share/fonts/msttcore ${CATALINA_OPTS}""，其中“/usr/share/fonts/msttcore”为字体存放路径，可以根据实际情况修改。**CATALINA_OPTS="-Dconfluence.document.conversion.fontpath=/usr/share/fonts/msttcore ${CATALINA_OPTS}" **
> >
> > 3. 删除指定文件confluence_home就是confluence的数据目录
> >
> >    - <confluence_home>/viewfile/
> >    - <confluence_home>/thumbnails/
> >    - <confluence_home>/shared-home/dcl-document/
> >    - <confluence_home>/shared-home/dcl-document_hd/
> >    - <confluence_home>/shared-home/dcl-thumbnail/
> >
> > 4.  重启