# Win10 1903的Ubuntu运行docker需要win安装docker
并且勾选选项
Expos....
## 启用windocker
最关键的一行命令，打开Bash：
```
echo "export DOCKER_HOST=tcp://localhost:2375" >> ~/.bashrc && source ~/.bashrc
```

## 安装compose
```
 sudo apt-get install python2.7  python2.7-dev
 sudo apt-get install python-pip
 sudo pip install docker-compose
```

## zabbix搭建
[引用](https://blog.csdn.net/matengbing/article/details/81221161)  
```
version: "3"
services:
  zabbix-mysql:
    image: mysql:5.7
    container_name: zabbix-mysql
    ports: 
      - '3306'
    environment:
      - MYSQL_ROOT_PASSWORD="123456"
    volumes:
      - ./mysql_data:/var/lib/mysql
  zabbix-web-apache-mysql:
    image: zabbix/zabbix-web-apache-mysql
    container_name: zabbix-web-apache-mysql
    environment:
      - DB_SERVER_HOST=zabbix-mysql
      - MYSQL_USER=root
      - MYSQL_PASSWORD="123456"
      - ZBX_SERVER_HOST=zabbix-server-mysql
      - PHP_TZ=Asia/Shanghai
    ports:
      - '80:80'
      - '443:443'
    links:
      - zabbix-mysql
      - zabbix-server-mysql
    depends_on:
      - zabbix-mysql
  zabbix-server-mysql:
    image: zabbix/zabbix-server-mysql
    container_name: zabbix-server-mysql
    environment:
      - DB_SERVER_HOST=zabbix-mysql
      - MYSQL_USER=root
      - MYSQL_PASSWORD="123456"
    ports:
      - '10051:10051'
    links:
      - zabbix-mysql
    depends_on:
      - zabbix-mysql
```

bin/logstash-plugin install logstash-output-zabbix
a8deaaf2142a        zabbix/zabbix-web-nginx-pgsql:latest   "docker-entrypoint.sh"   3 days ago          Up 3 days           0.0.0.0:80->80/tcp, 443/tcp   zabbix-web-nginx-pgsql
c99f19bed893        zabbix/zabbix-server-pgsql:latest      "/sbin/tini -- /usr/…"   3 days ago          Up 3 days           0.0.0.0:10051->10051/tcp      zabbix-server-pgsql
701d737f1cb4        zabbix/zabbix-snmptraps:latest         "/usr/bin/supervisor…"   3 days ago          Up 3 days           0.0.0.0:162->162/udp          zabbix-snmptraps
348ba06a0583        postgres:latest                        "docker-entrypoint.s…"   3 days ago          Up 3 days           5432/tcp                      postgres-server