# 简介  
Vuex 是一个专为 Vue.js 应用程序开发的 状态管理模式。它采用集中式存储管理应用的所有组件的状态，并以相应的规则保证状态以一种可预测的方式发生变化。  
# 目标 
继续之前 vue-router 章节做的案例项目，我们通过完善登录功能将用户信息保存至 Vuex 中来体会它的作用；  
# 安装  
```
npm install vuex -S
```
main.js声明使用  
```
import Vuex from 'vuex'
Vue.use(Vuex);
```
# 判断用户是否登录  
路由钩子可以起到作用  
我们利用路由钩子 beforeEach 来判断用户是否登录，期间会用到 sessionStorage 存储功能  
## sessionStore中存储登录标识  
```
// 设置用户登录成功
sessionStorage.setItem('isLogin', 'true');
```
## 登录过滤  
利用路由钩子beforeEach方法判断用户是否成功登录,关键代码如下:  
```

```