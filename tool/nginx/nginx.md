#  nginx 容器

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

# 配置  

##  tcp代理  

```
stream{
	
		upstream Sgx {
			server 203.125.103.170:10001 max_fails=3 fail_timeout=10s;
		}		
		upstream Enussy{                                         
			server 123.161.206.213:8383 max_fails=3 fail_timeout=10s;   
		}
		upstream zhongyi{                                         
			server 119.188.44.24:18402 max_fails=3 fail_timeout=10s;   
		}
		server{
			listen 10001;
			proxy_pass Sgx;
		}
		server{
			listen 8383;
			proxy_pass Enussy;
		}
		server{
		listen 18402;
		proxy_pass zhongyi;
		}
		
}
```

##  ssl 值https 与wss

```
http {
    include       mime.types;
    default_type  application/octet-stream;

    #log_format  main  '$remote_addr - $remote_user [$time_local] "$request" '
    #                  '$status $body_bytes_sent "$http_referer" '
    #                  '"$http_user_agent" "$http_x_forwarded_for"';

    #access_log  logs/access.log  main;

    sendfile        on;
    #tcp_nopush     on;

    #keepalive_timeout  0;
    keepalive_timeout  65;

    #gzip  on;

    # server {
    #     listen       8067;
    #     server_name  localhost;
    # 
    #     #charset koi8-r;
    # 
    #     #access_log  logs/host.access.log  main;
    # 
    #     location / {
    #         root   html;
    #         index  index.html index.htm;
    #     }
    # 
    #     #error_page  404              /404.html;
    # 
    #     # redirect server error pages to the static page /50x.html
    #     #
    #     error_page   500 502 503 504  /50x.html;
    #     location = /50x.html {
    #         root   html;
    #     }
    # 
    #     # proxy the PHP scripts to Apache listening on 127.0.0.1:80
    #     #
    #     #location ~ \.php$ {
    #     #    proxy_pass   http://127.0.0.1;
    #     #}
    # 
    #     # pass the PHP scripts to FastCGI server listening on 127.0.0.1:9000
    #     #
    #     #location ~ \.php$ {
    #     #    root           html;
    #     #    fastcgi_pass   127.0.0.1:9000;
    #     #    fastcgi_index  index.php;
    #     #    fastcgi_param  SCRIPT_FILENAME  /scripts$fastcgi_script_name;
    #     #    include        fastcgi_params;
    #     #}
    # 
    #     # deny access to .htaccess files, if Apache's document root
    #     # concurs with nginx's one
    #     #
    #     #location ~ /\.ht {
    #     #    deny  all;
    #     #}
    # }
	
    # another virtual host using mix of IP-, name-, and port-based configuration
    #
    #server {
    #    listen       8000;
    #    listen       somename:8080;
    #    server_name  somename  alias  another.alias;

    #    location / {
    #        root   html;
    #        index  index.html index.htm;
    #    }
    #}


    # HTTPS server
    #
    server {
        listen       443 ssl;
        server_name  localhost;
	ssl  on;

        ssl_certificate      /etc/nginx/keys/server.crt;
        ssl_certificate_key  /etc/nginx/keys/server.key;

        ssl_session_cache    shared:SSL:1m;
        ssl_session_timeout  5m;

        ssl_ciphers  HIGH:!aNULL:!MD5;
        ssl_prefer_server_ciphers  on;

        location / {
	        proxy_pass http://192.168.1.158:8094;
		proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
		proxy_set_header X-Forwarded-Proto $scheme;
		proxy_set_header X-Forwarded-Port $server_port;
        }
	location /sub {
		proxy_pass http://192.168.1.158:8094;
		proxy_http_version 1.1;
                proxy_set_header Upgrade $http_upgrade;
                proxy_set_header Connection "upgrade";
	}
    }

}
```

###  需要注意

配置ssl需要nginx模块具有该编译选项，可以`nginx -V` 验证  

另外，需要申请证书，以及私钥信息 ，过程如下

**linux为例子**

1.   生成密钥`openssl genrsa -des3 -out server.key 2048`,以及调用密码跳过`openssl rsa -in server.key -out server.key`
2.  创建证书申请文件`openssl req -new -key server.key -out server.csr`  
3.  创建CA证书(给自己签名用)`openssl req -new -x509 -key server.key -out ca.crt -days 3650`  
4.  创建当日起十年有效的服务器证书  `openssl x509 -req -days 3650 -in server.csr -CA ca.crt -CAkey server.key -CAcreateserial -out server.crt`  

其中第一步的server.key与第4步骤的证书供给nginx使用

# 规范化配置

对于不同需求的配置，可以分开文件，并在nginx.conf引入的方式进行配置

##  tcp代理

```
tcpproxy.conf
stream{

                upstream Sgx {
                        server 203.125.103.170:10001 max_fails=3 fail_timeout=10s;
                }
                upstream Enussy{
                        server 123.161.206.213:8383 max_fails=3 fail_timeout=10s;
                }
                upstream zhongyi{
                        server 119.188.44.24:18402 max_fails=3 fail_timeout=10s;
                }
                server{
                        listen 10001;
                        proxy_pass Sgx;
                }
                server{
                        listen 8383;
                        proxy_pass Enussy;
                }
                server{
                listen 18402;
                proxy_pass zhongyi;
                }

 }
```



##   https与wss

```
webssl.conf
http{
    include       mime.types;
    default_type  application/octet-stream;
    sendfile        on;
    keepalive_timeout  65;
    #https
    server {
        listen       443 ssl;
        server_name  localhost;
	    ssl  on;
        ssl_certificate      /etc/nginx/keys/server.crt;
        ssl_certificate_key  /etc/nginx/keys/server.key;
        ssl_session_cache    shared:SSL:1m;
        ssl_session_timeout  5m;
        ssl_ciphers  HIGH:!aNULL:!MD5;
        ssl_prefer_server_ciphers  on;
        location / {
	        proxy_pass http://192.168.1.158:8094;
			proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
			proxy_set_header X-Forwarded-Proto $scheme;
			proxy_set_header X-Forwarded-Port $server_port;
        }
        #wss
		location /sub {
			proxy_pass http://192.168.1.158:8094;
			proxy_http_version 1.1;
            proxy_set_header Upgrade $http_upgrade;
            proxy_set_header Connection "upgrade";
		}
    }
}
```



