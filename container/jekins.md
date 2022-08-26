# jekins 

 Jenkins是开源CI&CD软件领导者，提供超过1000个插件来支持构建、部署、自动化，满足任何项目的需要。我们可以用Jenkins来构建和部署我们的项目，比如说从我们的代码仓库获取代码，然后将我们的代码打包成可执行的文件，之后通过远程的ssh工具执行脚本来运行我们的项目。   

## 插件

1.  pipeline-utility-steps 

## Jekins 环境变量

```
在Jenkins的设置中可以设置全局变量, jenkins主页面->Manage Jenkins->Configure System->Global Properties 中, 将Environment variables复选框选中,会出来List of variables, 填入以下内容: 
/etc/profile  不会被load进来
name: JAVA_HOME value:XXX
name: M2_HOME value:/usr/cyz/apache-maven-3.6.1
name: PATH+EXTRA value: $M2_HOME/bin
```

## 常见问题 

1.  

```
+ docker build -t 192.168.1.158:20000/com.shanghaizhida.finanace-finanace:9af34dd --build-arg SPRING_PROFILE=prod --build-arg JAR_FILE=finanace-admin/target/finanace-1.0-SNAPSHOT.jar ./finanace-admin
Got permission denied while trying to connect to the Docker daemon socket at 


方法

添加docker用户组

groupadd docker 

把当前用户加入docker用户组

gpasswd -a ${USER} docker

查看是否添加成功

cat /etc/group | grep ^docker

重启docker

更新用户组

newgrp docker


```



1. 

## IDEA 支持

安装Jenkins 插件后

1.  Jenkins上安全管理中启动跨站功能,并且 [/crumbIssuer/api/xml?tree=crumb#](http://http//localhost:8080/crumbIssuer/api/xml?tree=crumb#)  下进行获取



## windows 

[推荐]( https://www.jianshu.com/p/de9c4f5ae7fa )

# linux

[安装]( https://www.jenkins.io/doc/book/installing/#red-hat-centos )

java环境

在[官网](https://www.oracle.com/java/technologies/javase/javase-jdk8-downloads.html   )找到所要的包

```
# 卸载旧环境
#1. 查询包
rpm -qa|grep java
#2. 卸载
rpm -e --nodeps java-1.7.0-openjdk-1.7.0.45-2.4.3.3.el6.x86_64

rpm -e --nodeps java-1.6.0-openjdk-1.6.0.0-1.66.1.13.0.el6.x86_64
# 剩余的不用卸载
[root@localhost sh]# rpm -qa|grep java
javapackages-tools-3.4.1-11.el7.noarch
python-javapackages-3.4.1-11.el7.noarch
tzdata-java-2018e-3.el7.noarch
tzdata-java-2020a-1.el7.noarch


#3. 下载后放到/usr/local下,并进行解压,删除原包
tar -zxvf jdk-8u251-linux-x64.tar.gz
rm jdk-8u251-linux-x64.tar.gz
#4. 配置环境变量
vi /etc/profile
-------
export JAVA_HOME=/usr/local/java/jdk1.8.0_251 
export CLASSPATH=.:$JAVA_HOME/jre/lib/rt.jar:$JAVA_HOME/lib/dt.jar:$JAVA_HOME/lib/tools.jar
export PATH=$PATH:$JAVA_HOME/bin  
----------
#5. 使得环境变量生效,并验证
[root@localhost jdk1.8.0_251]# source /etc/profile
[root@localhost jdk1.8.0_251]# java -version
java version "1.8.0_251"
Java(TM) SE Runtime Environment (build 1.8.0_251-b08)
Java HotSpot(TM) 64-Bit Server VM (build 25.251-b08, mixed mode)

```



maven环境 

```
# 下载
cd /usr/local/java/maven/
wget  https://mirrors.bfsu.edu.cn/apache/maven/maven-3/3.6.3/binaries/apache-maven-3.6.3-bin.tar.gz
#2. 解压后,配置环境变量
vi /etc/profile
​``````````
export MAVEN_HOME=/usr/local/java/maven/apache-maven-3.6.3
export PATH=${MAVEN_HOME}/bin:$PATH
​``````````
#3. 使得环境变量生效
source /etc/profile
mvn -version
```

git 环境

```
yum install git
```



jenkins环境

```
sudo wget -O /etc/yum.repos.d/jenkins.repo   https://pkg.jenkins.io/redhat-stable/jenkins.repo
sudo rpm --import https://pkg.jenkins.io/redhat-stable/jenkins.io.key
sudo yum upgrade
sudo yum install jenkins 

sudo systemctl start jenkins
sudo systemctl status jenkins

systemctl daemon-reload

systemctl enable jenkins

systemctl start jenkins
```

> > 如果发现启动不起来,可能是jenkins的jdk环境配置有问题
> >
> > ```
> > vi /etc/init.d/jenkins 
> > 
> > ```
> >
> > ![1591593571964](.\img\1591593571964.png)

默认8080端口



## C++ 自动化,编译以及跑单元测试  

采用cppunit方案

需要插件

1. msbuild 
2. xunit



需要配置msbuild 路径在配置中心  



![1591248202794](.\img\1591248202794.png)
### 保证依赖加入  
目前只测试64 release版本
```
vcpkg install cppunit:x64-windows-static
```
创建项目,并修改为静态链接  
```
  <PropertyGroup Label="Globals">
    <!-- .... -->
    <VcpkgTriplet Condition="'$(Platform)'=='Win32'">x86-windows-static</VcpkgTriplet>
    <VcpkgTriplet Condition="'$(Platform)'=='x64'">x64-windows-static</VcpkgTriplet>
  </PropertyGroup>
```
### CppUnit 
#### 基本原理
首先要明确我们写测试代码的目的，就是验证代码的正确性或者调试 bug。这样写测试代码时就有了针对性，对那些容易出错的，易变的编写测试代码；而不用对每个细节，每个功能编写测试代码，当然除非有过量精力或者可靠性要求。

根据上面说的目的、思想，下面总结一下平时开发过程中单元测试的原则：

* 先写测试代码，然后编写符合测试的代码。至少做到完成部分代码后，完成对应的测试代码；
* 测试代码不需要覆盖所有的细节，但应该对所有主要的功能和可能出错的地方有相应的测试用例；
*  发现 bug，首先编写对应的测试用例，然后进行调试；
*  不断总结出现 bug 的原因，对其他代码编写相应测试用例；
*  每次编写完成代码，运行所有以前的测试用例，验证对以前代码影响，把这种影响尽早消除；
*  不断维护测试代码，保证代码变动后通过所有测试；

#### CppUnit 原理  
在 CppUnit 中，一个或一组测试用例的测试对象被称为 Fixture（设施，下文为方便理解尽量使用英文名称）。Fixture 就是被测试的目标，可能是一个对象或者一组相关的对象，甚至一个函数。  
有了被测试的 fixture，就可以对这个 fixture 的某个功能、某个可能出错的流程编写测试代码，这样对某个方面完整的测试被称为TestCase（测试用例）。通常写一个 TestCase 的步骤包括：  
1. 对 fixture 进行初始化，及其他初始化操作，比如：生成一组被测试的对象，初始化值；
2. 按照要测试的某个功能或者某个流程对 fixture 进行操作；
3. 验证结果是否正确；
4. 对 fixture 的及其他的资源释放等清理工作。

对 fixture 的多个测试用例，通常（1）（4）部分代码都是相似的，CppUnit 在很多地方引入了 setUp 和 tearDown 虚函数。可以在 setUp 函数里完成（1）初始化代码，而在 tearDown 函数中完成（4）代码。具体测试用例函数中只需要完成（2）（3）部分代码即可，运行时 CppUnit 会自动为每个测试用例函数运行 setUp，之后运行 tearDown，这样测试用例之间就没有交叉影响。  
#### 最佳实践
一般分为两个项目,一个是程序的,另一个是测试的.
程序源码项目  
包含的头文件  

简单的举个栗子  
```
#pragma once
/**
 * 功能函数加减两个方法待测试
 */
class Calculator
{
public:
	int add()
	{
		return num1 + num2;
	}
	int sub() const
	{
		return num1 - num2;
	}
public:
	int num1;
	int num2;
};
```
测试项目需要引入原项目的扫描头文件与源码
然后编写测试类  
```
#pragma once
#include <memory>


#include "Calculator.h"
#include "cppunit/TestFixture.h"
#include "cppunit/TestAssert.h"
class CalculatorTest :public CppUnit::TestFixture
{
public:
	void setUp() override
	{
		calculatorPtr = std::make_shared<Calculator>();
		calculatorPtr->num1 = 5;
		calculatorPtr->num2 = 6;
	}
	void tearDown() override {}
	void testAdd()
	{
		CPPUNIT_ASSERT_EQUAL(11, calculatorPtr->add());
		CPPUNIT_ASSERT_EQUAL_MESSAGE("xiangdeng ", 11, calculatorPtr->add());
	}
	void testSub()
	{
		CPPUNIT_ASSERT_EQUAL(-1, calculatorPtr->sub());
		CPPUNIT_ASSERT_EQUAL_MESSAGE("xiangdeng ", -1, calculatorPtr->sub());
	}
private:
	std::shared_ptr<Calculator> calculatorPtr;
};

```
>>  CppUnit 提供了多种验证成功失败的方式：  
```
CPPUNIT_ASSERT(condition)   // 确信condition为真
CPPUNIT_ASSERT_MESSAGE(message, condition)  
// 当condition为假时失败, 并打印message
CPPUNIT_FAIL(message)            
// 当前测试失败, 并打印message
CPPUNIT_ASSERT_EQUAL(expected, actual)    
// 确信两者相等
CPPUNIT_ASSERT_EQUAL_MESSAGE(message, expected, actual)  
// 失败的同时打印message
CPPUNIT_ASSERT_DOUBLES_EQUAL(expected, actual, delta)  
// 当expected和actual之间差大于delta时失败
```
要把对 fixture 的一个测试函数转变成一个测试用例，需要生成一个 CppUnit::TestCaller 对象。而最终运行整个应用程序的测试代码的时候，可能需要同时运行对一个 fixture 的多个测试函数，甚至多个 fixture 的测试用例。CppUnit 中把这种同时运行的测试案例的集合称为 TestSuite。而 TestRunner 则运行测试用例或者 TestSuite，具体管理所有测试用例的生命周期。  
下面是一个demo
```
 #include "CalculatorTest.h"
#include "cppunit/TestSuite.h"
#include "cppunit/TestCaller.h"
#include "cppunit/ui/text/TestRunner.h"
int main(int argc, char* argv[])
{
	CppUnit::TextUi::TestRunner runner;
	CppUnit::TestSuite* suite = new CppUnit::TestSuite();
	suite->addTest(new CppUnit::TestCaller<CalculatorTest>("testAdd", &CalculatorTest::testAdd));
	suite->addTest(new CppUnit::TestCaller<CalculatorTest>("testSub", &CalculatorTest::testSub));
	runner.addTest(suite);
	runner.run("", true);
	return 0;
}

```

![1591253751321](.\img\1591253751321.png)

这是测试结果  两个均通过

#### 然后git支持  

目前提交的为gogs  ,提交到代码仓库中

##  jekins

1.  插件安装

 本例要用到 Git、MSBuild 和 xUnit ,gogs插件三个插件，第一步就是安装它们。 

需要注意,git,msbuild的配置需要宿主机路径也配置进去  

2. 创建自由风格的软件项目

创建构建任务,需要注意,根据自己的配置需求进行配置.

```
http://gogs:8080/gogs-webhook/?job=jksforcpp
```

> > 如果配置密码的话,需要在jenkins上进行配置

3. 邮件设置  

> > 需要注意上面的系统管理员邮件一定要与认证的用户名相同

![1591262434233](.\img\1591262434233.png)

运行结果后

![1591275299207](.\img\1591275299207.png)

> > 点开后有错误详情

####  java 项目管理

插件

1.  Role-based Authorization Strategy 
2.  SSH 
3.   Maven Integration plugin
4.   docker-build-step
5.  Docker plugin
6.  Gogs 

**基础设施** 
1.   jenkins ,
2.   maven 
3.   git
4.   java docker 
5.   docker register
具体使用过程
##### 代码架构

![1592644787256](.\img\1592644787256.png)

其中Jenkinsfile 为jenkins pipeline

Dockerfile 为image打包工具

#####  详细文件

```dockerfile
# 注意:日志文件位于/tmp文件夹,程序位于/app路径下
FROM  ascdc/jdk8:latest
VOLUME /tmp
ARG JAR_FILE
ADD ${JAR_FILE} /app/app.jar
EXPOSE 8080
ENTRYPOINT ["java","-Djava.security.egd=file:/dev/./urandom","-jar","/app/app.jar"]
```
```jenkins
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

}
```

##### git 仓库管理
然后代码仓库进行设置并且提交

![1592645100770](.\img\1592645100770.png)

##### Jenkins创建项目
选择pipeline 

![1592645280406](.\img\1592645280406.png)

> > Secret 为上面gogs配置的

![1592645453659](.\img\1592645453659.png)

然后就需要根据Jenkinsfile里的语法对业务进行组合了.一旦git push发生,就会触发该pipeline

##### 云服务话
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

3. jenkins 支持

   两种方式

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

   > > 关于workload 可以从负载url获取

```

```

## 宿主机tomcat

1. 安装

```
下载tomcat
[root@hyc ~]# cd /usr/src/
[root@hyc src]# wget http://mirror.bit.edu.cn/apache/tomcat/tomcat-9/v9.0.24/bin/apache-tomcat-9.0.24.tar.gz
# wget https://mirrors.huaweicloud.com/apache/tomcat/tomcat-9/v9.0.24/bin/apache-tomcat-9.0.24.tar.gz

解压部署
[root@hyc src]# tar xf apache-tomcat-9.0.24.tar.gz -C /usr/local/
[root@hyc src]# cd /usr/local/
[root@hyc local]# ln -s apache-tomcat-9.0.24/ tomcat
[root@hyc local]# ll
总用量 0
drwxr-xr-x. 9 root root 220 8月  29 22:22 apache-tomcat-9.0.24
drwxr-xr-x. 2 root root   6 3月  10 2016 bin
drwxr-xr-x. 2 root root   6 3月  10 2016 etc
drwxr-xr-x. 2 root root   6 3月  10 2016 games
drwxr-xr-x. 2 root root   6 3月  10 2016 include
drwxr-xr-x. 2 root root   6 3月  10 2016 lib
drwxr-xr-x. 2 root root   6 3月  10 2016 lib64
drwxr-xr-x. 2 root root   6 3月  10 2016 libexec
drwxr-xr-x. 2 root root   6 3月  10 2016 sbin
drwxr-xr-x. 5 root root  49 7月   3 23:24 share
drwxr-xr-x. 2 root root   6 3月  10 2016 src
lrwxrwxrwx. 1 root root  20 8月  29 22:22 tomcat -> apache-tomcat-9.0.24/


写一个hello world的java页面
[root@hyc ~]# vim index.jsp
[root@hyc ~]# cat index.jsp 
<html>
<head>
        <title>test page</title>
</head>
<body>
        <%
            out.println("Hellow World");
        %>
</body>
</html>

[root@hyc ~]# mkdir /usr/local/tomcat/webapps/test
[root@hyc ~]# cp index.jsp /usr/local/tomcat/webapps/test/
[root@hyc ~]# ll /usr/local/tomcat/webapps/test/
总用量 4
-rw-r--r--. 1 root root 141 8月  29 22:28 index.jsp


启动tomcat
[root@hyc ~]# /usr/local/tomcat/bin/catalina.sh start
Using CATALINA_BASE:   /usr/local/tomcat
Using CATALINA_HOME:   /usr/local/tomcat
Using CATALINA_TMPDIR: /usr/local/tomcat/temp
Using JRE_HOME:        /usr
Using CLASSPATH:       /usr/local/tomcat/bin/bootstrap.jar:/usr/local/tomcat/bin/tomcat-juli.jar
Tomcat started.

[root@hyc ~]#  ps -ef|grep tomcat
root       2560      1 20 22:28 pts/1    00:00:02 /usr/bin/java -Djava.util.logging.config.file=/usr/local/tomcat/conf/logging.properties -Djava.util.logging.manager=org.apache.juli.ClassLoaderLogManager -Djdk.tls.ephemeralDHKeySize=2048 -Djava.protocol.handler.pkgs=org.apache.catalina.webresources -Dorg.apache.catalina.security.SecurityListener.UMASK=0027 -Dignore.endorsed.dirs= -classpath /usr/local/tomcat/bin/bootstrap.jar:/usr/local/tomcat/bin/tomcat-juli.jar -Dcatalina.base=/usr/local/tomcat -Dcatalina.home=/usr/local/tomcat -Djava.io.tmpdir=/usr/local/tomcat/temp org.apache.catalina.startup.Bootstrap start
root       2602   2402  0 22:28 pts/1    00:00:00 grep --color=autotomcat

[root@hyc ~]# ss -antl
State      Recv-Q Send-Q Local Address:Port               Peer Address:Port              
LISTEN     0      128     *:22                  *:*                  
LISTEN     0      100    127.0.0.1:25                  *:*                  
LISTEN     0      100    :::8080               :::*                  
LISTEN     0      128    :::22                 :::*                  
LISTEN     0      100       ::1:25                 :::*                  
LISTEN     0      1        ::ffff:127.0.0.1:8005               :::*                  
LISTEN     0      100    :::8009               :::*                

```

2. 配置

```
配置一
[root@hyc ~]# vim /usr/local/tomcat/conf/tomcat-users.xml
[root@hyc ~]# tail -4 /usr/local/tomcat/conf/tomcat-users.xml 
<role rolename="admin-gui"/>
<role rolename="manager-gui"/>
<user username="tomcat" password="123456" roles="admin-gui,manager-gui"/>
</tomcat-users>   ## 在此行前面添加以上内容

注意：admin-gui是管理Host Manager项的，manager-gui是管理Server status和Manager App项

配置二
vim /usr/local/tomcat/webapps/manager/META-INF/context.xml



<Context antiResourceLocking="false" privileged="true" >
  <Valve className="org.apache.catalina.valves.RemoteAddrValve"
         allow="192\.168\.30\.\d+|127\.\d+\.\d+\.\d+|::1|0:0:0:0:0:0:0:1" />     ##此处要允许宿主机的ip访问
  <Manager sessionAttributeValueClassNameFilter="java\.lang\.(?:Boolean|Integer|Long|Number|String)|org\.apache\.catalina\.filters\.CsrfPreventionFilter\$LruCache(?:\$1)?|java\.util\.(?:Linked)?HashMap"/>
</Context>

```

3. 重启

   ```
   [root@hyc ~]# /usr/local/tomcat/bin/shutdown.sh 
   [root@hyc ~]# /usr/local/tomcat/bin/startup.sh 
   
   ```

   



