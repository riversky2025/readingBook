# java JNI

使用,一般使用native对c++程序进行调用  

基本过程如下  

1.  定义native方法
2. 生成.h 文件
3. c++实现生成动态库
4. 链接运行

#  定义native方法

#  生成.h文件

注意这里生成的话需要在java这个目录进行生成

Usage: javah [options] <classes>

where [options] include:

​    -help         Print this help message and exit

​    -classpath <path>   Path from which to load classes

​    -bootclasspath <path> Path from which to load bootstrap classes

​    -d <dir>        Output directory

​    -o <file>       Output file (only one of -d or -o may be used)

​    -jni          Generate JNI-style header file (default)

​    -version        Print version information

​    -verbose        Enable verbose output

​    -force         Always write output files

<classes> are specified with their fully qualified names (for instance, java.lang.Object).  



```
​```
 javah   -d ../resources/include  cn.zdsoft.datframe.dao.impl.DaApiImpl
​```
```

# # c++实现该.h

# 测试运行

```
public class DaApiImpl implements DaApi {     
static {      
System.loadLibrary("mydaapi");  
}   
@Override   native public String Login(String loginReq);
}
```

