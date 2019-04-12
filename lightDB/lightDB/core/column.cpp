#include "column.h"

Column::Column(const ColumnType& t, const vector<ColumnConstraint>& cs)
{
	for (int j = 0, len = cs.size(); j < len; j++) constraints.push_back(cs[j]);
	type = t;
}
/*
    Column编码方式（按byte）
    [0]:bit7为终止符;bit6和bit5合起来存储类型,00 01 10分别代表int double char*
    bit0/1/2/3/4的1/0分别为有/无非空约束/空约束/唯一约束/自增约束/主键约束
    [1-4]存储字段的length
    之后length个data循序排列，每个的数据域前四个字节是这个data编码后的长度li，后面接着li个字节是这个data的序列化数据，需要反序列化
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
    pColumn column=new Column(t,v);
    int valueNum=*s_int::Deserialize(content.substr(1,4));
    int point=5;
    for(int i=0;i<valueNum;i++){
        int valueLength=*s_int::Deserialize(content.substr(point,4));
        column->add(Data::Deserialize(content.substr(point+4,valueLength)));
        point+=4+valueLength;
    }
    return column;
}
