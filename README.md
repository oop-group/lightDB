
作为正在进行中的课程大作业，此项目的README不知所云，待学期结束之后补上正式的README。
=======
# lightDB
A very weak light DB for oop.

4.5 做了个字段类，顺便写了一个没什么用的单元测试。
接下来打算做数据表类：一堆字段类的组合。
错误处理什么的都没做，假设使用者输入的都是非恶意的数据。<br>
4.6 把字段类从模板类改成了普通的继承方式；添加了数据表类，能够添加字段和search字段<br/>
4.7用union实现了一个可以接受任意数据类型的Data类，作为数据表中的一格；完善了数据表的增删查改功能。目前还没有任何的异常处理代码。<br/>

问题：<br/>
1、search返回的结构过于复杂，可以包装成一个优雅的Record类，表示一行；vector<Record>表示一次查询返回的所有的记录<br/>
2、约束：这可得好好想想<br/>
3、专门建一个文件，将指针用typedef的方式美化，不要满屏*乱飞<br/>
4、构造函数里最好不要出现vector，可以用传入任意数量参数的构造函数来初始化Column,Table等类<br/>
5、用Record类表示一条记录（一行）<br/>
6、调度模块是否一次性读入全部以文件储存的数据库的具体内容，而不仅仅是数据库名称与路径的映射，读入的时机，数据库从内存保存到文件的时机<br/>
7、可以考虑的拓展：数据库修改后即时保存（设置选项人为开关此项功能）/周期性保存，保留备份上次文件（以.bak的形式），防止数据丢失提高可靠性<br/>
8、鉴于主键的特殊性，Table应该知道自己哪个列是主键<br/>
  
  
 ## 如何解析SQL语句：
 构造一个action_map:string->函数指针<br/>
 Action类：根据select xxx from xxx这样的语句构造；根据命令的种类分支出不同的子类(SelectAction等）<br/>
 string：命令名称，如'select','update'<br/>
 Case对象：根据不同的操作符（如>,=）衍生出不同的子类<br/>
 函数指针：select，构造一个Action对象并返回其指针<br/>
 1、读入字符串statement<br/>
 2、按按照where将语句分成2份，前一份为statement[0],后一份为statement[1]<br/>
 3、前一半为select id,name from stu，按照空格分开得到数组statement0<br/>
 4、function=action_map['select'] action=function(statement0) 一个SelectAction类的指针<br/>
 5、根据statement[1]构造一个判断类对象Case,将其作为Action的成员<br/>
 6、将这个Action指针作为参数，执行execute函数，解析这个对象<br/>
