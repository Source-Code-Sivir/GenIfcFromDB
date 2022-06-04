#pragma once


#include <map>
//#include "cmd/Command.h"
#include "ifcpp/writer/IfcPPWriterSTEP.h"
#include "ifcpp/IFC4/include/IfcRelAggregates.h"
#include "ifcpp/IFC4/include/IfcSite.h"
#include "ifcpp/IFC4/include/IfcObjectDefinition.h"
#include "ifcpp/IFC4/include/IfcUnitEnum.h"
#include "ifcpp/IFC4/include/IfcAbsorbedDoseMeasure.h"
#include "ifcpp\IFC4\include\IfcDerivedMeasureValue.h"
#include "ifcpp\IFC4\include\IfcValue.h"
#include "ifcpp/IFC4/include/IfcUnit.h"
#include "ifcpp/model/IfcPPAttributeObject.h"
#include "ifcpp/model/shared_ptr.h"
#include <fstream>
#include <sstream>

#include "src\gui\bar.h"

class IfcPlusPlusSystem;
class MainWindow;
class IfcPPModel;

class ComponentOpSlots : public QObject
{
	Q_OBJECT
public:
	ComponentOpSlots(IfcPlusPlusSystem* sys);
	~ComponentOpSlots();	
	
	//��ʼ��ifc���ļ�ͷ
	void init_ifcfile(shared_ptr<IfcPPModel> &model, std::stringstream & stream, std::string fileName);
	//����model�еĹ����������stream��
	void direct_model(shared_ptr<IfcPPModel> &model, std::stringstream& stream);
	//��model�����ifc�ļ���
	void single_model(shared_ptr<IfcPPModel> &model);

	std::string ws2s(const std::wstring& ws);

	void InitIfcModel(int type_unit);

	void AddColumn(double length, double width, double height, double locate_x, double locate_y, double locate_z, double zdirect_x, double zdirect_y, double zdirect_z, double xdirect_x, double xdirect_y, double xdirect_z);
	void AddBeam(double XDim, double YDim, double Depth, double locate_x, double locate_y, double locate_z, double zdirect_x, double zdirect_y, double zdirect_z, double xdirect_x, double xdirect_y, double xdirect_z);
	void Addbar(bar& Reinforcingbar);
	void AddComponent_Bar(bar& Reinforcingbar);
	std::string paramdata[12];
private:	
	IfcPlusPlusSystem* m_system;
	std::fstream outfile;
	shared_ptr<IfcPPModel> m_model;
	bool flag_initModel;

public slots:	
    void slotOutputComponentIfc();
	void slotAddComponent(int type, int shape);  //���β�����AddColumn�Ⱥ���
	//void slotAddRebar(bar& Reinforcingbar,int cnt); //��һ������Ϊ����ĸֽ���󣬵ڶ�������Ϊ�ֽ����߶ε���Ŀ



	
};