// #include<iostream>
// using namespace std;
// #include <vector>
// #include <string>
// #include <map>
// #include <ctime>
//
// /*
// - 公司今天招聘了10个员工（ABCDEFGHIJ），10名员工进入公司之后，需要指派员工在那个部门工作
// - 员工信息有: 姓名  工资组成；部门分为：策划、美术、研发
// - 随机给10名员工分配部门和工资
// - 通过multimap进行信息的插入  key(部门编号) value(员工)
// - 分部门显示员工信息
// */
//
// #define CEHUA  0
// #define MEISHU 1
// #define YANFA  2
//
// class Worker
// {
// public:
// 	string m_Name;
// 	int m_Salary;
// };
//
// void createWorker(vector<Worker>&v)
// {
// 	string nameSeed = "ABCDEFGHIJ";
// 	for (int i = 0; i < 10; i++)
// 	{
// 		Worker worker;
// 		worker.m_Name =  "员工";
// 		worker.m_Name += nameSeed[i];
//
// 		worker.m_Salary = rand() % 10000 + 10000; // 10000 ~ 19999
// 		//将员工放入到容器中
// 		v.push_back(worker);
// 	}
// }
//
// //员工分组
// void setGroup(vector<Worker>&v,multimap<int,Worker>&m)
// {
// 	for (vector<Worker>::iterator it = v.begin(); it != v.end(); it++)
// 	{
// 		//产生随机部门编号
// 		int deptId = rand() % 3; // 0 1 2
//
// 		//将员工插入到分组中
// 		//key部门编号，value具体员工
// 		m.insert(make_pair(deptId, *it));
// 	}
// }
//
// void showWorkerByGourp(multimap<int,Worker>&m)
// {
// 	// 0  A  B  C   1  D  E   2  F G ...
// 	cout << "策划部门：" << endl;
//
// 	multimap<int,Worker>::iterator pos = m.find(CEHUA);
// 	int count = m.count(CEHUA); // 统计具体人数
// 	int index = 0;
// 	for (; pos != m.end() && index < count; pos++ , index++)
// 	{
// 		cout << "姓名： " << pos->second.m_Name << " 工资： " << pos->second.m_Salary << endl;
// 	}
//
// 	cout << "----------------------" << endl;
// 	cout << "美术部门： " << endl;
// 	pos = m.find(MEISHU);
// 	count = m.count(MEISHU); // 统计具体人数
// 	index = 0;
// 	for (; pos != m.end() && index < count; pos++, index++)
// 	{
// 		cout << "姓名： " << pos->second.m_Name << " 工资： " << pos->second.m_Salary << endl;
// 	}
//
// 	cout << "----------------------" << endl;
// 	cout << "研发部门： " << endl;
// 	pos = m.find(YANFA);
// 	count = m.count(YANFA); // 统计具体人数
// 	index = 0;
// 	for (; pos != m.end() && index < count; pos++, index++)
// 	{
// 		cout << "姓名： " << pos->second.m_Name << " 工资： " << pos->second.m_Salary << endl;
// 	}
//
// }
//
// int main() {
//
// 	srand((unsigned int)time(NULL));
//
// 	//1、创建员工
// 	vector<Worker>vWorker;
// 	createWorker(vWorker);
//
// 	//2、员工分组
// 	multimap<int, Worker>mWorker;
// 	setGroup(vWorker, mWorker);
//
//
// 	//3、分组显示员工
// 	showWorkerByGourp(mWorker);
//
// 	////测试
// 	//for (vector<Worker>::iterator it = vWorker.begin(); it != vWorker.end(); it++)
// 	//{
// 	//	cout << "姓名： " << it->m_Name << " 工资： " << it->m_Salary << endl;
// 	//}
//
// 	system("pause");
//
// 	return 0;
// }





//----------Deepseek优化






#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <ctime>
#include <algorithm>
#include <iomanip>

using namespace std;

// 部门枚举
enum class Department : int {
    CEHUA = 0,
    MEISHU = 1,
    YANFA = 2,
    COUNT = 3
};

// 部门名称映射
const map<Department, string> DEPT_NAMES = {
    {Department::CEHUA, "策划部门"},
    {Department::MEISHU, "美术部门"},
    {Department::YANFA, "研发部门"}
};

class Worker {
public:
    string m_Name;
    int m_Salary;

    Worker() = default;
    Worker(const string& name, int salary) : m_Name(name), m_Salary(salary) {}

    void display() const {
        cout << "姓名： " << m_Name << " 工资： " << m_Salary;
    }
};

// 创建员工
vector<Worker> createWorkers(int count = 10) {
    vector<Worker> workers;
    workers.reserve(count);

    const string nameSeed = "ABCDEFGHIJ";
    for (int i = 0; i < count && i < static_cast<int>(nameSeed.length()); ++i) {
        string name = "员工";
        name += nameSeed[i];
        int salary = rand() % 10000 + 10000; // 10000 ~ 19999
        workers.emplace_back(name, salary);
    }
    return workers;
}

// 员工分组
multimap<Department, Worker> groupWorkers(const vector<Worker>& workers) {
    multimap<Department, Worker> grouped;

    for (const auto& worker : workers) {
        Department dept = static_cast<Department>(rand() % static_cast<int>(Department::COUNT));
        grouped.insert({dept, worker});
    }
    return grouped;
}

// 显示指定部门员工
void displayDepartment(const multimap<Department, Worker>& grouped, Department dept) {
    auto it = DEPT_NAMES.find(dept);
    if (it != DEPT_NAMES.end()) {
        cout << it->second << "：" << endl;
    }

    auto range = grouped.equal_range(dept);
    int count = distance(range.first, range.second);

    if (count == 0) {
        cout << "  （暂无员工）" << endl;
    } else {
        int index = 0;
        for (auto it = range.first; it != range.second; ++it, ++index) {
            cout << "  ";
            it->second.display();
            cout << endl;
        }
        cout << "  本部门共 " << count << " 人" << endl;
    }
    cout << "----------------------" << endl;
}

// 显示所有部门员工
void displayAllDepartments(const multimap<Department, Worker>& grouped) {
    for (int i = 0; i < static_cast<int>(Department::COUNT); ++i) {
        Department dept = static_cast<Department>(i);
        displayDepartment(grouped, dept);
    }
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    // 1、创建员工
    auto workers = createWorkers(10);

    // 2、员工分组
    auto grouped = groupWorkers(workers);

    // 3、分组显示员工
    displayAllDepartments(grouped);

    // 可选：显示所有员工原始列表
    // cout << "\n所有员工列表：" << endl;
    // for (const auto& worker : workers) {
    //     worker.display();
    //     cout << endl;
    // }

    system("pause");
    return 0;
}