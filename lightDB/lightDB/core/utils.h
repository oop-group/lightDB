#pragma once

/*
	һЩ���õĹ�����ͺ���
*/

/*
	�ֶ�֧�ֵ��������ͼ���
*/
enum class ColumnType {
	INT,
	DOUBLE,
	CHAR,
};

/*
	�ֶ�Լ��
*/
enum class ColumnConstraint {
	NOT_NULL,	//�ǿ�Լ��
	YES_NULL,		//��Լ��
	UNIQUE,		//ΨһԼ��
	INCREMENT,	//����Լ��
	PRIMARY,	//����Լ��
};


