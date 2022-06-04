#pragma once
#include "../GeneratedFiles/ui_CreateComponent.h"
#include "qdialog.h"
#include <qobject.h>
#include <qaxobject.h>

#include <ifcpp/model/IfcPPObject.h>
#include <ifcpp/model/IfcPPModel.h>

#include "ViewController.h"

class ComponentOpSlots;
class IfcPlusPlusSystem;


//���ȼƻ� 
class ComponentOpDlg : public QDialog
{
	Q_OBJECT
public:
	ComponentOpDlg(IfcPlusPlusSystem* sys, QWidget *parent);	
	
public:
	
	//�Զ���Ի��� �Ա�򿪵ı������	
	Ui::CreateComponent* m_CreateComponent_dialog;
	
protected:
	IfcPlusPlusSystem*	m_system;	
	ComponentOpSlots*  m_ComponentOpSlot;
	
	
private:
	
	public slots :

	void slotAddComponent();
	void slotImportComponentData();
	void slotNameChanged(int);
	void slotcloseDlg();

signals:
	void AddComponent(int, int);
};