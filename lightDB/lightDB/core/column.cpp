#include "column.h"

Column::Column(ColumnType&& t, vector<ColumnConstraint>&& cs)
{
	constraints = cs;
	type = t;
	defaultValue = nullptr;
	extra = "";
}
/*
    Column���뷽ʽ����byte��
    [0]:bit7Ϊ��ֹ��;bit6��bit5�������洢����,00 01 10�ֱ����int double char*
    bit0/1/2/3/4��1/0�ֱ�Ϊ��/�޷ǿ�Լ��/��Լ��/ΨһԼ��/����Լ��/����Լ��
    [1-4]�洢�ֶε�length
    ֮��length��dataѭ�����У�ÿ����������ǰ�ĸ��ֽ������data�����ĳ���li���������li���ֽ������data�����л����ݣ���Ҫ�����л�
*/
string Column::Serialize(){
    string s;
    char c0;
    bool b[5];
    for(int i=0;i<5;i++)b[i]=0;
    for(ColumnConstraint constraint: constraints)b[static_cast<int>(constraint)]=1;
    c0=static_cast<int>(type)<<5;
    for(int i=0;i<5;i++)c0+=(b[i]<<i);
    s+=c0;
    s_int valuesLength(values.size());
    s+=valuesLength.Serialize();
    for(int i=0;i<values.size();i++){
        string ss=values[i]->Serialize();
        s_int iLength(ss.size());
        s+=iLength.Serialize();
        s+=ss;
    }
    return s;
}
pColumn Column::Deserialize(const string& content){
    bool b[8];
    for(int i=0;i<8;i++)b[i]=(content[0]>>i)%2;
    int iType=b[6]*2+b[5];
    ColumnType t=ColumnType(iType);
    vector<ColumnConstraint> v;
    for(int i=0;i<5;i++){
        if(b[i])v.push_back(ColumnConstraint(i));
    }
    pColumn column=new Column(std::move(t),std::move(v));
    int valueNum=*s_int::Deserialize(content.substr(1,4));
    int point=5;
    for(int i=0;i<valueNum;i++){
        int valueLength=*s_int::Deserialize(content.substr(point,4));
        column->add(Data::Deserialize(content.substr(point+4,valueLength)));
        point+=4+valueLength;
    }
    return column;
}
