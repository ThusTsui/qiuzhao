#include<iostream>
#include<vector>
#include<ctime>
#include<string>
#include<map>

using namespace std;

//公司今天招聘了10个员工（ABCDEFGHIJ），10名员工进入公司之后，需要指派员工在那个部门工作
//员工信息有: 姓名 工资组成；部门分为：策划、美术、研发
//随机给10名员工分配部门和工资
//通过multimap进行信息的插入 key(部门编号) value(员工)
//分部门显示员工信息

class worker{
	
	public:
		string m_name;
		int m_salary;
};

void createworker(vector<worker>&v){
	
	string nameSeed="ABCDEFGHIJ";
	for(int i =0;i<10;i++){
		
		worker worker1;
		worker1.m_name="员工";
        worker1.m_name+=nameSeed[i];

        worker1.m_salary=rand()%10000 +10000;
        v.push_back(worker1);
	}
}

//员工分组
void setGroup(vector<worker>&v,multimap<int,worker>&m){
    for(vector<worker>::iterator it = v.begin();it!=v.end();it++){
        //产生随机部门编号
        int deptID=rand()%3;
        m.insert(make_pair(deptID,*it));
    }

}
void showWorkerByGroup(multimap<int,worker>&m){
    cout<<"策划部门："<<endl;
    multimap<int,worker>::iterator pos = m.find(0);
    int s = m.count(0);//统计策划部门具体人数
    int index = 0;
    for(;pos!=m.end() && index<s;pos++,index++){
        cout<<"姓名："<<pos->second.m_name<<" 工资："<<pos->second.m_salary<<endl;
    }
}


int main(){
	//创建员工
	vector<worker> vworker;
	createworker(vworker);
	
    // //测试
    // for(vector<worker>::iterator it=vworker.begin();it!=vworker.end();it++){
    //     cout<<"姓名："<<it->m_name<<" 工资："<<it->m_salary<<endl;
    // }

    //员工分组
    multimap<int,worker> mworker;
    setGroup(vworker,mworker);

    //显示员工分组
    showWorkerByGroup(mworker);
	
	return 0;
}