# 1. Gorm入门
## 1.1. 功能特性
* 支持orm全特性
* 多种关系处理(一对多,一对一,多对多,属于,多态等)
* 切面(前置,后置,增删改查)
* 预加载
* 事务
* 联合主键
* SQL构建器
* 自动迁移
* 日志
* 扩展,插件支持
### 1.1.1. 安装
```
go get -u github.com/jinzhu/gorm
```  
### 1.1.2. 快速入门
```
package gailan

import (
	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/sqlite"
)

type Product struct {
	gorm.Model
	Code string
	Price uint
}

func K1Start() {
	db, err := gorm.Open("sqlite3", "test.db")
	if err!=nil{
		panic("failed to connect database")
	}
	defer db.Close()
	//自动迁移
	db.AutoMigrate(&Product{})
	//创建
	db.Create(&Product{Code:"L1212",Price:1000})
	//读取
	var product Product
	db.First(&product,1)//查询id为1的product
	db.First(&product,"code=?","L1212")//查询code为L1212的product
	//更新
	db.Model(&product).Update("Price",2000)
	//删除
	db.Delete(&product)
}
```

## 1.2. 模型定义  
模型（Models）通常只是正常的 golang structs、基本的 go 类型或它们的指针。 同时也支持sql.Scanner及driver.Valuer 接口（interfaces）。  
模型示例:  
```
type User struct {
	gorm.Model
	Name         string
	Age          sql.NullInt64
	Birthday *time.Time
	Email string `gorm:"type:varchar(100);unique_index"`
	Role string `gorm:"size:255"`
	MemberNumber *string`gorm:"unique;not null"`
	Num int `gorm:"AUTO_INCREMENT"`
	Address string `gorm:"index:addr"`
	IgnoreMe int `gorm:"-"`//忽略本字段
}
```
**结构体标记** 
标记（tags）在声明模型时是可选项。gorm 支持以下标记:  
|结构体标记|描述|
|:--|:--|
|Column|指定列名|
|Type|指定列数据类型|
|SIze|指定列大小,默认255|
|PRIMARY_KEY|指定为主键|
|UNIQUE|将列指定为唯一|
|DEFAULT|指定默认值|
|PRECISION|	指定列精度|
|NOT NULL	|将列指定为非 NULL|
|AUTO_INCREMENT|	指定列是否为自增类型|
|INDEX	|创建具有或不带名称的索引, 如果多个索引同名则创建复合索引|
|UNIQUE_INDEX	|和 INDEX 类似，只不过创建的是唯一索引|
|EMBEDDED	|将结构设置为嵌入|
|EMBEDDED_PREFIX	|设置嵌入结构的前缀|
|-|	忽略此字段|
**关联关系相关的结构体标记（tags）**  

|结构体标记（Tag）|	描述|
|:--|:--|
|MANY2MANY|设置join的表|
|FOREIGNKEY|设置外键|
|ASSOCIATION_FOREIGNKEY|制定关联外键|
|POLYMORPHIC|指定多态类型|
|POLYMORPHIC_VALUE|指定多态值|
|JOINTTABLE_FOREIGNKEY|指定jointable的外键|
|ASSOCIATION_JOINTABLE_FOREIGNKEY|指定jointable的关联外键|
|SAVE_ASSOCIATIONS|是否自动保存关联|
|ASSOCIATION_AUTOUPDATE|是否自动更新关联|
|ASSOCIATION_AUTOCREATE|是否自动创建关联|
|ASSOCIATION_SAVE_REFERENCE|AutoSave关联引用与否|
|PRELOAD|是否自动预加载关联|  

## 1.3. 惯例
### 1.3.1. gorm.Model
gorm.Model是一个基本的GoLang结构，包括以下字段: ID, CreatedAt, UpdatedAt, DeletedAt.  
例如
```
// gorm.Model definition
type Model struct {
  ID        uint `gorm:"primary_key"`
  CreatedAt time.Time
  UpdatedAt time.Time
  DeletedAt *time.Time
}
// Inject fields `ID`, `CreatedAt`, `UpdatedAt`, `DeletedAt` into model `User`
type User struct {
  gorm.Model
  Name string
}
// Declaring model w/o gorm.Model
type User struct {
  ID   int
  Name string
}
```
### 1.3.2. ID作为主键
默认情况下，GORM使用名称为ID的任何字段作为表的主键。  
```
type User struct {
  ID   string // field named `ID` will be used as primary field by default
  Name string
}

// Set field `AnimalID` as primary field
type Animal struct {
  AnimalID int64 `gorm:"primary_key"`
  Name     string
  Age      int64
}
```
### 1.3.3. 多元化的表名（Table Name）  
表名是结构名称的复数形式。  
```
type User struct {} // default table name is `users`

// Set User's table name to be `profiles`
func (User) TableName() string {
  return "profiles"
}

func (u User) TableName() string {
    if u.Role == "admin" {
        return "admin_users"
    } else {
        return "users"
    }
}

// Disable table name's pluralization, if set to true, `User`'s table name will be `user`
db.SingularTable(true)
```
### 1.3.4. 指定表名称
您可以通过定义DefaultTableNameHandler在默认表名称上应用任何规则  
```
gorm.DefaultTableNameHandler = func (db *gorm.DB, defaultTableName string) string  {
    return "prefix_" + defaultTableName;
}
```
### 1.3.5. 下划线分割命名（Snake Case）的列名
列名称将是该字段的名称是较低的蛇案例  
```
type User struct {
  ID        uint      // column name is `id`
  Name      string    // column name is `name`
  Birthday  time.Time // column name is `birthday`
  CreatedAt time.Time // column name is `created_at`
}
// Overriding Column Name
type Animal struct {
    AnimalId    int64     `gorm:"column:beast_id"`         // set column name to `beast_id`
    Birthday    time.Time `gorm:"column:day_of_the_beast"` // set column name to `day_of_the_beast`
    Age         int64     `gorm:"column:age_of_the_beast"` // set column name to `age_of_the_beast`
}
```
### 1.3.6. 时间点（Timestamp）跟踪
**CreatedAt**   
对于具有CreatedAt字段的模型，它将设置为首次创建记录的时间。  
```
db.Create(&user) // will set `CreatedAt` to current time
// To change its value, you could use `Update`
db.Model(&user).Update("CreatedAt", time.Now())
```
**UpdatedAt**  
对于具有UpdatedAt字段的模型，它将设置为更新记录的时间。  
```
db.Save(&user) // will set `UpdatedAt` to current time
db.Model(&user).Update("name", "jinzhu") // will set `UpdatedAt` to current time
```
**DeletedAt**   
对于具有DeletedAt字段的模型，当在该实例上调用Delete时，它不会真正从数据库中删除，而是将其DeletedAt字段设置为当前时间。请参阅软删除 
## 1.4. 连接数据库
```
import _ "github.com/jinzhu/gorm/dialects/mysql"
// import _ "github.com/jinzhu/gorm/dialects/postgres"
// import _ "github.com/jinzhu/gorm/dialects/sqlite"
// import _ "github.com/jinzhu/gorm/dialects/mssql"
```
### 1.4.1. 所支持的数据库
* MySQL
```
import (
  "github.com/jinzhu/gorm"
  _ "github.com/jinzhu/gorm/dialects/mysql"
)

func main() {
  db, err := gorm.Open("mysql", "user:password@/dbname?charset=utf8&parseTime=True&loc=Local")
  defer db.Close()
}
```
* PostgreSQL  
```
import (
  "github.com/jinzhu/gorm"
  _ "github.com/jinzhu/gorm/dialects/postgres"
)

func main() {
  db, err := gorm.Open("postgres", "host=myhost port=myport user=gorm dbname=gorm password=mypassword")
  defer db.Close()
}
```
* Sqlite3
```
import (
  "github.com/jinzhu/gorm"
  _ "github.com/jinzhu/gorm/dialects/sqlite"
)

func main() {
  db, err := gorm.Open("sqlite3", "/tmp/gorm.db")
  defer db.Close()
}
```
* SQL Server
```
import (
  "github.com/jinzhu/gorm"
  _ "github.com/jinzhu/gorm/dialects/mssql"
)

func main() {
  db, err := gorm.Open("mssql", "sqlserver://username:password@localhost:1433?database=dbname")
  defer db.Close()
}
```
### 1.4.2. 不支持的数据库
[支持的数据](http://gorm.io/docs/dialects.html)
# 2. CRUD接口
## 2.1. 创建
### 2.1.1. 创建记录
```
user := User{Name: "Jinzhu", Age: 18, Birthday: time.Now()}
db.NewRecord(user) // => 主键为空返回`true`
db.Create(&user)
db.NewRecord(user) // => 创建`user`后返回`false`
```
### 2.1.2. 默认值
```
type Animal struct {
  ID   int64
  Name string `gorm:"default:'galeone'"`
  Age  int64
}
```
然后插入SQL将排除那些没有值或零值的字段。将记录插入数据库后，gorm将从数据库中加载这些字段的值。  
```
var animal = Animal{Age: 99, Name: ""}
db.Create(&animal)
// INSERT INTO animals("age") values('99');
// SELECT name from animals WHERE ID=111; // the returning primary key is 111
// animal.Name => 'galeone'
```
>> 注意所有具有零值的字段（如0，''，false或其他零值）将不会保存到数据库中，而是使用其默认值。如果要避免这种情况，请考虑使用指针类型或扫描器/值，例如：   
```
// Use pointer value
type User struct {
  gorm.Model
  Name string
  Age  *int `gorm:"default:18"`
}

// Use scanner/valuer
type User struct {
  gorm.Model
  Name string
  Age  sql.NullInt64 `gorm:"default:18"`
}
```
### 2.1.3. 在Hooks中设置字段值
如果要在BeforeCreate挂钩中更新字段的值，可以使用scope.SetColumn，例如：  
```
func (user *User) BeforeCreate(scope *gorm.Scope) error {
  scope.SetColumn("ID", uuid.New())
  return nil
}
```
### 2.1.4. 扩展创建选项
```
// 为Instert语句添加扩展SQL选项
db.Set("gorm:insert_option", "ON CONFLICT").Create(&product)
// INSERT INTO products (name, code) VALUES ("name", "code") ON CONFLICT;
```
## 2.2. 查询
### 2.2.1. 查询
```
//通过主键查询第一条记录
db.First(&user)
//// SELECT * FROM users ORDER BY id LIMIT 1;

// 随机取一条记录
db.Take(&user)
//// SELECT * FROM users LIMIT 1;

// 通过主键查询最后一条记录
db.Last(&user)
//// SELECT * FROM users ORDER BY id DESC LIMIT 1;

// 拿到所有的记录
db.Find(&users)
//// SELECT * FROM users;

// 查询指定的某条记录(只可在主键为整数型时使用)
db.First(&user, 10)
//// SELECT * FROM users WHERE id = 10;
```
### 2.2.2. Where
```
// 获取第一个匹配的记录
db.Where("name = ?", "jinzhu").First(&user)
//// SELECT * FROM users WHERE name = 'jinzhu' limit 1;

// 获取所有匹配的记录
db.Where("name = ?", "jinzhu").Find(&users)
//// SELECT * FROM users WHERE name = 'jinzhu';

// <>
db.Where("name <> ?", "jinzhu").Find(&users)

// IN
db.Where("name in (?)", []string{"jinzhu", "jinzhu 2"}).Find(&users)

// LIKE
db.Where("name LIKE ?", "%jin%").Find(&users)

// AND
db.Where("name = ? AND age >= ?", "jinzhu", "22").Find(&users)

// Time
db.Where("updated_at > ?", lastWeek).Find(&users)

// BETWEEN
db.Where("created_at BETWEEN ? AND ?", lastWeek, today).Find(&users)
```
**Struct & Map** 
```
// Struct
db.Where(&User{Name: "jinzhu", Age: 20}).First(&user)
//// SELECT * FROM users WHERE name = "jinzhu" AND age = 20 LIMIT 1;

// Map
db.Where(map[string]interface{}{"name": "jinzhu", "age": 20}).Find(&users)
//// SELECT * FROM users WHERE name = "jinzhu" AND age = 20;

// Slice of primary keys
db.Where([]int64{20, 21, 22}).Find(&users)
//// SELECT * FROM users WHERE id IN (20, 21, 22);
```
>> 当通过结构体进行查询时，GORM将会只通过非零值字段查询，这意味着如果你的字段值为0，''， false 或者其他 零值时，将不会被用于构建查询条件，例如：  
```
db.Where(&User{Name: "jinzhu", Age: 0}).Find(&users)
//// SELECT * FROM users WHERE name = "jinzhu";  
```
您可以考虑使用指针类型或扫描仪/值来避免这种情况。  
```
// Use pointer value
type User struct {
  gorm.Model
  Name string
  Age  *int
}

// Use scanner/valuer
type User struct {
  gorm.Model
  Name string
  Age  sql.NullInt64
}
```
### 2.2.3. not
```
db.Not("name", "jinzhu").First(&user)
//// SELECT * FROM users WHERE name <> "jinzhu" LIMIT 1;

// Not In
db.Not("name", []string{"jinzhu", "jinzhu 2"}).Find(&users)
//// SELECT * FROM users WHERE name NOT IN ("jinzhu", "jinzhu 2");

// Not In slice of primary keys
db.Not([]int64{1,2,3}).First(&user)
//// SELECT * FROM users WHERE id NOT IN (1,2,3);

db.Not([]int64{}).First(&user)
//// SELECT * FROM users;

// Plain SQL
db.Not("name = ?", "jinzhu").First(&user)
//// SELECT * FROM users WHERE NOT(name = "jinzhu");

// Struct
db.Not(User{Name: "jinzhu"}).First(&user)
//// SELECT * FROM users WHERE name <> "jinzhu";
```
### 2.2.4. Or
```
db.Where("role = ?", "admin").Or("role = ?", "super_admin").Find(&users)
//// SELECT * FROM users WHERE role = 'admin' OR role = 'super_admin';

// Struct
db.Where("name = 'jinzhu'").Or(User{Name: "jinzhu 2"}).Find(&users)
//// SELECT * FROM users WHERE name = 'jinzhu' OR name = 'jinzhu 2';

// Map
db.Where("name = 'jinzhu'").Or(map[string]interface{}{"name": "jinzhu 2"}).Find(&users)
//// SELECT * FROM users WHERE name = 'jinzhu' OR name = 'jinzhu 2'; 
```
### 2.2.5. 内联条件
TODO:  
## 2.3. 更新
### 2.3.1. 更新所有字段
Save会更新所有字段，即使你没有赋值  
```
db.First(&user)
user.Name = "jinzhu 2"
user.Age = 100
db.Save(&user)
//// UPDATE users SET name='jinzhu 2', age=100, birthday='2016-01-01', updated_at = '2013-11-17 21:34:10' WHERE id=111;
```
### 2.3.2. 更新修改字段
如果你只希望更新指定字段，可以使用Update或者Updates  
```
// Update single attribute if it is changed
db.Model(&user).Update("name", "hello")
//// UPDATE users SET name='hello', updated_at='2013-11-17 21:34:10' WHERE id=111;

// Update single attribute with combined conditions
db.Model(&user).Where("active = ?", true).Update("name", "hello")
//// UPDATE users SET name='hello', updated_at='2013-11-17 21:34:10' WHERE id=111 AND active=true;

// Update multiple attributes with `map`, will only update those changed fields
db.Model(&user).Updates(map[string]interface{}{"name": "hello", "age": 18, "actived": false})
//// UPDATE users SET name='hello', age=18, actived=false, updated_at='2013-11-17 21:34:10' WHERE id=111;

// Update multiple attributes with `struct`, will only update those changed & non blank fields
db.Model(&user).Updates(User{Name: "hello", Age: 18})
//// UPDATE users SET name='hello', age=18, updated_at = '2013-11-17 21:34:10' WHERE id = 111;

// WARNING when update with struct, GORM will only update those fields that with non blank value
// For below Update, nothing will be updated as "", 0, false are blank values of their types
db.Model(&user).Updates(User{Name: "", Age: 0, Actived: false})
```
### 2.3.3. 更新选择的字段
如果您只想在更新时更新或忽略某些字段，可以使用Select，Omit  
```
db.Model(&user).Select("name").Updates(map[string]interface{}{"name": "hello", "age": 18, "actived": false})
//// UPDATE users SET name='hello', updated_at='2013-11-17 21:34:10' WHERE id=111;

db.Model(&user).Omit("name").Updates(map[string]interface{}{"name": "hello", "age": 18, "actived": false})
//// UPDATE users SET age=18, actived=false, updated_at='2013-11-17 21:34:10' WHERE id=111;
```
### 2.3.4. 更新的Hooks
上面的更新操作将执行模型的BeforeUpdate，AfterUpdate方法，更新其UpdatedAt时间戳，更新时保存其关联，如果您不想调用它们，可以使用UpdateColumn，UpdateColumns   
```
// Update single attribute, similar with `Update`
db.Model(&user).UpdateColumn("name", "hello")
//// UPDATE users SET name='hello' WHERE id = 111;

// Update multiple attributes, similar with `Updates`
db.Model(&user).UpdateColumns(User{Name: "hello", Age: 18})
//// UPDATE users SET name='hello', age=18 WHERE id = 111;
```
### 2.3.5. 批量更新
批量更新时，挂钩不会运行  
```
db.Table("users").Where("id IN (?)", []int{10, 11}).Updates(map[string]interface{}{"name": "hello", "age": 18})
//// UPDATE users SET name='hello', age=18 WHERE id IN (10, 11);

// Update with struct only works with none zero values, or use map[string]interface{}
db.Model(User{}).Updates(User{Name: "hello", Age: 18})
//// UPDATE users SET name='hello', age=18;

// Get updated records count with `RowsAffected`
db.Model(User{}).Updates(User{Name: "hello", Age: 18}).RowsAffected
```
### 2.3.6. 使用SQL Expression更新  
```
DB.Model(&product).Update("price", gorm.Expr("price * ? + ?", 2, 100))
//// UPDATE "products" SET "price" = price * '2' + '100', "updated_at" = '2013-11-17 21:34:10' WHERE "id" = '2';

DB.Model(&product).Updates(map[string]interface{}{"price": gorm.Expr("price * ? + ?", 2, 100)})
//// UPDATE "products" SET "price" = price * '2' + '100', "updated_at" = '2013-11-17 21:34:10' WHERE "id" = '2';

DB.Model(&product).UpdateColumn("quantity", gorm.Expr("quantity - ?", 1))
//// UPDATE "products" SET "quantity" = quantity - 1 WHERE "id" = '2';

DB.Model(&product).Where("quantity > 1").UpdateColumn("quantity", gorm.Expr("quantity - ?", 1))
//// UPDATE "products" SET "quantity" = quantity - 1 WHERE "id" = '2' AND quantity > 1;
```
### 2.3.7. Hooks中修改值
如果要使用BeforeUpdate，BeforeSave更改挂钩中的更新值，可以使用scope.SetColumn，例如：  
```
func (user *User) BeforeSave(scope *gorm.Scope) (err error) {
  if pw, err := bcrypt.GenerateFromPassword(user.Password, 0); err == nil {
    scope.SetColumn("EncryptedPassword", pw)
  }
}
```
### 2.3.8. 额外更新选项  
```
// Add extra SQL option for updating SQL
db.Model(&user).Set("gorm:update_option", "OPTION (OPTIMIZE FOR UNKNOWN)").Update("name", "hello")
//// UPDATE users SET name='hello', updated_at = '2013-11-17 21:34:10' WHERE id=111 OPTION (OPTIMIZE FOR UNKNOWN);
```
## 2.4. 删除
### 2.4.1. 删除记录 
```
// Delete an existing record
db.Delete(&email)
//// DELETE from emails where id=10;

// Add extra SQL option for deleting SQL
db.Set("gorm:delete_option", "OPTION (OPTIMIZE FOR UNKNOWN)").Delete(&email)
//// DELETE from emails where id=10 OPTION (OPTIMIZE FOR UNKNOWN);
```
### 2.4.2. 批量删除
```
db.Where("email LIKE ?", "%jinzhu%").Delete(Email{})
//// DELETE from emails where email LIKE "%jinzhu%";
db.Delete(Email{}, "email LIKE ?", "%jinzhu%")
//// DELETE from emails where email LIKE "%jinzhu%";
```
### 2.4.3. 软删除
如果模型有DeletedAt字段，它将自动获得软删除功能！调用Delete时，不会从数据库中永久删除记录;相反，DeletedAt的值将设置为当前时间  
```
db.Delete(&user)
//// UPDATE users SET deleted_at="2013-10-29 10:23" WHERE id = 111;

// Batch Delete
db.Where("age = ?", 20).Delete(&User{})
//// UPDATE users SET deleted_at="2013-10-29 10:23" WHERE age = 20;

// Soft deleted records will be ignored when query them
db.Where("age = 20").Find(&user)
//// SELECT * FROM users WHERE age = 20 AND deleted_at IS NULL;

// Find soft deleted records with Unscoped
db.Unscoped().Where("age = 20").Find(&users)
//// SELECT * FROM users WHERE age = 20;
```
### 2.4.4. 永久删除记录
```
// Delete record permanently with Unscoped
db.Unscoped().Delete(&order)
//// DELETE FROM orders WHERE id=10;
```