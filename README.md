
作为正在进行中的课程大作业，此项目的README不知所云，待学期结束之后补上正式的README。
=======
# lightDB
A very weak light DB for oop.<br/>

测试sql语句在test.txt中。<br/>
# TODOLIST
* 尚未通过sql语句实现的功能：exit,show,create
* and和or的顺序（现在一律当成and，可能需要用二叉树？）
* load_database
* write_database
* 一些尚未用typedef优雅化的指针
* 注释
* 。。。优化？


## 重要：Database中有一处错误
erase的方法不对，有空就改。<br/>

## 重要：不安全的拷贝函数strcpy
先这么写着，以后统一改为strcpy_s<br/>

Database需要实现的的主要功能
在core文件夹下新建一个database.h和database.cpp文件<br/>
建立class Database<br/>
createTable<br/>
dropTable<br/>
getTable<br/>
序列化和反序列化<br/>
快照<br/>
其他你认为重要的功能...<br/>
**不要修改别的文件！！！！！**<br/>


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
 6、将这个Action指针作为参数，执行execute函数<br/>
 7、在execute中通过action.type访问命令类型，如'select'。构造一个string->function ptr的map，将'select'映射到select函数，并传入action作为参数；返回select(action.table,action.data)。<br/>
 8、select(action.table,action.data)相当于table.search(data)，高层调用底层<br/>
 ### 总结一下：
 {}表示变量类型<br/>
 input {string} str<br/>
 {Engine(调度类，全局唯一)}engine.run()<br/>
 split str by 'where'<br/>
 {Action*} action=parse(str[0])<br/>
 for colname,symbol,value in str[1]:<br/>
 &nbsp;action.addCondition(colname,{Case(判断类)}(symbol,Data(value)))<br/>
 if action.type=='select':</br>
 &nbsp;vector<{Record}> result=actionMap{action.type}(action)(记住actionMap把字符串映射到函数指针)<br/>
     如果函数指针用不了，就写一个函数类，即重载（）的类<br/>
 else:<br/>
     actionMap[action.type](action)   增删改都不需要返回值<br/>
 actionMap['update']=this->update<br/>
 update(action):<br/>
     action.table.update(action.data,action.conditions><br/>
 [Table].update(data,conditions):<br/>(记住conditions是一对对[列名：Case]，参见上文的addCondition函数)<br/>
     match_idx=parse_conditions(conditions)<br/>
     this->getcolumn(data.name)->modify(match_idx,data.data)<br/>
     data可以是一对对[列名：vector<Data*>]，也可以就是一个vector<Data*>，然后再update中再传一个参数vector<string> names<br/>
  
  parse_conditions(conditions):<br/>
      if conditions.size()=0:return [0,rows-1] <br/>
      for name in conditions.names:<br/>
          for idx in [0,rows-1]:<br/>
              if case(this->getcolumn(name)->getdata(idx))==True:<br/>
                  match_idx.append(idx)<br/>
       return match_idx <br/>
       
  Case对象：<br/>
       operator()(data) return symbol_map[this->symbol](data,this->condition)<br/>
  symbol_map把一个字符串映射成一个返回true or flase的函数<br/>
  例如：symbol_map['=']=equal
  bool equal(data,condition){return data==condition;}<br/>
  this->symbol是一个操作符，例如>,=<br/>
  data:{Data}<br/>
  this->condition:{Data}<br/>
 详见addCondition中的Case对象构造过程。<br/>
 如果函数指针不会写的话，就if-else或者函数类<br/>
 
 
 
 
