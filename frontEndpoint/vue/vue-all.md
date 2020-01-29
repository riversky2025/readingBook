# 1. Vue.js  
## 1.1. 什么是Vue.js
+ Vue.js 是目前最火的一个前端框架，React是最流行的一个前端框架（React除了开发网站，还可以开发手机App， Vue语法也是可以用于进行手机App开发的，需要借助于Weex）
+ Vue.js 是前端的**主流框架之一**，和Angular.js、React.js 一起，并成为前端三大主流框架！
+ Vue.js 是一套构建用户界面的框架，**只关注视图层**，它不仅易于上手，还便于与第三方库或既有项目整合。（Vue有配套的第三方类库，可以整合起来做大型项目的开发）
+ 前端的主要工作？主要负责MVC中的V这一层；主要工作就是和界面打交道，来制作前端页面效果；  
## 1.2. 框架和库的区别

 + 框架：是一套完整的解决方案；对项目的侵入性较大，项目如果需要更换框架，则需要重新架构整个项目。例如 node 中的 express；
 + 库（插件）：提供某一个小功能，对项目的侵入性较小，如果某个库无法完成某些需求，可以很容易切换到其它库实现需求。
   1. 从Jquery 切换到 Zepto
   2. 从 EJS 切换到 art-template
## 1.3. Node（后端）中的 MVC 与 前端中的 MVVM 之间的区别  
![](./img/123.png)  
## 1.4. 基本使用
[代码demo](./vuecode/study.html)
# 2. 项目构建
## 2.1. 在网页中会引用哪些常见的静态资源？
+ JS
 - .js  .jsx  .coffee  .ts（TypeScript  类 C# 语言）
+ CSS
 - .css  .less   .sass  .scss
+ Images
 - .jpg   .png   .gif   .bmp   .svg
+ 字体文件（Fonts）
 - .svg   .ttf   .eot   .woff   .woff2
+ 模板文件
 - .ejs   .jade  .vue【这是在webpack中定义组件的方式，推荐这么用】
## 2.2. 网页中引入的静态资源多了以后有什么问题？？？
1. 网页加载速度慢， 因为 我们要发起很多的二次请求；
2. 要处理错综复杂的依赖关系  
  
## 2.3. 什么是webpack?
webpack 是前端的一个项目构建工具，它是基于 Node.js 开发出来的一个前端工具；  
## 2.4. 如何完美实现上述的2种解决方案
1. 使用Gulp， 是基于 task 任务的；
2. 使用Webpack， 是基于整个项目进行构建的；
+ 借助于webpack这个前端自动化构建工具，可以完美实现资源的合并、打包、压缩、混淆等诸多功能。
+ 根据官网的图片介绍webpack打包的过程
+ [webpack官网](http://webpack.github.io/)
## 2.5. webpack安装的两种方式
使用淘宝镜像(使用全局安装)   
```
npm install -g cnpm --registry=https://registry.npm.taobao.org
```
1. 运行`npm i webpack -g`全局安装webpack，这样就能在全局使用webpack的命令
2. 在项目根目录中运行`npm i webpack --save-dev`安装到项目依赖中
## 2.6. webpack使用
### 2.6.1. 仅仅打包
根目录配置webpack.config.js
```
var path=require('path');
module.exports={
    entry:path.resolve(__dirname,'src/js/main.js'),
    output:{
        path:path.resolve(__dirname,'dist'),
        filename:'bundle.js'
    },
    mode:'development'//production
}
```
然后命令行运行
`webpack`指令   
### 2.6.2. 实时打包构建  

1. 由于每次重新修改代码之后，都需要手动运行webpack打包的命令，比较麻烦，所以使用`webpack-dev-server`来实现代码实时打包编译，当修改代码之后，会自动进行打包构建。  
2. 运行`cnpm i webpack-dev-server --save-dev`安装到开发依赖
3. 安装完成之后，在命令行直接运行`webpack-dev-server`来进行打包，发现报错，此时需要借助于`package.json`文件中的指令，来进行运行`webpack-dev-server`命令，在`scripts`节点下新增`"dev": "webpack-dev-server"`指令，发现可以进行实时打包，但是dist目录下并没有生成`bundle.js`文件，这是因为`webpack-dev-server`将打包好的文件放在了内存中 
   
+ 把`bundle.js`放在内存中的好处是：由于需要实时打包编译，所以放在内存中速度会非常快
+ 这个时候访问webpack-dev-server启动的`http://localhost:8080/`网站，发现是一个文件夹的面板，需要点击到src目录下，才能打开我们的index首页，此时引用不到bundle.js文件，需要修改index.html中script的src属性为:`<script src="../bundle.js"></script>`
+ 为了能在访问`http://localhost:8080/`的时候直接访问到index首页，可以使用`--contentBase src`指令来修改dev指令，指定启动的根目录：  
```
 "dev": "webpack-dev-server --contentBase src"
```

#### 2.6.2.1. 热更新
**注意：热更新在JS中表现的不明显，可以从一会儿要讲到的CSS身上进行介绍说明！**
### 2.6.3. 方式1：
+ 修改`package.json`的script节点如下，其中`--open`表示自动打开浏览器，`--port 4321`表示打开的端口号为4321，`--hot`表示启用浏览器热更新：
```
"dev": "webpack-dev-server --hot --port 4321 --open"
```

### 2.6.4. 方式2：
1. 修改`webpack.config.js`文件，新增`devServer`节点如下：
```
devServer:{
        hot:true,
        open:true,
        port:4321
    }
```
2. 在头部引入`webpack`模块：
```
var webpack = require('webpack');
```
3. 在`plugins`节点下新增：
```
new webpack.HotModuleReplacementPlugin()
```
### 2.6.5. webpack插件使用
#### 2.6.5.1. html插件
 作用:自动添加script标签
 安装   
 ```
 cnpm i html-webpack-plugin -D
 ```
 webpack配置
 ```
 // 导入处理路径的模块
    var path = require('path');
    // 导入自动生成HTMl文件的插件
    var htmlWebpackPlugin = require('html-webpack-plugin');

    module.exports = {
        entry: path.resolve(__dirname, 'src/js/main.js'), // 项目入口文件
        output: { // 配置输出选项
            path: path.resolve(__dirname, 'dist'), // 配置输出的路径
            filename: 'bundle.js' // 配置输出的文件名
        },
        plugins:[ // 添加plugins节点配置插件
            new htmlWebpackPlugin({
                template:path.resolve(__dirname, 'src/index.html'),//模板路径
                filename:'index.html'//自动生成的HTML文件的名称
            })
        ]
    }
 ```
#### 2.6.5.2. CSS插件
1. 运行`cnpm i style-loader css-loader -D`
2. 修改`webpack.config.js`这个配置文件：
```
module: { // 用来配置第三方loader模块的
        rules: [ // 文件的匹配规则
            { test: /\.css$/, use: ['style-loader', 'css-loader'] }//处理css文件的规则
        ]
    }
```
#### 2.6.5.3. SASS插件  
1. 运行`cnpm i sass-loader node-sass -D`
2. 在`webpack.config.js`中添加处理sass文件的loader模块：
```
{ test: /\.scss$/, use: ['style-loader', 'css-loader', 'sass-loader'] }
```
#### 2.6.5.4. less插件
1. 运行`cnpm i less-loader less -D`
2. 修改`webpack.config.js`这个配置文件：
```
{ test: /\.less$/, use: ['style-loader', 'css-loader', 'less-loader'] },
```
#### 2.6.5.5. css中路径问题
1. 运行`cnpm i url-loader file-loader --save-dev`
2. 在`webpack.config.js`中添加处理url路径的loader模块：
```
{ test: /\.(png|jpg|gif)$/, use: 'url-loader' }
```
3. 可以通过`limit`指定进行base64编码的图片大小；只有小于指定字节（byte）的图片才会进行base64编码：
```
{ test: /\.(png|jpg|gif)$/, use: 'url-loader?limit=43960' },
```
## 2.7. babel处理高级JS语法
```
class A {
    b=()=>{
        console.log("hel")
    }
}
var a=new A;
a.b()

```
1. 运行`cnpm i babel-core babel-loader babel-plugin-transform-runtime -D`安装babel的相关loader包
2. 运行`cnpm i babel-preset-env babel-preset-stage-0 -D`安装babel转换的语法
3. 在`webpack.config.js`中添加相关loader模块，其中需要注意的是，一定要把`node_modules`文件夹添加到排除项：
```
{ test: /\.js$/, use: 'babel-loader', exclude: /node_modules/ }
```
4. 在项目根目录中添加`.babelrc`文件，并修改这个配置文件如下：
```
{
    "presets":["env", "stage-0"],
    "plugins":["transform-runtime"]
}
```
5. **注意：语法插件`babel-preset-es2015`可以更新为`babel-preset-env`，它包含了所有的ES相关的语法；**
转换失败的话
`cnpm i babel-loader@7 -D`

## 2.8. Vue 脚手架
vue-cli是一个vue脚手架，可以快速构造项目结构  
```
vue-cli本身集成了多种项目模板：  
    simple  很少简单  
    webpack 包含ESLint代码规范检查和unit单元测试等  
    webpack-simple 没有代码规范检查和单元测试  
    browserify 使用的也比较多  
    browserify-simple   
``` 
### 2.8.1. 安装  
```
    cnpm install vue-cli -g
    vue --version
    vue list
```  
项目创建  
```
    语法：vue init 模板名  项目名
    vue init webpack-simple  vue-cli-demo
    cd vue-cli-demo
    cnpm install  
``` 

### 2.8.2. 模块化开发
#### 2.8.2.1. 路由
用基础模版webpack-simple构建,再添加less,file等dev组件,以及axios,route.
```
vue init webpack-simple vue-li-demo
```
```
cnpm install vue-router -S  
```
该模块使用比较简单只需要3步即可
1. 组件配置
```
import Home from './components/Home.vue'
import News from './components/News.vue'
export default {
	routes:[
		{
			path:'/home',
			component:Home
		},
		{
			path:'/news',
			component:News
		}
	]
}
```
2. 组件声明  
注意这里主要是引入,配置,Vue中注入
```
import routerConfig from './router.config.js'

//使用VueRouter
Vue.use(VueRouter);
//创建路由实例
const router=new VueRouter(routerConfig);
new Vue({
  el: '#app',
  render: h => h(App),
  router
})
```
3. 组件使用  
```
<h3>
      <router-link to="/home">主页</router-link>
      <router-link to="/news">新闻</router-link>
    </h3>
    <div>
      <keep-alive>
        <router-view></router-view>
      </keep-alive>
</div>
```
>> 路由也是可以监听的,通过watch中监听数据 $route即可
#### 2.8.2.2. ajax异步请求
 安装
```
cnpm install axios -S
```
 使用
使用主要有1.声明注入2.使用两个过程
main.js声明
```
import axios from 'axios'
Vue.prototype.$http=axios;
```
使用
```
任何一个组件的方法中都可以获取使用
send(){
      this.$http.get('https://api.github.com/users/tangyang8942')
        .then(resp => {
          console.log(resp.data);
        }).catch(err => {
          console.log(err);
        });
}
```
#### 2.8.2.3. 插件制作(全局使用)
1. 定以模块
```
<template>
	<div id="login">
		{{msg}}
	</div>
</template>
<script>
	export default {
		data(){
			return {
				msg:'用户登陆'
			}
		}
	}
</script>

<style scoped>
	#login{
		color:red;
		font-size:20px;
		text-shadow:2px 2px 5px #000;
	}
</style>
```
模块index.js 注册
```
import Login from './Login.vue'
export default {
	install:function(Vue){
		Vue.component('Login',Login);
	}
}
```
全局main.js注册
```
import Login from './components/user'
Vue.use(Login);
```
App.vue使用
```
<template>
  <div id="app">
    <Login></Login>
  </div>
</template>
```
### 2.8.3. 饿了么ElementUI
项目构建
```
vue init webpack-simple element1
```
```
cnpm install
cnpm install element-ui -S
```
>> 由于美化可能需要用到less,file字体,因此需要注意引入css   
```
cnpm install less -D
cnpm install less-loader -D
cnpm install style-loader -D
```
配置对应的解析模块
```
    {
        test: /\.(eot|svg|ttf|woff|woff2)(\?\S*)?$/,
        loader: 'file-loader'
    },{
        test:/\.less$/,
        loader:'less-loader'
    }
```
使用
```
import ElementUi from 'element-ui';
import "element-ui/lib/theme-chalk/index.css"
Vue.use(ElementUi)
//全局使用  
```
### 2.8.4. vuex使用
项目构建
```
vue init webpack-simple vue-demo1
```
```
cnpm install
cnpm install vuex -S
```
配置
```
import Vue from 'vue'
import Vuex from 'vuex'
Vue.use(Vuex)
export default new Vuex.Store({
    strict: process.env.NODE_ENV !== 'production',
    state:{
        count : 6
    },
    actions: {
        increment({commit}, payload) {
            commit('increment', payload);
        },
        decrement({commit,state}){
            if(state.count>10){
                commit('decrement')
            }
        },
        incrementAsync({commit,state}){
            //异步操作
            var p=new Promise((resolve,reject) => {
                setTimeout(() => {
                    resolve();
                },3000);
            });
    
            p.then(() => {
                commit('increment');
            }).catch(() => {
                console.log('异步操作');
            });
        }
    },
    mutations: {
        increment(state)   {
            state.count++; 
        },
        decrement(state){
            state.count--;
        }
    },
    getters:{
        count(state){
            return state.count;
        },
        isEvenOrOdd(state){
            return state.count%2==0?'偶数':'奇数';
        }
    }
})
```
全局声明 
```
import store from './store'
new Vue({
  store,
  el: '#app',
  render: h => h(App)
})
```
使用
```
<template>
  <div id="app">
    <button @click="increment">增加</button>
    <button @click="decrement">减小</button>
    <button @click="incrementAsync">增加</button>
    <p>{{count}}</p>
  </div>
</template>

<script>
import { mapState, mapGetters, mapActions } from "vuex";
export default {
  name: "app",
  data() {
    return {
      msg: "Welcome to Your Vue.js App"
    };
  },
  computed: mapGetters(["count"]),
  methods: mapActions(["increment", "decrement", "incrementAsync"])
};
</script>
```

