#include "ComponentOpDlg.h"
#include "qdialog.h"
#include "ComponentOpSlots.h"
#include "IfcPlusPlusSystem.h"

#include <qmessagebox.h>
#include <memory>
#include <fstream>

#pragma execution_character_set("utf-8")

extern std::string ws2s(const std::wstring& ws);
ComponentOpDlg::ComponentOpDlg(IfcPlusPlusSystem* sys, QWidget *parent) : QDialog(parent), m_system(sys)
{	
	
	m_CreateComponent_dialog = new Ui::CreateComponent();

	m_CreateComponent_dialog->setupUi(this);
	m_ComponentOpSlot = new ComponentOpSlots(m_system);

	connect(m_CreateComponent_dialog->pushButton_AddComponent, SIGNAL(clicked()), this, SLOT(slotAddComponent()));	
	connect(m_CreateComponent_dialog->pushButton_ImportParams, SIGNAL(clicked()), this, SLOT(slotImportComponentData()));
	connect(m_CreateComponent_dialog->pushButton_OutputIFC, SIGNAL(clicked()), m_ComponentOpSlot, SLOT(slotOutputComponentIfc()));
	connect(m_CreateComponent_dialog->comboBox_component_name, SIGNAL(currentIndexChanged(int)), this, SLOT(slotNameChanged(int)));
	connect(m_CreateComponent_dialog->pushButton_Close, SIGNAL(clicked()), this, SLOT(slotcloseDlg()));

	
	
	connect(this, SIGNAL(AddComponent(int, int)), m_ComponentOpSlot, SLOT(slotAddComponent(int, int)));
	
}
void ComponentOpDlg::slotcloseDlg()
{
	this->close();
}
void ComponentOpDlg::slotNameChanged(int index)
{
	if (index == 0)
	{
		m_CreateComponent_dialog->label_XDim->setText("Length");
		m_CreateComponent_dialog->label_YDim->setText("Width");
		m_CreateComponent_dialog->label_Depth->setText("Height");

	}
	else if (index == 1)
	{
		m_CreateComponent_dialog->label_XDim->setText("Height");
		m_CreateComponent_dialog->label_YDim->setText("Width");
		m_CreateComponent_dialog->label_Depth->setText("Length");
	}
	//m_CreateComponent_dialog->comboBox_component_name->itemText(index)
}
void ComponentOpDlg::slotAddComponent()
{
	std::string param[12] = { "" };	
	param[0] = m_CreateComponent_dialog->lineEdit_length->text().toStdString();
	param[1] = m_CreateComponent_dialog->lineEdit_width->text().toStdString();
	param[2] = m_CreateComponent_dialog->lineEdit_height->text().toStdString();
	param[3] = m_CreateComponent_dialog->lineEdit_LocateX->text().toStdString();
	param[4] = m_CreateComponent_dialog->lineEdit_locateY->text().toStdString();
	param[5] = m_CreateComponent_dialog->lineEdit_locateZ->text().toStdString();
	param[6] = m_CreateComponent_dialog->lineEdit_ZDirect_X->text().toStdString();
	param[7] = m_CreateComponent_dialog->lineEdit_ZDirect_Y->text().toStdString();
	param[8] = m_CreateComponent_dialog->lineEdit_ZDirect_Z->text().toStdString();
	param[9] = m_CreateComponent_dialog->lineEdit_XDirect_X->text().toStdString();
	param[10] = m_CreateComponent_dialog->lineEdit_XDirect_Y->text().toStdString();
	param[11] = m_CreateComponent_dialog->lineEdit_XDirect_Z->text().toStdString();		
	
	if (m_CreateComponent_dialog->comboBox_component_name->currentIndex() == -1)
	{
		QMessageBox::about(NULL, tr("提示"), tr("请选择构件类型！"));
		return;
	}
	else if (m_CreateComponent_dialog->comboBox_component_type->currentIndex() == -1)
	{
		QMessageBox::about(NULL, tr("提示"), tr("请选择构件形状！"));	
		return;
	}

	for (int i = 0; i < 12; i++)
	{
		if (param[i] == "")
		{
			QMessageBox::about(NULL, tr("提示"), tr("请设置构件属性参数！"));
			return;
		}
	}
	for (int i = 0; i < 12; i++)
	{
		//qDebug("%f", std::stof(param[i]));
		m_ComponentOpSlot->paramdata[i] = param[i];
		//qDebug("%f", std::stof(m_ComponentOpSlot->paramdata[i]));
	}
	
	emit(AddComponent(m_CreateComponent_dialog->comboBox_component_name->currentIndex(), m_CreateComponent_dialog->comboBox_component_type->currentIndex()));
}

void ComponentOpDlg::slotImportComponentData()
{
	QSettings settings(QSettings::UserScope, QLatin1String("NMBIM"));

	QString default_dir = settings.value("defaultDir").toString();	
	QString selected_file = QFileDialog::getOpenFileName(NULL, tr("Choose file"),
		default_dir, tr("csv file(*.csv)"));	

	QFile File(selected_file);
	if (!File.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::about(NULL, tr("提示"), tr("文件读取失败！"));
		return ;
	}	

	QTextStream in(&File);
	in.setCodec("GBK");   // 或者设置为in.setCodec("UTF-8");
	QString fileLine;
	std::string param[12] = { "" };
	int i = 3;

	while (!in.atEnd())//csv内容存入ep中
	{
		fileLine = in.readLine();
		QStringList Entity_list = fileLine.split(";", QString::SkipEmptyParts);
		if (Entity_list.length() > 2)
		{
			param[i] = Entity_list.at(0).trimmed().toStdString(); i++;
			param[i] = Entity_list.at(1).trimmed().toStdString(); i++;
			param[i] = Entity_list.at(2).trimmed().toStdString(); i++;
			if (i > 11) break;
		}
		else
		{
			QMessageBox::about(NULL, tr("提示"), tr("读取数据内容出错！"));
			break;
		}
	}
	File.close();
	
	m_CreateComponent_dialog->lineEdit_LocateX->setText(QString::fromStdString(param[3]));
	m_CreateComponent_dialog->lineEdit_locateY->setText(QString::fromStdString(param[4]));
	m_CreateComponent_dialog->lineEdit_locateZ->setText(QString::fromStdString(param[5]));
	m_CreateComponent_dialog->lineEdit_ZDirect_X->setText(QString::fromStdString(param[6]));
	m_CreateComponent_dialog->lineEdit_ZDirect_Y->setText(QString::fromStdString(param[7]));
	m_CreateComponent_dialog->lineEdit_ZDirect_Z->setText(QString::fromStdString(param[8]));
	m_CreateComponent_dialog->lineEdit_XDirect_X->setText(QString::fromStdString(param[9]));
	m_CreateComponent_dialog->lineEdit_XDirect_Y->setText(QString::fromStdString(param[10]));
	m_CreateComponent_dialog->lineEdit_XDirect_Z->setText(QString::fromStdString(param[11]));	

	
	
}






