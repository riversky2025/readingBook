# 前言
# 简介
# Windows入门
# 脚本语言
# 基础知识

## 运行Swig

```c++
swig [ options ] filename
```

其中filename为c/c++的头文件,

```
-allegrocl            Generate ALLEGROCL wrappers
-chicken              Generate CHICKEN wrappers
-clisp                Generate CLISP wrappers
-cffi                 Generate CFFI wrappers
-csharp               Generate C# wrappers
-go                   Generate Go wrappers
-guile                Generate Guile wrappers
-java                 Generate Java wrappers
-lua                  Generate Lua wrappers
-modula3              Generate Modula 3 wrappers
-mzscheme             Generate Mzscheme wrappers
-ocaml                Generate Ocaml wrappers
-perl                 Generate Perl wrappers
-php                  Generate PHP wrappers
-pike                 Generate Pike wrappers
-python               Generate Python wrappers
-r                    Generate R (aka GNU S) wrappers
-ruby                 Generate Ruby wrappers
-sexp                 Generate Lisp S-Expressions wrappers
-tcl                  Generate Tcl wrappers
-uffi                 Generate Common Lisp / UFFI wrappers
-xml                  Generate XML wrappers

-c++                  Enable C++ parsing
-Dsymbol              Define a preprocessor symbol
-Fstandard            Display error/warning messages in commonly used format
-Fmicrosoft           Display error/warning messages in Microsoft format
-help                 Display all options
-Idir                 Add a directory to the file include path
-lfile                Include a SWIG library file.
-module name          Set the name of the SWIG module
-o outfile            Name of output file
-outcurrentdir	      Set default output dir to current dir instead of input file's path
-outdir dir           Set language specific files output directory
-pcreversion          Display PCRE version information
-swiglib              Show location of SWIG library
-version              Show SWIG version number
```



###  输入格式

 SWIG接口最常见的格式如下:   

```swig
%module mymodule 
%{
#include "myheader.h"
%}
// Now list ANSI C/C++ declarations
int foo;
int bar(int x);
...
```

 模块名是使用特殊的%module指令提供的   

所有在%{   %}内的都是原封不动的会拷贝过去.  

### 输出

例如

```
$ swig -c++ -python -o example_wrap.cpp example.i
$ swig -c++ -python -outdir pyfiles -o cppfiles/example_wrap.cpp example.i
```

结果为  

```
cppfiles/example_wrap.cpp
pyfiles/example.py
```



### 注释

采用c/c++样式

### C预处理器

 -includeall  采用的话才会对于#include 不忽略

### Swig指令

虽然只有%才是需要swig处理,但是为了融合c的头文件,会有以下支持

```
/* header.h  --- Some header file */

/* SWIG directives -- only seen if SWIG is running */ 
#ifdef SWIG
%module foo
#endif
```



### 解析器限制
虽然SWIG可以解析大多数C/ c++声明，但它并没有提供完整的C/ c++解析器实现。这些限制大多涉及非常复杂的类型声明和某些高级c++特性。具体来说，目前不支持以下功能:
* cpp文件(通常是header)

* 某些高级特性,(如内部类)

## 简单的C封装  
SWIG通过创建一个与在C程序中使用声明的方式密切匹配的接口来包装简单的C声明。例如，考虑以下接口文件:  
```
%module example 
%inline %{
extern double sin(double x);
extern int strcmp(const char *, const char *);
extern int Foo;
%}
# define STATUS 50
# define VERSION "1.1"  
```
以上中包含了两个函数,一个全局变量,两个常量  
使用时  
```
>>> example.sin(3)
5.2335956
>>> example.strcmp('Dave','Mike')
-1
>>> print example.cvar.Foo
42
>>> print example.STATUS
50
>>> print example.VERSION
1.1
```
### 基本的类型处理  
大多数脚本语言都提供了一个整数类型，该类型在C语言中使用int或long数据类型实现。下面的列表显示了SWIG将在目标语言中转换为整数或从整数转换为整数的所有C数据类型:  
```
int
short
long
unsigned
signed
unsigned short
unsigned long
unsigned char
signed char
bool
```
当从C转换一个整数值时，使用强制转换将其转换为目标语言中的表示形式。因此，一个16位的短在C可能被提升到一个32位的整数。当整数在另一个方向转换时，值被转换回原来的C类型。如果值太大而无法匹配，则将其静默截断。  
### 全局变量  
只要有可能，SWIG就会将C/ c++全局变量映射到脚本语言变量中。例如,  
```
%module example
double foo;  
```
结果在脚本语言变量像这样:
```
# Python
cvar.foo = 3.5                  # Set foo to 3.5
print cvar.foo                  # Print value of foo

```
### 常量 
可以使用#define、枚举或特殊的%constant指令创建常量。下面的接口文件显示了一些有效的常量声明:
```
#define I_CONST       5               // An integer constant
#define PI            3.14159         // A Floating point constant
#define S_CONST       "hello world"   // A string constant
#define NEWLINE       '\n'            // Character constant

enum boolean {NO=0, YES=1};
enum months {JAN, FEB, MAR, APR, MAY, JUN, JUL, AUG,
             SEP, OCT, NOV, DEC};
%constant double BLAH = 42.37;
#define PI_4 PI/4
#define FLAGS 0x04 | 0x08 | 0x40
```
### 关于const 
```
%constant double PI = 3.14159;
```
### 关于char* 
需要注意,这里是不可改变的  
因为有的语言是在常量区,不允许修改  
## 关于指针和复杂对象  
大多数C程序操作数组、结构和其他类型的对象。本节讨论这些数据类型的处理。  
### 简单指针  
这方面是支持的.  
### 派生类结构和结构体,类  
换句话说，SWIG通过引用操作其他所有操作。这个模型很有意义，因为大多数C/ c++程序都大量使用指针，而SWIG可以使用现有的类型检查指针机制来处理指向基本数据类型的指针。  
```
%module fileio
FILE *fopen(char*,char*);
int fclose(FILE*);
unsigned fread(void *ptr,unsigned size,unsigned nobj,FILE*);
unsigned fwrite(void *ptr,unsigned size,unsigned nobj,FILE*)  ;
void * malloc(int nbytes);
void free(void*);
```
在这个文件中，SWIG不知道文件是什么，但是由于它用作指针，所以它是什么并不重要。如果你把这个模块包装成Python，你可以像你期望的那样使用函数:  
```
# Copy a file 
def filecopy(source,target):
	f1 = fopen(source,"r")
	f2 = fopen(target,"w")
	buffer = malloc(8192)
	nbytes = fread(buffer,8192,1,f1)
	while (nbytes > 0):
		fwrite(buffer,8192,1,f2)
		nbytes = fread(buffer,8192,1,f1)
	free(buffer)
```
###  未定义的数据类型  
当SWIG遇到未声明的数据类型时，它会自动假设它是一个结构或类。例如，假设以下函数出现在一个SWIG输入文件中:  
```
void matrix_multiply(Matrix *a, Matrix *b, Matrix *c);
```
### 类型定义 
支持类型定义 
```
typedef unsigned int size_t;
```
例如  
```
%{
/* Include in the generated wrapper file */
typedef unsigned int size_t;
%}
/* Tell SWIG about it */
typedef unsigned int size_t;
```
或者  
```
%inline %{
typedef unsigned int size_t;
%}
```
在某些情况下，您可以包含其他头文件来收集类型信息。例如:  
```
%module example
%import "sys/types.h"
```
```
$ swig -I/usr/include -includeall example.i
```
## 其他实用的  
### 值传递 
```
double dot_product(Vector a, Vector b);
```
转换后

```
double wrap_dot_product(Vector *a, Vector *b) {
    Vector x = *a;
    Vector y = *b;
    return dot_product(x,y);
}
```
### 返回值
```
Vector cross_product(Vector v1, Vector v2);
```
这个函数想要返回Vector，但是SWIG只真正支持指针。因此，SWIG创建了一个这样的包装:
```
Vector *wrap_cross_product(Vector *v1, Vector *v2) {
        Vector x = *v1;
        Vector y = *v2;
        Vector *result;
        result = (Vector *) malloc(sizeof(Vector));
        *(result) = cross(x,y);
        return result;
}
```
如果支持c++参数生成 
```
Vector *wrap_cross(Vector *v1, Vector *v2) {
        Vector x = *v1;
        Vector y = *v2;
        Vector *result = new Vector(cross(x,y)); // Uses default copy constructor
        return result;
}
```
### 链接到结构体中的变量  
全局变量
```
Vector unit_i;
```
映射到一个底层的set/get函数对，如下所示:
```
Vector *unit_i_get() {
	return &unit_i;
}
void unit_i_set(Vector *value) {
	unit_i = *value;
}
```
### 链接char* 
```
char *foo;
```
转换后
```
/* C mode */
void foo_set(char *value) {
   if (foo) free(foo);
   foo = (char *) malloc(strlen(value)+1);
   strcpy(foo,value);
}

/* C++ mode.  When -c++ option is used */
void foo_set(char *value) {
   if (foo) delete [] foo;
   foo = new char[strlen(value)+1];
   strcpy(foo,value);
}
```
调用的话
```
set_foo("Hello World")
```
### Arrays 
```
int foobar(int a[40]);
void grok(char *argv[]);
void transpose(double a[20][20]);
```
处理它们时，就好像它们真的是这样声明的: 
```
int foobar(int *a);
void grok(char **argv);
void transpose(double (*a)[20]);
```
```
int [10];         // Maps to int *
int [10][20];     // Maps to int (*)[20]
int [10][20][30]; // Maps to int (*)[20][30]
```
## 结构体和联合  
如果SWIG遇到结构或联合的定义，它将创建一组访问器函数。尽管SWIG不需要结构定义来构建接口，但提供定义使访问结构成员成为可能。SWIG生成的访问器函数只是获取一个指向对象的指针，并允许访问单个成员。例如，  
```
struct Vector {
	double x,y,z;
}
```
```
double Vector_x_get(struct Vector *obj) {
	return obj->x;
}
double Vector_y_get(struct Vector *obj) { 
	return obj->y;
}
double Vector_z_get(struct Vector *obj) { 
	return obj->z;
}
void Vector_x_set(struct Vector *obj, double value) {
	obj->x = value;
}
void Vector_y_set(struct Vector *obj, double value) {
	obj->y = value;
}
void Vector_z_set(struct Vector *obj, double value) {
	obj->z = value;
}
```
此外，如果接口中没有定义任何函数，那么SWIG将创建默认构造函数和析构函数。  
```
truct Vector *new_Vector() {
    return (Vector *) calloc(1,sizeof(struct Vector));
}
void delete_Vector(struct Vector *obj) {
    free(obj);
}
```
```
v = new_Vector()
Vector_x_set(v,2)
Vector_y_set(v,10)
Vector_z_set(v,-5)
...
delete_Vector(v)
```
### 字符串
涉及字符串的结构需要注意。SWIG假设char * 类型的所有成员都是使用malloc()动态分配的，并且它们是以null结尾的ASCII字符串。当这样的成员被修改时，将释放以前的内容，并分配新的内容。例如:  
```
%module mymodule
...
struct Foo {
	char *name;
	...
}

```
```
char *Foo_name_get(Foo *obj) {
	return Foo->name;
}

char *Foo_name_set(Foo *obj, char *c) {
	if (obj->name) free(obj->name);
	obj->name = (char *) malloc(strlen(c)+1);
	strcpy(obj->name,c);
	return obj->name;
}
```
###  接口文件  
使用SWIG的首选方法是生成单独的接口文件。假设你有以下C头文件:
```
/* File : header.h */

#include <stdio.h>
#include <math.h>

extern int foo(double);
extern double bar(int, int);
extern void dump(FILE *f);
```
这个头文件的一个典型的SWIG接口文件应该是这样的:  
```
%module mymodule
%{
#include "header.h"
%}
extern int foo(double);
extern double bar(int, int);
extern void dump(FILE *f);
```
如果接口特别简单,也可以实用
```
/* File : interface.i */
%module mymodule
%{
#include "header.h"
%}
%include "header.h"
```
这种方法的主要优点是，当将来头文件发生更改时，只需对接口文件进行最小程度的维护。在更复杂的项目中，包含许多类似于这样的%include和#include语句的接口文件是最常见的接口文件设计方法之一，因为这样可以降低维护开销。


# Swig和C++
# SWIG和C++11 
# 预处理
# SWIG库
# 参数处理
# TypeMap  
# 自定义
# Swig和python
## 简介 
为了构建Python扩展模块，SWIG使用分层方法，其中扩展模块的部分用C定义，其他部分用Python定义。C层包含低级包装器，而Python代码用于定义高级特性。
## 简单使用  
头文件定义example.h
```
int fact(int n);
```
实现类  example.cpp
```
#include "example.h"

int fact(int n) {
    if (n < 0){ /* This should probably return an error, but this is simpler */
        return 0;
    }
    if (n == 0) {
        return 1;
    }
    else {
        /* testing for overflow would be a good idea here */
        return n * fact(n-1);
    }
}
```
swig 文件描述
```
%module example

%{
#define SWIG_FILE_WITH_INIT
#include "example.h"
%}

int fact(int n);
```
创建python版本的模块
```
swig -c++ -python example.i
```
这会创建两个不同的文件;一个C/ c++源文件example_wrap. C或example_wrap。cxx和一个Python源文件example.py。生成的C源文件包含需要编译并与C/ c++应用程序的其余部分链接以创建扩展模块的低级包装器。Python源文件包含高级支持代码。这是您将导入以使用模块的文件。  



##  c/c++包装类的手册  
##  python接口细节  
## 跨语言的多态性  
## 常见的定制特性  
## 建议
## 类型
## 类型映射
## 文档特性
## 包
## pthon3支持  



