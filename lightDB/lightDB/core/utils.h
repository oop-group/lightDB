#pragma once

/*
	一些常用的功能类和函数
*/

/*
	字段支持的数据类型集合
*/
enum class ColumnType {
	INT,
	DOUBLE,
	CHAR,
};

/*
	字段约束
*/
enum class ColumnConstraint {
	NOT_NULL,	//非空约束
	YES_NULL,		//空约束
	UNIQUE,		//唯一约束
	INCREMENT,	//自增约束
	PRIMARY,	//主键约束
};


