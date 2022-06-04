#pragma once
#ifndef SQLBAG_H
#define SQLBAG_H

#include"sqlite3.h"
#include<string>
#pragma comment(lib,"sqlite3.lib")

//��sqliteҪ�õĲ���ɾ��������װһ��
typedef int (*sqlite3_callback)(
	void*,//sqlite_exec�ĵ��ĸ�����
	int, //��һ�����ݵĹ�ģ��Ҳ��������
	char**,//һ���ַ����������� ÿһ��������
	char**//����������
	);
class SqliteExecution
{ 
public:
	//Ŀ����ʲô���Ƿ���һ���Ѿ���ʼ����sqlite3��ʵ��
	static SqliteExecution *Instance() {
		static SqliteExecution ins;
		return &ins;
	}
	void Init(std::string file) {//��init��ʱ���Ѿ���ʼ����db�ˣ�����ֱ�ӵ��þ����ˡ�
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
		int rc = sqlite3_exec(db,command.data(),0,0,&errmsg);//�������������Բ��ô� insert��delete���ø�
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