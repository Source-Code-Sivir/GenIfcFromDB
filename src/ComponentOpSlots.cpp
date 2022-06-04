#include "ComponentOpSlots.h"

#define BOOST_DATE_TIME_NO_LIB
#include <QtCore/qglobal.h>
#include <QSettings>
#include <QAction>
#include <QDockWidget>
#include <QStatusBar>
#include <QFile>
#include <QTreeWidget>
#include <fstream>
#include <qmessagebox.h>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>

#include "IfcPlusPlusSystem.h"
#include <ifcpp/model/IfcPPObject.h>
#include <ifcpp/model/IfcPPModel.h>
#include <ifcpp/geometry/GeometryConverter.h>
#include "ifcpp/model/IfcPPGuid.h"

#include <ifcpp/reader/ReaderUtil.h>
#include <ifcpp/writer/WriterUtil.h>
#include "ifcpp/IFC4/include/IfcGloballyUniqueId.h"
#include "ifcpp/IFC4/include/IfcOwnerHistory.h"
#include "ifcpp/IFC4/include/IfcText.h"
#include "ifcpp/IFC4/include/IfcAreaMeasure.h"
#include "ifcpp/IFC4/include/IfcVolumeMeasure.h"
#include "ifcpp/IFC4/include/IfcPlaneAngleMeasure.h"
#include "ifcpp/IFC4/include/IfcSolidAngleMeasure.h"
#include "ifcpp/IFC4/include/IfcTimeMeasure.h"
#include "ifcpp/IFC4/include/IfcMassMeasure.h"
#include "ifcpp/IFC4/include/IfcThermodynamicTemperatureMeasure.h"
#include "ifcpp/IFC4/include/IfcLuminousIntensityMeasure.h"
#include "ifcpp\IFC4\include\IfcDerivedUnitEnum.h"
#include "ifcpp\IFC4\include\IfcVolumetricFlowRateMeasure.h"
#include "ifcpp\IFC4\include\IfcGeometricProjectionEnum.h"
#include "ifcpp\IFC4\include\IfcProfileTypeEnum.h"
#include "ifcpp\IFC4\include\IfcReflectanceMethodEnum.h"
#include "ifcpp\IFC4\include\IfcSurfaceSide.h"
#include "ifcpp/IfcPPEntities.h"

#include <QTextCodec>
#include <string>
#include <windows.h>
#include <locale.h>
#include <sstream>
#include <cmath>
#include <stack>
#include <qvector3d.h>
#include <qinputdialog.h>
#include "qdialog.h"


using namespace std;
class IFCPP_EXPORT IfcUnitEnum;

#pragma execution_character_set("utf-8")


ComponentOpSlots::ComponentOpSlots(IfcPlusPlusSystem* sys)
	: m_system(sys)
{	
	flag_initModel = false;
	
}
ComponentOpSlots::~ComponentOpSlots()
{
	//outfile.close();
}

std::string ComponentOpSlots::ws2s(const std::wstring& ws)
{
	string curLocale = setlocale(LC_ALL, NULL);
	setlocale(LC_ALL, "chs");
	const wchar_t* _Source = ws.c_str();
	size_t _Dsize = 2 * ws.size() + 1;
	char *_Dest = new char[_Dsize];
	memset(_Dest, 0, _Dsize);
	wcstombs(_Dest, _Source, _Dsize);
	std::string result = _Dest;
	delete[]_Dest;
	setlocale(LC_ALL, curLocale.c_str());
	return result;
}
void ComponentOpSlots::direct_model(shared_ptr<IfcPPModel> &model, std::stringstream& stream)
{
	const boost::unordered_map<int, shared_ptr<IfcPPEntity> >& map_0 = model->getMapIfcEntities();
	std::map<int, shared_ptr<IfcPPEntity> > map_ordered_0(map_0.begin(), map_0.end());
	for (auto it = map_ordered_0.begin(); it != map_ordered_0.end(); ++it)
	{
		shared_ptr<IfcPPEntity> obj = it->second;
		if (obj.use_count() < 2)
		{
			// entity is referenced only in model map, not by other entities
			if (!dynamic_pointer_cast<IfcProduct>(obj) && !dynamic_pointer_cast<IfcProject>(obj))
			{
				continue;
			}
		}
		obj->getStepLine(stream);
		stream << std::endl;
	}

}

void ComponentOpSlots::InitIfcModel(int type_unit)
{
	m_model = m_system->getIfcModel(m_system->cur_model_sq);

	m_model->initIfcModel(type_unit);

	m_model = m_system->getIfcModel(m_system->cur_model_sq);

	m_system->getGeometryConverter()->setModel(m_model);

	flag_initModel = true;
}


void ComponentOpSlots::slotAddComponent(int type, int shape)
{		
	if (!flag_initModel) InitIfcModel(1);//单位默认毫米

	if (type == 0 && shape == 0)//column rectangle
	{
		//AddColumn(3100, 300, 500, 887.98508106, 461.800437105, 0);
		AddColumn(std::stof(paramdata[0]), std::stof(paramdata[1]), std::stof(paramdata[2]), std::stof(paramdata[3]), std::stof(paramdata[4]), std::stof(paramdata[5]), std::stof(paramdata[6]),
			std::stof(paramdata[7]), std::stof(paramdata[8]), std::stof(paramdata[9]), std::stof(paramdata[10]), std::stof(paramdata[11]));

		//AddColumn(800, 380, 7200, -1.59006, 1.56042, -1.1148, 0.988629, 0.144225, -0.0425732, -0.0339267, -0.0618901, -0.997506);
		
	}
	else if (type == 1 && shape == 0)//beam rectangle
	{			
		//AddBeam(800, 380, 7200, 7100, 6173.2050, 6053.5898, 0.24999,-0.433012,0.866025,0.866025,0.49999,0);
		//AddBeam(800, 380, 7200, 610.22, -121.908, -5482.85, -0.0769724, 0.0488293, -0.995837, 0.297851, -0.952064, -0.0697052);
		
		AddBeam(std::stof(paramdata[0]), std::stof(paramdata[1]), std::stof(paramdata[2]), std::stof(paramdata[3]), std::stof(paramdata[4]), std::stof(paramdata[5]), std::stof(paramdata[6]),
			std::stof(paramdata[7]), std::stof(paramdata[8]), std::stof(paramdata[9]), std::stof(paramdata[10]), std::stof(paramdata[11]));

	}

}

void ComponentOpSlots::AddComponent_Bar(bar& Reinforcingbar)
{
	if (!flag_initModel) InitIfcModel(1);//单位默认毫米

	Addbar( Reinforcingbar);
}


void ComponentOpSlots::slotOutputComponentIfc()
{
	single_model(m_model);
}


void ComponentOpSlots::AddColumn(double length, double width, double height, double locate_x, double locate_y, double locate_z, double zdirect_x, double zdirect_y, double zdirect_z, double xdirect_x, double xdirect_y, double xdirect_z)
{
	shared_ptr<IfcProject> project = m_model->getIfcProject();
	shared_ptr<IfcColumn> column(new IfcColumn());
	
	column->m_GlobalId = shared_ptr<IfcGloballyUniqueId>(new IfcGloballyUniqueId(CreateCompressedGuidString22()));
	column->m_OwnerHistory = project->m_OwnerHistory;
	column->m_Name = shared_ptr<IfcLabel>(new IfcLabel(L"Column"));
	m_model->insertEntity(column);

	const boost::unordered_map<int, shared_ptr<IfcPPEntity> >& map_ifc_objects = m_model->getMapIfcEntities();
	boost::unordered_map<int, shared_ptr<IfcPPEntity> >::const_iterator it;

	shared_ptr<IfcLocalPlacement> obj_placement_buildstorey(new IfcLocalPlacement());
	shared_ptr<IfcBuildingStorey> BuildingStorey;
	for (auto it = map_ifc_objects.begin(); it != map_ifc_objects.end(); ++it)
	{
		shared_ptr<IfcPPEntity> ifc_object = 0;

		ifc_object = (*it).second;
		std::string name = ifc_object->className();
		if ("IfcBuildingStorey" == name)
		{
			/*std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > > vec;
			ifc_object->getAttributes(vec);
			for (size_t ii = 0; ii < vec.size(); ++ii)
			{
				obj_placement_buildstorey = dynamic_pointer_cast<IfcLocalPlacement>(vec[ii].second);

				if (obj_placement_buildstorey)
				{
					continue;
				}
			}*/
			BuildingStorey = dynamic_pointer_cast<IfcBuildingStorey>(ifc_object);			
		}		
		
		if ("IfcRelContainedInSpatialStructure" == name)
		{
			shared_ptr<IfcRelContainedInSpatialStructure> entity_is = dynamic_pointer_cast<IfcRelContainedInSpatialStructure>(ifc_object);			
			entity_is->m_RelatedElements.push_back(dynamic_pointer_cast<IfcProduct>(column));
			continue;
		}		
	}

	shared_ptr<IfcLocalPlacement> obj_placement1(new IfcLocalPlacement());	
	obj_placement1->m_PlacementRelTo = BuildingStorey->m_ObjectPlacement;
	m_model->insertEntity(dynamic_pointer_cast<IfcObjectPlacement>(obj_placement1));

	column->m_ObjectPlacement = dynamic_pointer_cast<IfcObjectPlacement>(obj_placement1);

	shared_ptr<IfcAxis2Placement3D> axis_placement(new IfcAxis2Placement3D());
	m_model->insertEntity(axis_placement);

	obj_placement1->m_RelativePlacement = axis_placement;

	shared_ptr<IfcCartesianPoint> location(new IfcCartesianPoint());
	m_model->insertEntity(location);
	location->m_Coordinates.push_back(shared_ptr<IfcLengthMeasure>(new IfcLengthMeasure(locate_x)));
	location->m_Coordinates.push_back(shared_ptr<IfcLengthMeasure>(new IfcLengthMeasure(locate_y)));
	location->m_Coordinates.push_back(shared_ptr<IfcLengthMeasure>(new IfcLengthMeasure(locate_z)));

	/*shared_ptr<IfcDirection> column_directionZ(new IfcDirection());	
	column_directionZ->m_DirectionRatios.push_back(0.0);
	column_directionZ->m_DirectionRatios.push_back(0.0);
	column_directionZ->m_DirectionRatios.push_back(1.0);
	m_model->insertEntity(column_directionZ);	

	shared_ptr<IfcDirection> column_directionX(new IfcDirection());
	column_directionX->m_DirectionRatios.push_back(1.0);
	column_directionX->m_DirectionRatios.push_back(0.0);
	column_directionX->m_DirectionRatios.push_back(0.0);
	m_model->insertEntity(column_directionX);*/

	shared_ptr<IfcDirection> directionZ(new IfcDirection());

	directionZ->m_DirectionRatios.push_back(zdirect_x);
	directionZ->m_DirectionRatios.push_back(zdirect_y);
	directionZ->m_DirectionRatios.push_back(zdirect_z);
	m_model->insertEntity(directionZ);

	shared_ptr<IfcDirection> directionX(new IfcDirection());
	directionX->m_DirectionRatios.push_back(xdirect_x);
	directionX->m_DirectionRatios.push_back(xdirect_y);
	directionX->m_DirectionRatios.push_back(xdirect_z);
	m_model->insertEntity(directionX);

	axis_placement->m_Location = location;
	axis_placement->m_Axis = directionZ;
	axis_placement->m_RefDirection = directionX;

	shared_ptr<IfcProductDefinitionShape> def_shape(new IfcProductDefinitionShape());
	m_model->insertEntity(def_shape);

	column->m_Representation = dynamic_pointer_cast<IfcProductRepresentation>(def_shape);

	shared_ptr<IfcShapeRepresentation> rep_shape(new IfcShapeRepresentation());
	m_model->insertEntity(rep_shape);

	def_shape->m_Representations.push_back(dynamic_pointer_cast<IfcRepresentation>(rep_shape));

	shared_ptr<IfcGeometricRepresentationSubContext> rep_geom(new IfcGeometricRepresentationSubContext());
	rep_geom->m_ContextIdentifier = shared_ptr<IfcLabel>(new IfcLabel(L"Body"));
	rep_geom->m_ContextType = shared_ptr<IfcLabel>(new IfcLabel(L"Model"));
	rep_geom->m_ParentContext = dynamic_pointer_cast<IfcGeometricRepresentationContext>(project->m_RepresentationContexts[0]);
	rep_geom->m_TargetView = shared_ptr<IfcGeometricProjectionEnum>(new IfcGeometricProjectionEnum(IfcGeometricProjectionEnum::ENUM_MODEL_VIEW));
	m_model->insertEntity(rep_geom);

	shared_ptr<IfcExtrudedAreaSolid> extraAreaSolid(new IfcExtrudedAreaSolid());

	shared_ptr<IfcPositiveLengthMeasure> m_length(new IfcPositiveLengthMeasure());
	m_length->m_value = height;
	extraAreaSolid->m_Depth=m_length;
	m_model->insertEntity(extraAreaSolid);

	shared_ptr<IfcRectangleProfileDef> RectangleProfileDef(new IfcRectangleProfileDef());	
	RectangleProfileDef->m_ProfileType = shared_ptr<IfcProfileTypeEnum>(new IfcProfileTypeEnum(IfcProfileTypeEnum::ENUM_AREA));

	shared_ptr<IfcPositiveLengthMeasure> m_XDim(new IfcPositiveLengthMeasure());
	m_XDim->m_value = length;

	shared_ptr<IfcPositiveLengthMeasure> m_YDim(new IfcPositiveLengthMeasure());
	m_YDim->m_value = width;
	
	RectangleProfileDef->m_XDim = m_XDim;
	RectangleProfileDef->m_YDim = m_YDim;
	m_model->insertEntity(RectangleProfileDef);
	extraAreaSolid->m_SweptArea = RectangleProfileDef;

	rep_shape->m_ContextOfItems = rep_geom;
	rep_shape->m_RepresentationIdentifier = shared_ptr<IfcLabel>(new IfcLabel(L"Body"));
	rep_shape->m_RepresentationType = shared_ptr<IfcLabel>(new IfcLabel(L"SweptSolid"));
	rep_shape->m_Items.push_back(dynamic_pointer_cast<IfcRepresentationItem>(extraAreaSolid));

	shared_ptr<IfcAxis2Placement3D> extra_axis_placement3D(new IfcAxis2Placement3D());
	m_model->insertEntity(extra_axis_placement3D);
	extraAreaSolid->m_Position = extra_axis_placement3D;

	shared_ptr<IfcDirection> extra_directionZ(new IfcDirection());
	extra_directionZ->m_DirectionRatios.push_back(0.0);
	extra_directionZ->m_DirectionRatios.push_back(0.0);
	extra_directionZ->m_DirectionRatios.push_back(1.0);
	m_model->insertEntity(extra_directionZ);
	extraAreaSolid->m_ExtrudedDirection = extra_directionZ;

	shared_ptr<IfcAxis2Placement2D> profile_axis_placement2D(new IfcAxis2Placement2D());
	m_model->insertEntity(profile_axis_placement2D);

	RectangleProfileDef->m_Position = profile_axis_placement2D;

	shared_ptr<IfcCartesianPoint> profile_Point(new IfcCartesianPoint());
	profile_Point->m_Coordinates.push_back(shared_ptr<IfcLengthMeasure>(new IfcLengthMeasure(0)));
	profile_Point->m_Coordinates.push_back(shared_ptr<IfcLengthMeasure>(new IfcLengthMeasure(0)));
	m_model->insertEntity(profile_Point);

	shared_ptr<IfcDirection> profile_direction(new IfcDirection());
	profile_direction->m_DirectionRatios.push_back(1.0);
	profile_direction->m_DirectionRatios.push_back(0.0);
	m_model->insertEntity(profile_direction);

	profile_axis_placement2D->m_Location = profile_Point;
	profile_axis_placement2D->m_RefDirection = profile_direction;


	shared_ptr<IfcCartesianPoint> m_Axis(new IfcCartesianPoint());
	m_Axis->m_Coordinates.push_back(shared_ptr<IfcLengthMeasure>(new IfcLengthMeasure(0)));
	m_Axis->m_Coordinates.push_back(shared_ptr<IfcLengthMeasure>(new IfcLengthMeasure(0)));
	m_Axis->m_Coordinates.push_back(shared_ptr<IfcLengthMeasure>(new IfcLengthMeasure(0)));
	m_model->insertEntity(m_Axis);

	shared_ptr<IfcDirection> m_AxisZ(new IfcDirection());
	m_model->insertEntity(m_AxisZ);
	m_AxisZ->m_DirectionRatios.push_back(0.0);
	m_AxisZ->m_DirectionRatios.push_back(0.0);
	m_AxisZ->m_DirectionRatios.push_back(1.0);

	shared_ptr<IfcDirection> m_AxisX(new IfcDirection());
	m_model->insertEntity(m_AxisX);
	m_AxisX->m_DirectionRatios.push_back(1.0);
	m_AxisX->m_DirectionRatios.push_back(0.0);
	m_AxisX->m_DirectionRatios.push_back(0.0);

	extra_axis_placement3D->m_Location = m_Axis;
	extra_axis_placement3D->m_RefDirection = m_AxisX;
	extra_axis_placement3D->m_Axis = m_AxisZ;

}

template<typename select_t>
void getSelectType(const std::wstring& item, shared_ptr<select_t>& result)
{
	// could be type like IFCPARAMETERVALUE(90)
	std::wstring keyword;
	std::wstring inline_arg;
	tokenizeInlineArgument(item, keyword, inline_arg);

	if (keyword.size() == 0)
	{
		return;
	}

	IfcPPTypeEnum type_enum = findTypeEnumForString(keyword);
	if (type_enum != IfcPPTypeEnum::IFC_TYPE_UNDEFINED)
	{
		const boost::unordered_map<int, shared_ptr<IfcPPEntity> > map;
		shared_ptr<IfcPPObject> type_instance = createIfcPPType(type_enum, inline_arg, map);
		if (type_instance)
		{
			result = dynamic_pointer_cast<select_t>(type_instance);
			return;
		}
	}
}
void ComponentOpSlots::AddBeam(double XDim, double YDim, double Depth, double locate_x, double locate_y, double locate_z, double zdirect_x, double zdirect_y, double zdirect_z, double xdirect_x, double xdirect_y, double xdirect_z)
{
	shared_ptr<IfcProject> project = m_model->getIfcProject();
	shared_ptr<IfcBeam> beam(new IfcBeam());
	QString name_lable = QString::number(XDim, 10, 0) + "*" + QString::number(YDim, 10, 0);
   
	//qDebug() << name_lable;

	beam->m_GlobalId = shared_ptr<IfcGloballyUniqueId>(new IfcGloballyUniqueId(CreateCompressedGuidString22()));
	beam->m_OwnerHistory = project->m_OwnerHistory;
	beam->m_Name = shared_ptr<IfcLabel>(new IfcLabel(L"Beam"));
	beam->m_Description = shared_ptr<IfcText>(new IfcText(name_lable.toStdWString()));
	beam->m_ObjectType = shared_ptr<IfcLabel>(new IfcLabel(name_lable.toStdWString()));
	m_model->insertEntity(beam);

	const boost::unordered_map<int, shared_ptr<IfcPPEntity> >& map_ifc_objects = m_model->getMapIfcEntities();
	boost::unordered_map<int, shared_ptr<IfcPPEntity> >::const_iterator it;

	shared_ptr<IfcLocalPlacement> obj_placement_buildstorey(new IfcLocalPlacement());
	shared_ptr<IfcBuildingStorey> BuildingStorey;
	for (auto it = map_ifc_objects.begin(); it != map_ifc_objects.end(); ++it)
	{
		shared_ptr<IfcPPEntity> ifc_object = 0;

		ifc_object = (*it).second;
		std::string name = ifc_object->className();
		if ("IfcBuildingStorey" == name)
		{			
			BuildingStorey = dynamic_pointer_cast<IfcBuildingStorey>(ifc_object);
		}

		if ("IfcRelContainedInSpatialStructure" == name)
		{
			shared_ptr<IfcRelContainedInSpatialStructure> entity_is = dynamic_pointer_cast<IfcRelContainedInSpatialStructure>(ifc_object);
			entity_is->m_RelatedElements.push_back(dynamic_pointer_cast<IfcProduct>(beam));
			continue;
		}
	}

	shared_ptr<IfcLocalPlacement> obj_placement1(new IfcLocalPlacement());
	obj_placement1->m_PlacementRelTo = BuildingStorey->m_ObjectPlacement;
	m_model->insertEntity(dynamic_pointer_cast<IfcObjectPlacement>(obj_placement1));

	beam->m_ObjectPlacement = dynamic_pointer_cast<IfcObjectPlacement>(obj_placement1);

	shared_ptr<IfcAxis2Placement3D> axis_placement(new IfcAxis2Placement3D());
	m_model->insertEntity(axis_placement);

	obj_placement1->m_RelativePlacement = axis_placement;

	shared_ptr<IfcCartesianPoint> location(new IfcCartesianPoint());
	m_model->insertEntity(location);
	location->m_Coordinates.push_back(shared_ptr<IfcLengthMeasure>(new IfcLengthMeasure(locate_x)));
	location->m_Coordinates.push_back(shared_ptr<IfcLengthMeasure>(new IfcLengthMeasure(locate_y)));
	location->m_Coordinates.push_back(shared_ptr<IfcLengthMeasure>(new IfcLengthMeasure(locate_z)));

	shared_ptr<IfcDirection> directionZ(new IfcDirection());
	
	directionZ->m_DirectionRatios.push_back(zdirect_x);
	directionZ->m_DirectionRatios.push_back(zdirect_y);
	directionZ->m_DirectionRatios.push_back(zdirect_z);
	m_model->insertEntity(directionZ);

	shared_ptr<IfcDirection> directionX(new IfcDirection());
	directionX->m_DirectionRatios.push_back(xdirect_x);
	directionX->m_DirectionRatios.push_back(xdirect_y);
	directionX->m_DirectionRatios.push_back(xdirect_z);
	m_model->insertEntity(directionX);

	axis_placement->m_Location = location;
	axis_placement->m_Axis = directionZ;
	axis_placement->m_RefDirection = directionX;

	shared_ptr<IfcProductDefinitionShape> def_shape(new IfcProductDefinitionShape());
	m_model->insertEntity(def_shape);

	beam->m_Representation = dynamic_pointer_cast<IfcProductRepresentation>(def_shape);

	shared_ptr<IfcShapeRepresentation> rep_shape(new IfcShapeRepresentation());
	m_model->insertEntity(rep_shape);

	def_shape->m_Representations.push_back(dynamic_pointer_cast<IfcRepresentation>(rep_shape));

	shared_ptr<IfcGeometricRepresentationSubContext> rep_geom(new IfcGeometricRepresentationSubContext());
	rep_geom->m_ContextIdentifier = shared_ptr<IfcLabel>(new IfcLabel(L"Body"));
	rep_geom->m_ContextType = shared_ptr<IfcLabel>(new IfcLabel(L"Model"));
	rep_geom->m_ParentContext = dynamic_pointer_cast<IfcGeometricRepresentationContext>(project->m_RepresentationContexts[0]);
	rep_geom->m_TargetView = shared_ptr<IfcGeometricProjectionEnum>(new IfcGeometricProjectionEnum(IfcGeometricProjectionEnum::ENUM_MODEL_VIEW));
	m_model->insertEntity(rep_geom);

	shared_ptr<IfcExtrudedAreaSolid> extraAreaSolid(new IfcExtrudedAreaSolid());

	shared_ptr<IfcPositiveLengthMeasure> m_length(new IfcPositiveLengthMeasure());
	m_length->m_value = Depth;
	extraAreaSolid->m_Depth = m_length;
	m_model->insertEntity(extraAreaSolid);

	shared_ptr<IfcRectangleProfileDef> RectangleProfileDef(new IfcRectangleProfileDef());
	RectangleProfileDef->m_ProfileType = shared_ptr<IfcProfileTypeEnum>(new IfcProfileTypeEnum(IfcProfileTypeEnum::ENUM_AREA));
	RectangleProfileDef->m_ProfileName = shared_ptr<IfcLabel>(new IfcLabel(name_lable.toStdWString()));

	shared_ptr<IfcPositiveLengthMeasure> m_XDim(new IfcPositiveLengthMeasure());
	m_XDim->m_value = XDim;//截面长边length

	shared_ptr<IfcPositiveLengthMeasure> m_YDim(new IfcPositiveLengthMeasure());
	m_YDim->m_value = YDim;//截面短边width

	RectangleProfileDef->m_XDim = m_XDim;
	RectangleProfileDef->m_YDim = m_YDim;
	m_model->insertEntity(RectangleProfileDef);
	extraAreaSolid->m_SweptArea = RectangleProfileDef;

	rep_shape->m_ContextOfItems = rep_geom;
	rep_shape->m_RepresentationIdentifier = shared_ptr<IfcLabel>(new IfcLabel(L"Body"));
	rep_shape->m_RepresentationType = shared_ptr<IfcLabel>(new IfcLabel(L"SweptSolid"));
	rep_shape->m_Items.push_back(dynamic_pointer_cast<IfcRepresentationItem>(extraAreaSolid));

	shared_ptr<IfcAxis2Placement3D> extra_axis_placement3D(new IfcAxis2Placement3D());
	m_model->insertEntity(extra_axis_placement3D);
	extraAreaSolid->m_Position = extra_axis_placement3D;

	shared_ptr<IfcDirection> extra_directionZ(new IfcDirection());
	extra_directionZ->m_DirectionRatios.push_back(0.0);
	extra_directionZ->m_DirectionRatios.push_back(0.0);
	extra_directionZ->m_DirectionRatios.push_back(1.0);
	m_model->insertEntity(extra_directionZ);
	extraAreaSolid->m_ExtrudedDirection = extra_directionZ;

	shared_ptr<IfcAxis2Placement2D> profile_axis_placement2D(new IfcAxis2Placement2D());
	m_model->insertEntity(profile_axis_placement2D);

	RectangleProfileDef->m_Position = profile_axis_placement2D;

	shared_ptr<IfcCartesianPoint> profile_Point(new IfcCartesianPoint());
	profile_Point->m_Coordinates.push_back(shared_ptr<IfcLengthMeasure>(new IfcLengthMeasure(0)));
	profile_Point->m_Coordinates.push_back(shared_ptr<IfcLengthMeasure>(new IfcLengthMeasure(0)));
	m_model->insertEntity(profile_Point);

	shared_ptr<IfcDirection> profile_direction(new IfcDirection());
	profile_direction->m_DirectionRatios.push_back(1.0);
	profile_direction->m_DirectionRatios.push_back(0.0);
	m_model->insertEntity(profile_direction);

	profile_axis_placement2D->m_Location = profile_Point;
	profile_axis_placement2D->m_RefDirection = profile_direction;


	shared_ptr<IfcCartesianPoint> m_Axis(new IfcCartesianPoint());
	m_Axis->m_Coordinates.push_back(shared_ptr<IfcLengthMeasure>(new IfcLengthMeasure(Depth)));
	m_Axis->m_Coordinates.push_back(shared_ptr<IfcLengthMeasure>(new IfcLengthMeasure(0)));
	m_Axis->m_Coordinates.push_back(shared_ptr<IfcLengthMeasure>(new IfcLengthMeasure(0)));
	m_model->insertEntity(m_Axis);

	shared_ptr<IfcDirection> m_AxisZ(new IfcDirection());
	m_model->insertEntity(m_AxisZ);
	m_AxisZ->m_DirectionRatios.push_back(-1.0);
	m_AxisZ->m_DirectionRatios.push_back(0.0);
	m_AxisZ->m_DirectionRatios.push_back(0);

	shared_ptr<IfcDirection> m_AxisX(new IfcDirection());
	m_model->insertEntity(m_AxisX);
	m_AxisX->m_DirectionRatios.push_back(0.0);
	m_AxisX->m_DirectionRatios.push_back(0.0);
	m_AxisX->m_DirectionRatios.push_back(1.0);

	extra_axis_placement3D->m_Location = m_Axis;	
	extra_axis_placement3D->m_Axis = m_AxisZ;
	extra_axis_placement3D->m_RefDirection = m_AxisX;	

	shared_ptr<IfcColourRgb> colour_rgb(new IfcColourRgb());
	colour_rgb->m_Name = shared_ptr<IfcLabel>(new IfcLabel(L"Light Yellow"));
	shared_ptr<IfcNormalisedRatioMeasure> m_Red(new IfcNormalisedRatioMeasure());
	m_Red->m_value = 1;//0	
	shared_ptr<IfcNormalisedRatioMeasure> m_Green(new IfcNormalisedRatioMeasure());
	m_Green->m_value = 0.89803;//0	
	shared_ptr<IfcNormalisedRatioMeasure> m_Blue(new IfcNormalisedRatioMeasure());
	m_Blue->m_value = 0;//0	
	colour_rgb->m_Red = m_Red;
	colour_rgb->m_Green = m_Green;
	colour_rgb->m_Blue = m_Blue;
	m_model->insertEntity(colour_rgb);

	shared_ptr<IfcSurfaceStyleRendering> surface_style_render(new IfcSurfaceStyleRendering());
	surface_style_render->m_SurfaceColour = colour_rgb;
	shared_ptr<IfcNormalisedRatioMeasure> m_Transparency(new IfcNormalisedRatioMeasure());
	m_Transparency->m_value = 0;//0	
	surface_style_render->m_Transparency = m_Transparency;	
	

	shared_ptr<IfcColourOrFactor> value;
	getSelectType(L"IFCNORMALISEDRATIOMEASURE(0.00390625)", value);		
	//shared_ptr<IfcNormalisedRatioMeasure> m_SpecularColour(new IfcNormalisedRatioMeasure());	
	surface_style_render->m_SpecularColour = value;

	shared_ptr<IfcSpecularHighlightSelect> value2;
	getSelectType(L"IFCSPECULAREXPONENT(10)", value2);	
	surface_style_render->m_SpecularHighlight = value2;

	surface_style_render->m_ReflectanceMethod = shared_ptr<IfcReflectanceMethodEnum>(new IfcReflectanceMethodEnum(IfcReflectanceMethodEnum::ENUM_NOTDEFINED));
	m_model->insertEntity(surface_style_render);

	shared_ptr<IfcSurfaceStyle> surface_style(new IfcSurfaceStyle());
	surface_style->m_Name = shared_ptr<IfcLabel>(new IfcLabel(L"CONCRETE/C50"));
	surface_style->m_Side = shared_ptr<IfcSurfaceSide>(new IfcSurfaceSide(IfcSurfaceSide::ENUM_POSITIVE));
	surface_style->m_Styles.push_back(dynamic_pointer_cast<IfcSurfaceStyleRendering>(surface_style_render));
	m_model->insertEntity(surface_style);
	
	shared_ptr<IfcPresentationStyleAssignment> pre_style_assign(new IfcPresentationStyleAssignment());
	pre_style_assign->m_Styles.push_back(dynamic_pointer_cast<IfcSurfaceStyle>(surface_style));
	m_model->insertEntity(pre_style_assign);

	shared_ptr<IfcStyledItem> styleitem(new IfcStyledItem());
	styleitem->m_Item = extraAreaSolid;
	styleitem->m_Styles.push_back(dynamic_pointer_cast<IfcPresentationStyleAssignment>(pre_style_assign));
	m_model->insertEntity(styleitem);
	
	QMessageBox::about(NULL, tr("提示"), tr("新建构件已成功！"));

}

//将model输出到ifc文件中
void ComponentOpSlots::single_model(shared_ptr<IfcPPModel> &model)
{
	QString fileName = QFileDialog::getSaveFileName(nullptr,
		tr("Save ifc file"),
		"",
		tr("ifc Files (*.ifc)"));
	if (fileName.isNull())
	{
		return;
	}
	std::wstring wFileName = fileName.toStdWString();
	std::string file_name = "";

	file_name = ws2s(wFileName);

	std::stringstream str1;
	std::stringstream & stream = str1;

	std::string current_numeric_locale(setlocale(LC_NUMERIC, nullptr));
	setlocale(LC_NUMERIC, "C");
	//init the ouput stream fileheader (stringsream & stream)
	std::string filename_escaped = boost::replace_all_copy(file_name, "\\", "\\\\");

	std::wstringstream strs;
	strs << "ISO-10303-21;" << std::endl;
	strs << "HEADER;" << std::endl;
	strs << "FILE_DESCRIPTION(('IFC2X3'),'2;1');" << std::endl;
	strs << "FILE_NAME('" << filename_escaped.c_str() << "','";
	//2011-04-21T14:25:12
	std::locale loc(std::wcout.getloc(), new boost::posix_time::wtime_facet(L"%Y-%m-%dT%H:%M:%S"));
	std::basic_stringstream<wchar_t> wss;
	wss.imbue(loc);
	boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
	wss << now;
	std::wstring ts = wss.str().c_str();
	strs << ts;
	strs << "',('SJTUBIM'),(''SJTUBIM''),'NMBIM 4.0','Ifc file generated by NMBIM4.0','the Authorising person');" << std::endl;
	strs << "FILE_SCHEMA(('IFC2X3'));" << std::endl;
	strs << "ENDSEC;" << std::endl;
	std::wstring m_file_header = strs.str().c_str();

	model->setFileHeader(m_file_header);
	const std::wstring& file_header_wstr = model->getFileHeader();
	std::string file_header_str = encodeStepString(file_header_wstr);
	stream << file_header_str.c_str();
	stream << "DATA;\n";
	/*stream << std::setprecision(4);*/
	stream << std::setiosflags(std::ios::showpoint);
	stream << std::fixed;
	// end the init file header
	//end init the model's id


	// end the init file header
	//////////////////////////////////////////////////////////////////////////


	// end output the second model to stringstream
	/////////////////////////////////////////////////////////////////////

	//init output the first model to stringstream

	direct_model(model, stream);

	stream << "ENDSEC;\nEND-ISO-10303-21;\n";
	//end output the first model to stringstream
	setlocale(LC_NUMERIC, current_numeric_locale.c_str());
	char ch;
	std::ofstream f1(wFileName.c_str());
	if (!f1)return;
	while (stream.get(ch))
	{
		f1 << ch;
	}
	f1 << std::endl;
	f1.close();
	stream.clear();

	QMessageBox::about(NULL, tr("提示"), tr("已导出IFC文件！"));

}



