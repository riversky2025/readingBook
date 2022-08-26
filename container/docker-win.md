



# mysql

win:

```
docker run -d  --restart=unless-stopped -p 3306:3306  -v /var/run/docker.sock:/var/run/docker.sock -v D:/dockerv/mysql/data:/var/lib/mysql -e  MYSQL_ROOT_PASSWORD=root -v D:/dockerv/mysql/config/my.cnf:/etc/mysql/my.cnf --name mysql  mysql:5.7
```

linux:

```
docker run -d  --restart=unless-stopped -p 3306:3306  -v /var/run/docker.sock:/var/run/docker.sock -v /dockerv/mysql/data:/var/lib/mysql -e  MYSQL_ROOT_PASSWORD=root -v /dockerv/mysql/config/my.cnf:/etc/mysql/my.cnf --name mysql  mysql:5.7
```

# Portainer

win:

```
docker run -d  --restart=unless-stopped -p 9000:9000  -v /var/run/docker.sock:/var/run/docker.sock -v D:/dockerv/portainer/data:/data -v D:/dockerv/portainer/public:/public --name prtainer  portainer/portainer
```

linux:

```
docker run -d  --restart=unless-stopped -p 9000:9000  -v /var/run/docker.sock:/var/run/docker.sock -v /dockerv/portainer/data:/data -v /dockerv/portainer/public:/public --name prtainer  portainer/portainer
```

# redis

win

```
docker run -d  --restart=unless-stopped   -p 6379:6379  -v /var/run/docker.sock:/var/run/docker.sock -v D:/dockerv/redis/data:/data -v D:/dockerv/redis/conf/redis.conf:/redis.conf  --name redis redis:5.0.3 redis-server /redis.conf
```

linux:

```
docker run -d  --restart=unless-stopped   -p 6379:6379  -v /var/run/docker.sock:/var/run/docker.sock -v /dockerv/redis/data:/data -v /dockerv/redis/conf/redis.conf:/redis.conf  --name redis redis:5.0.3 redis-server /redis.conf
```

# Gogs

win:

```
docker run -d  --restart=unless-stopped --name=gogs -p 10022:22 -p 3000:3000 -v D:/dockerv/gogs/data:/data gogs/gogs
```



linux:

```
docker run -d  --restart=unless-stopped --name=gogs -p 10022:22 -p 3000:3000 -v /dockerv/gogs/data:/data gogs/gogs
```

# minio

windows

```
 docker run \
    -p 9004:9000 \
    -p 9001:9001 \
    --name carpxt-minio \
    -d --restart=always \
    -v D:/dockerv/minio/data:/data \
    -e "MINIO_ROOT_USER=zzu" \
    -e "MINIO_ROOT_PASSWORD=zzufree123456" \
    minio/minio:RELEASE.2022-01-03T18-22-58Z server /data --console-address ":9001"
```



linux:

```
 docker run \
    -p 9004:9000 \
    -p 9001:9001 \
    --name carpxt-minio \
    -d --restart=always \
    -v /dockerv/minio/data:/data \
    -e "MINIO_ROOT_USER=zzu" \
    -e "MINIO_ROOT_PASSWORD=zzufree123456" \
    minio/minio:RELEASE.2022-01-03T18-22-58Z server /data --console-address ":9001"

```



# nexus3



window:

```
docker run -d --restart=unless-stopped --user root -p 8081:8081 -v F:/dockerv/nexus-data:/nexus-data   --name nexus3 sonatype/nexus3:3.14.0
```



linux:

```
docker run -d --restart=unless-stopped --user root -p 8081:8081 -v /media/zzu/新加卷1/dockerv/nexus-data:/nexus-data   --name nexus3 sonatype/nexus3:3.14.0

docker run -d --restart=unless-stopped --user root -p 8081:8081 -v /dockerv/nexus-data:/nexus-data   --name nexus3 sonatype/nexus3:3.14.0
```



# uptime-kuma

win:

linux:

```
docker run -d --restart=always -p 3001:3001 -v /dockerv/uptime-kuma:/app/data --name uptime-kuma louislam/uptime-kuma:1

```









docker run -d --restart=unless-stopped --user root -p 8081:8081 -v F:/dockerv/nexus-data:/nexus-data   --name nexus3 sonatype/nexus3:3.14.0





docker run -d  --restart=unless-stopped -p 9000:9000  -v /var/run/docker.sock:/var/run/docker.sock -v /dockerv/portainer/data:/data -v /dockerv/portainer/public:/public --name prtainer  portainer/portainer

