#pragma once
#ifndef SQLBAG_H
#define SQLBAG_H

#include"sqlite3.h"
#include<string>
#pragma comment(lib,"sqlite3.lib")

//把sqlite要用的插入删除操作封装一下
typedef int (*sqlite3_callback)(
	void*,//sqlite_exec的第四个参数
	int, //这一行数据的规模，也就是列数
	char**,//一行字符串，代表着 每一个的数字
	char**//代表着列名
	);
class SqliteExecution
{ 
public:
	//目的是什么？是返回一个已经初始化的sqlite3的实例
	static SqliteExecution *Instance() {
		static SqliteExecution ins;
		return &ins;
	}
	void Init(std::string file) {//在init的时候已经初始化了db了，所以直接调用就行了。
		int rc = sqlite3_open(file.data(),&db);
		if (rc) {
			fprintf(stderr, "error:cannot open database:%s\n", sqlite3_errmsg(db));
			exit(0);
		}
		else {
			fprintf(stderr, "Open successfully!\n");
		}
	}
	void closeDb() {
		sqlite3_close(db);
	}
	void insertDb(std::string command) {
		char* errmsg = 0;
		int rc = sqlite3_exec(db,command.data(),0,0,&errmsg);//第三个函数可以不用传 insert和delete不用给
		if (rc != SQLITE_OK) {
			fprintf(stderr, "Insert failed!:%s\n", errmsg);
			sqlite3_free(errmsg);
		}
		else {
			fprintf(stdout, "Insert Successfully!\n");
		}
	}
	void SelectDb(std::string command,int(*callback)(void*, int, char**, char**), void*tmp) {
		char* errmsg = 0;
		int rc = sqlite3_exec(db, command.data(), callback, tmp, &errmsg);
		if (rc != SQLITE_OK) {
			fprintf(stderr,"SELECT Failed!:%s\n", errmsg);
			sqlite3_free(errmsg);
		}
		else {
			fprintf(stdout, "SELECT Successfully!\n");
		}
	}
	SqliteExecution() {};
	~SqliteExecution() { closeDb(); };
private:
	sqlite3* db;
};

#endif // !SQLBAG_H