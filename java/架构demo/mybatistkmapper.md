# mybatis数据生成
依赖
```
  <plugin>
     <groupId>org.mybatis.generator</groupId>
     <artifactId>mybatis-generator-maven-plugin</artifactId>
     <version>1.3.2</version>
     <configuration>
         <configurationFile>src/main/resources/mybatis-generator/generatorConfig.xml</configurationFile>
         <verbose>true</verbose>
         <overwrite>true</overwrite>
     </configuration>
     <executions>
         <execution>
             <id>Generate MyBatis Artifacts</id>
             <goals>
                 <goal>generate</goal>
             </goals>
         </execution>
     </executions>
     <dependencies>
         <dependency>
             <groupId>org.mybatis.generator</groupId>
             <artifactId>mybatis-generator-core</artifactId>
             <version>1.3.2</version>
         </dependency>
         <dependency>
             <groupId>mysql</groupId>
             <artifactId>mysql-connector-java</artifactId>
             <version>5.1.46</version>
             <scope>runtime</scope>
         </dependency>
     </dependencies>
 </plugin>
```
sql表内容
```
DROP TABLE IF EXISTS category;
CREATE TABLE category (
  category_id   INT PRIMARY KEY,
  category_name VARCHAR (50) NOT NULL,
  description   VARCHAR (100)
);
DROP TABLE IF EXISTS product;
CREATE TABLE product (
  product_id    INT PRIMARY KEY auto_increment,
  category_id   INT NOT NULL,
  product_name  VARCHAR (50) NOT NULL,
  price         DECIMAL
);
DELETE FROM category;
INSERT INTO category (category_id, category_name, description) VALUES
  (1, 'Beverages', 'test'),
  (2, 'Condiments', 'test'),
  (3, 'Oil', 'test');
  DELETE FROM product;
INSERT INTO product (product_id, category_id, product_name, price) VALUES
  (1, 1, 'Northwind Traders Chai', 18.0000),
  (2, 2, 'Northwind Traders Syrup', 7.5000),
  (3, 2, 'Northwind Traders Cajun Seasoning', 16.5000),
  (4, 3, 'Northwind Traders Olive Oil', 16.5000),
  (5, 3, 'Northwind Traders Olive Oil2', 16.5000);
```
生成配置
```
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE generatorConfiguration
    PUBLIC "-//mybatis.org//DTD MyBatis Generator Configuration 1.0//EN"
    "http://mybatis.org/dtd/mybatis-generator-config_1_0.dtd">

<generatorConfiguration>
    <!--<classPathEntry location="/Program Files/IBM/SQLLIB/java/db2java.zip" />-->

    <context id="Mybatis3Context" targetRuntime="MyBatis3">
        <property name="javaFileEncoding" value="UTF-8"/>
        <!--因为生成过程中需要连接db，指定了驱动jar包的位置-->
        <jdbcConnection driverClass="com.mysql.jdbc.Driver"
                        connectionURL="jdbc:mysql://localhost:3306/d524?useLegacyDatetimeCode=false&amp;serverTimezone=UTC&amp;nullCatalogMeansCurrent=true"
                        userId="root"
                        password="riversky">
        </jdbcConnection>

        <javaTypeResolver>
            <property name="forceBigDecimals" value="false"/>
        </javaTypeResolver>
        <!--19-33行指定生成“entity实体类、-->
        <javaModelGenerator targetPackage="xyz.mybts.demo.domain" targetProject="H:/sutdy/java/demo/src/main/java">
            <property name="enableSubPackages" value="true"/>
            <property name="trimStrings" value="true"/>
        </javaModelGenerator>
        <!--mybatis映射xml文件、-->
        <sqlMapGenerator targetPackage="xyz.mybts.demo.repository.maperxml" targetProject="H:/sutdy/java/demo/src/main/java">
            <property name="enableSubPackages" value="true"/>
        </sqlMapGenerator>
        <!--mapper接口”的具体位置-->
        <javaClientGenerator type="XMLMAPPER" targetPackage="xyz.mybts.demo.repository" targetProject="H:/sutdy/java/demo/src/main/java">
            <property name="enableSubPackages" value="true"/>
        </javaClientGenerator>
        <!--具体要生成的表，如果有多个表，复制这一段，改下表名即可-->
        <table tableName="category" domainObjectName="Category" enableCountByExample="false"
               enableDeleteByExample="false" enableUpdateByExample="false" enableSelectByExample="false">
        </table>
        <table tableName="product" domainObjectName="Product" enableCountByExample="false"
               enableDeleteByExample="false" enableUpdateByExample="false" enableSelectByExample="false">
        </table>

    </context>
</generatorConfiguration>
```
# tk使用
依赖
```
<dependency>
    <groupId>tk.mybatis</groupId>
    <artifactId>mapper-spring-boot-starter</artifactId>
    <version>2.0.2</version>
</dependency>
<dependency>
    <groupId>org.projectlombok</groupId>
    <artifactId>lombok</artifactId>
    <version>1.18.6</version>
</dependency>
<dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
    <version>5.1.38</version>
</dependency>
```
配置部分: 
```
spring.datasource.url=jdbc:mysql://localhost:3306/d524
spring.datasource.username=root
spring.datasource.password=riversky
spring.datasource.driver-class-name=com.mysql.jdbc.Driver

#mapper.mappers=xyz.mybts.demo.repository 数组解析出错,可以在Application上配置注解@MapperScan(basePackages = "xyz.mybts.demo.repository")代替
mapper.not-empty=false
mapper.i-d-e-n-t-i-t-y=MYSQL
```
删除xml,以及Mapper内的方法 
修改如下:  
```
@Repository
public interface CategoryDao extends Mapper<Category> {

}
```
测试
```
@RunWith(SpringRunner.class)
@SpringBootTest
@ContextConfiguration(classes = DemoApplication.class)
public class DemoApplicationTests {

    @Autowired
    private CategoryDao productMapper;
    @Test
    public void contextLoads() {
        List<Product> products = productMapper.selectAll();
        System.out.println(products);
    }
}
```
# 分页使用  
依赖 
```
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-web</artifactId>
</dependency>

<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-test</artifactId>
    <scope>test</scope>
</dependency>
<dependency>
    <groupId>com.github.pagehelper</groupId>
    <artifactId>pagehelper-spring-boot-starter</artifactId>
    <version>1.2.5</version>
</dependency>
<dependency>
    <groupId>tk.mybatis</groupId>
    <artifactId>mapper-spring-boot-starter</artifactId>
    <version>2.0.2</version>
</dependency>
<dependency>
    <groupId>org.projectlombok</groupId>
    <artifactId>lombok</artifactId>
    <version>1.18.6</version>
</dependency>
<dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
    <version>5.1.38</version>
</dependency>
```
注意版本,spring boot版本2.0以上,pagehelper版本1.2.5(低版本可能无法通过)    
配置  
```
spring.datasource.url=jdbc:mysql://localhost:3306/d524
spring.datasource.username=root
spring.datasource.password=riversky
spring.datasource.driver-class-name=com.mysql.jdbc.Driver

#mapper.mappers=xyz.mybts.demo.repository
mapper.not-empty=false
mapper.i-d-e-n-t-i-t-y=MYSQL


pagehelper.helperDialect=mysql
pagehelper.reasonable=true
pagehelper.supportMethodsArguments=true
pagehelper.params=count=countSql
pagehelper.page-size-zero=true
```
分页Service  
```
@Service
public class ProductService {
    @Autowired
    private ProductDao productDao;
    public PageInfo<Product> getProduct(int page, int size){
        PageHelper.startPage(page,size);
        List<Product> products = productDao.selectAll();
        PageInfo<Product> productPageInfo=new PageInfo<>(products);
        return  productPageInfo;
    }
}
```
测试  
```
@RunWith(SpringRunner.class)
@SpringBootTest
@ContextConfiguration(classes = DemoApplication.class)
public class DemoApplicationTests {

    @Autowired
    private ProductService productMapper;
    @Test
    public void contextLoads() {
        PageInfo<Product> products = productMapper.getProduct(2,2);
        System.out.println(products);
    }
}
```
# 项目流程
1.  先决条件,mysql数据库,以及数据库中的表
2.  利用mavent插件mybatis生成domain,dao,xml
3.  删除xml,dao中冗余数据,继承tk.Mapper的接口
4.  配置各项内容
5.  测试

