#include"DB2Ifc.h"
#include"sqlBag.h"
#include"Genifc.h"
#include<sstream>
#include "ifcpp/model/BuildingGuid.h"
#include"ifcpp\IFC4\include\IfcColourRgb.h"
#include"ifcpp\IFC4\include\IfcSurfaceStyleRendering.h"
#include"ifcpp\IFC4\include\IfcSurfaceStyle.h"
#include"ifcpp\IFC4\include\IfcPresentationStyleAssignment.h"
#include"ifcpp\IFC4\include\IfcSpecularExponent.h"
#include<string>

using std::stoi;
using std::stod;
using std::string;
using std::vector;
using namespace std;
#pragma comment(lib,"IfcPlusPlus.lib")


std::unordered_map<int, std::shared_ptr<IfcCartesianPoint>>  DB2Ifc::points;
std::unordered_map<int, std::shared_ptr<IfcDirection>>  DB2Ifc::directions;
std::unordered_map<int, std::shared_ptr<IfcAxis2Placement3D>>  DB2Ifc::placements;
std::unordered_map<int, std::shared_ptr<IfcLine>>  DB2Ifc::lines;
std::unordered_map<int, std::shared_ptr<IfcCircle>>  DB2Ifc::circles;
std::unordered_map<int, std::shared_ptr<IfcTrimmedCurve>>  DB2Ifc::TrimmedCurves;
std::unordered_map<int, std::shared_ptr<IfcCompositeCurve>>  DB2Ifc::CompositeCurves;
std::unordered_map<int, std::shared_ptr<IfcSweptDiskSolid>>  DB2Ifc::SweptDIskSolids;
std::unordered_map<int, std::shared_ptr<IfcReinforcingBar>>DB2Ifc::ReinforcingBars;
std::unordered_map<int, std::shared_ptr<IfcLocalPlacement>>DB2Ifc::LocalPlacements;
std::unordered_map<int, std::shared_ptr<IfcMappedItem>>DB2Ifc::MappedItems;
std::unordered_map<int, std::shared_ptr<IfcBuildingStorey>> DB2Ifc::BuildingStorey;
std::unordered_map<int, std::shared_ptr<IfcBuilding>>DB2Ifc::Buildings;
std::unordered_map<int, std::shared_ptr<IfcExtrudedAreaSolid>> DB2Ifc::ExtrudedAreaSolids;
std::unordered_map<int, std::shared_ptr<IfcBeam>> DB2Ifc::beams;
std::unordered_map<int, std::shared_ptr<IfcRelContainedInSpatialStructure>> DB2Ifc::storeyComponents;
//std::unordered_map<int, std::shared_ptr<IfcElementAssembly>> DB2Ifc::BeamBarAssembly;
unordered_map<int, shared_ptr<IfcRelAggregates>> DB2Ifc::BeamBarAssembly;

shared_ptr<IfcRelAggregates> DB2Ifc::buildingAggregates = nullptr;
shared_ptr<IfcPresentationStyleAssignment> DB2Ifc::mainBarColor = nullptr;
shared_ptr<IfcPresentationStyleAssignment> DB2Ifc::tiedBarColor = nullptr;
shared_ptr<IfcPresentationStyleAssignment> DB2Ifc::shearBarColor = nullptr;
shared_ptr<IfcPresentationStyleAssignment> DB2Ifc::waistBarColor = nullptr;
std::vector<shared_ptr<BuildingEntity>> DB2Ifc::vec_new_entitys;

shared_ptr<IfcSite>DB2Ifc::site = nullptr;

DB2Ifc* DB2Ifc::ins = nullptr;

int GenIfcPoint_callback(void* data, int argc, char** argv, char** azColName) {//通过ifcpoint表里面提取出来的数字生成ifcPoint
	//fprintf(stderr, "%s: ", (const char*)data);
	std::vector<double> point(3);
	int id = std::stoi(argv[0]);
	for (int i = 1; i < argc; i++) {
		point[i-1] = std::stod(argv[i]);
	}
	DB2Ifc::points[id]= (GenIfc::GenIfcCartesianPoint(point));
	//DB2Ifc::vec_new_entitys.push_back(DB2Ifc::points[id]);
	return 0;
}

int GenIfcDirection_callback(void* data, int argc, char** argv, char** azColName) {
	std::vector<double> direction(3);
	int id = std::stoi(argv[0]);
	for (int i = 1; i < argc; i++) {
		direction[i - 1] = std::stod(argv[i]);
	}
	DB2Ifc::directions[id] = GenIfc::GenIfcDirection(direction);
	//DB2Ifc::vec_new_entitys.push_back(DB2Ifc::directions[id]);
	return 0;
}
int GenIfcPlacement3D_callback(void* data, int argc, char** argv, char** azColName) {
	int id = -1,pointid = -1, dzid = -1, dxid = -1;
	id = std::stoi(argv[0]);
	pointid = std::stoi(argv[1]);
	dzid = std::stoi(argv[2]);
	dxid = std::stoi(argv[3]);
	DB2Ifc::placements[id] = GenIfc::GenIfcAxis2Placement3D(DB2Ifc::points[pointid], DB2Ifc::directions[dzid], DB2Ifc::directions[dxid]);
	//DB2Ifc::vec_new_entitys.push_back(DB2Ifc::placements[id]);
	return 0;
}
int GenIfcLines_callback(void* data, int argc, char** argv, char** azColName) {
	int id, pointid, directionid;
	id = stoi(argv[0]);
	pointid = stoi(argv[1]);
	directionid = stoi(argv[2]);
	DB2Ifc::lines[id] = GenIfc::GenIfcLine(DB2Ifc::points[pointid], DB2Ifc::directions[directionid]);
	//DB2Ifc::vec_new_entitys.push_back(DB2Ifc::lines[id]);
	return 0;
}
int GenIfcCircles_callback(void* data, int argc, char** argv, char** azColName) {
	int id, placeid;
	double radius;
	id = stoi(argv[0]);
	placeid = stoi(argv[1]);
	radius = stod(argv[2]);
	DB2Ifc::circles[id] = GenIfc::GenIfcCircle(radius, DB2Ifc::placements[placeid]);
	//DB2Ifc::vec_new_entitys.push_back(DB2Ifc::circles[id]);
	return 0;
}
int GenIfcTrimmedCurve_callback(void* data, int argc, char** argv, char** azColName) {
	int id, curveid;
	double trim1, trim2;
	bool same;
	id = stoi(argv[0]);
	curveid = stoi(argv[1]);
	trim1 = stod(argv[2]);
	trim2 = stod(argv[3]);
	bool isline = true;
	if (trim1 < 10 && trim2 < 10) {
		isline = false;
	}
	shared_ptr<IfcCurve> tmp;
	if (isline) {
		tmp = DB2Ifc::lines[curveid];
	}
	else {
		tmp = DB2Ifc::circles[curveid];
	}
		
	same = strcmp(argv[4], "1") ? false : true;
	DB2Ifc::TrimmedCurves[id] = GenIfc::GenIfcTrimmedCurve(tmp, trim1, trim2, same, IfcTrimmingPreference::ENUM_PARAMETER);
	//DB2Ifc::vec_new_entitys.push_back(DB2Ifc::TrimmedCurves[id]);
	return 0;
}
int GenIfcCompositeCurve_callback(void* data, int argc, char** argv, char** azColName) {
	int id = stoi(argv[0]);
	shared_ptr<IfcCompositeCurve> res;
	std::vector<shared_ptr<IfcCompositeCurveSegment>> vec;
	string curveid (argv[1]);
	stringstream ss(curveid);
	string tmps;
	while (ss >> tmps)
	{
		printf("%s\n", tmps.c_str());
		shared_ptr<IfcCompositeCurveSegment> tmp = GenIfc::GenIfcCompositeCurveSegment(make_shared<IfcTransitionCode>(IfcTransitionCode::ENUM_CONTINUOUS), true, DB2Ifc::TrimmedCurves[stoi(tmps)]);
		vec.push_back(tmp);
	}
	res = GenIfc::GenIfcCompositeCurve(vec, LogicalEnum::LOGICAL_FALSE);
	//DB2Ifc::vec_new_entitys.push_back(DB2Ifc::CompositeCurves[id]);
	DB2Ifc::CompositeCurves[id] = res;
	return 0;
}
int GenIfcSweptDiskSolid_callback(void* data, int argc, char** argv, char** azColName) {
	int id = stoi(argv[0]), directid = stoi(argv[1]);
	double radius = stod(argv[2])/2, innerradius = stod(argv[3]), begin = stod(argv[4]), end = stod(argv[5]);
	bool inner = true, b = true, e = true;
	if (innerradius < 0) {
		inner = false;
	}
	if (begin < 0) {
		b = false;
	}
	if (end < 0) {
		e = false;
	} 
	int bartype = stoi(argv[6]);
	DB2Ifc::SweptDIskSolids[id] = GenIfc::GenIfcSweptDiskSolid(DB2Ifc::CompositeCurves[directid], radius, innerradius, begin, end);
	if (DB2Ifc::mainBarColor == nullptr) {
		shared_ptr<IfcColourRgb> colorrgb = make_shared<IfcColourRgb>();
		DB2Ifc::vec_new_entitys.push_back(colorrgb);
		colorrgb->m_Red = make_shared< IfcNormalisedRatioMeasure>(1);
		colorrgb->m_Green = make_shared< IfcNormalisedRatioMeasure>(0);
		colorrgb->m_Blue = make_shared< IfcNormalisedRatioMeasure>(0);

		shared_ptr<IfcSurfaceStyleRendering> rendering = make_shared<IfcSurfaceStyleRendering>();
		DB2Ifc::vec_new_entitys.push_back(rendering);
		rendering->m_SurfaceColour = colorrgb;
		rendering->m_ReflectanceMethod = make_shared<IfcReflectanceMethodEnum>(IfcReflectanceMethodEnum::ENUM_NOTDEFINED);
		rendering->m_SpecularColour = make_shared<IfcNormalisedRatioMeasure>(0.00390625);
		rendering->m_SpecularHighlight = make_shared<IfcSpecularExponent>(10);
		rendering->m_Transparency = make_shared<IfcNormalisedRatioMeasure>(0);

		shared_ptr<IfcSurfaceStyle> surfacestyle = make_shared<IfcSurfaceStyle>();
		DB2Ifc::vec_new_entitys.push_back(surfacestyle);
		surfacestyle->m_Side = make_shared<IfcSurfaceSide>(IfcSurfaceSide::ENUM_POSITIVE);
		surfacestyle->m_Styles.push_back(rendering);

		shared_ptr<IfcPresentationStyleAssignment>layerass = make_shared<IfcPresentationStyleAssignment>();
		DB2Ifc::vec_new_entitys.push_back(layerass);
		layerass->m_Styles.push_back(surfacestyle);

		DB2Ifc::mainBarColor = layerass;
	}
	if (DB2Ifc::tiedBarColor == nullptr) {
		shared_ptr<IfcColourRgb> colorrgb = make_shared<IfcColourRgb>();
		DB2Ifc::vec_new_entitys.push_back(colorrgb);
		colorrgb->m_Red = make_shared< IfcNormalisedRatioMeasure>(0);
		colorrgb->m_Green = make_shared< IfcNormalisedRatioMeasure>(1);
		colorrgb->m_Blue = make_shared< IfcNormalisedRatioMeasure>(0);

		shared_ptr<IfcSurfaceStyleRendering> rendering = make_shared<IfcSurfaceStyleRendering>();
		DB2Ifc::vec_new_entitys.push_back(rendering);
		rendering->m_SurfaceColour = colorrgb;
		rendering->m_ReflectanceMethod = make_shared<IfcReflectanceMethodEnum>(IfcReflectanceMethodEnum::ENUM_NOTDEFINED);
		rendering->m_SpecularColour = make_shared<IfcNormalisedRatioMeasure>(0.00390625);
		rendering->m_SpecularHighlight = make_shared<IfcSpecularExponent>(10);
		rendering->m_Transparency = make_shared<IfcNormalisedRatioMeasure>(0);

		shared_ptr<IfcSurfaceStyle> surfacestyle = make_shared<IfcSurfaceStyle>();
		DB2Ifc::vec_new_entitys.push_back(surfacestyle);
		surfacestyle->m_Side = make_shared<IfcSurfaceSide>(IfcSurfaceSide::ENUM_POSITIVE);
		surfacestyle->m_Styles.push_back(rendering);

		shared_ptr<IfcPresentationStyleAssignment>layerass = make_shared<IfcPresentationStyleAssignment>();
		DB2Ifc::vec_new_entitys.push_back(layerass);
		layerass->m_Styles.push_back(surfacestyle);

		DB2Ifc::tiedBarColor = layerass;
	}
	if (DB2Ifc::waistBarColor == nullptr) {
		shared_ptr<IfcColourRgb> colorrgb = make_shared<IfcColourRgb>();
		DB2Ifc::vec_new_entitys.push_back(colorrgb);
		colorrgb->m_Red = make_shared< IfcNormalisedRatioMeasure>(0);
		colorrgb->m_Green = make_shared< IfcNormalisedRatioMeasure>(0.6);
		colorrgb->m_Blue = make_shared< IfcNormalisedRatioMeasure>(0.8);

		shared_ptr<IfcSurfaceStyleRendering> rendering = make_shared<IfcSurfaceStyleRendering>();
		DB2Ifc::vec_new_entitys.push_back(rendering);
		rendering->m_SurfaceColour = colorrgb;
		rendering->m_ReflectanceMethod = make_shared<IfcReflectanceMethodEnum>(IfcReflectanceMethodEnum::ENUM_NOTDEFINED);
		rendering->m_SpecularColour = make_shared<IfcNormalisedRatioMeasure>(0.00390625);
		rendering->m_SpecularHighlight = make_shared<IfcSpecularExponent>(10);
		rendering->m_Transparency = make_shared<IfcNormalisedRatioMeasure>(0);

		shared_ptr<IfcSurfaceStyle> surfacestyle = make_shared<IfcSurfaceStyle>();
		DB2Ifc::vec_new_entitys.push_back(surfacestyle);
		surfacestyle->m_Side = make_shared<IfcSurfaceSide>(IfcSurfaceSide::ENUM_POSITIVE);
		surfacestyle->m_Styles.push_back(rendering);

		shared_ptr<IfcPresentationStyleAssignment>layerass = make_shared<IfcPresentationStyleAssignment>();
		DB2Ifc::vec_new_entitys.push_back(layerass);
		layerass->m_Styles.push_back(surfacestyle);

		DB2Ifc::waistBarColor = layerass;
	}
	if (DB2Ifc::shearBarColor == nullptr) {
		shared_ptr<IfcColourRgb> colorrgb = make_shared<IfcColourRgb>();
		DB2Ifc::vec_new_entitys.push_back(colorrgb);
		colorrgb->m_Red = make_shared< IfcNormalisedRatioMeasure>(1);
		colorrgb->m_Green = make_shared< IfcNormalisedRatioMeasure>(0.6);
		colorrgb->m_Blue = make_shared< IfcNormalisedRatioMeasure>(0);

		shared_ptr<IfcSurfaceStyleRendering> rendering = make_shared<IfcSurfaceStyleRendering>();
		DB2Ifc::vec_new_entitys.push_back(rendering);
		rendering->m_SurfaceColour = colorrgb;
		rendering->m_ReflectanceMethod = make_shared<IfcReflectanceMethodEnum>(IfcReflectanceMethodEnum::ENUM_NOTDEFINED);
		rendering->m_SpecularColour = make_shared<IfcNormalisedRatioMeasure>(0.00390625);
		rendering->m_SpecularHighlight = make_shared<IfcSpecularExponent>(10);
		rendering->m_Transparency = make_shared<IfcNormalisedRatioMeasure>(0);

		shared_ptr<IfcSurfaceStyle> surfacestyle = make_shared<IfcSurfaceStyle>();
		DB2Ifc::vec_new_entitys.push_back(surfacestyle);
		surfacestyle->m_Side = make_shared<IfcSurfaceSide>(IfcSurfaceSide::ENUM_POSITIVE);
		surfacestyle->m_Styles.push_back(rendering);

		shared_ptr<IfcPresentationStyleAssignment>layerass = make_shared<IfcPresentationStyleAssignment>();
		DB2Ifc::vec_new_entitys.push_back(layerass);
		layerass->m_Styles.push_back(surfacestyle);

		DB2Ifc::shearBarColor = layerass;
	}
	shared_ptr<IfcStyledItem>style = make_shared<IfcStyledItem>();
	DB2Ifc::vec_new_entitys.push_back(style);
	style->m_Item = DB2Ifc::SweptDIskSolids[id];
	//shared_ptr<IfcPresentationStyleAssignment>tmp = DB2Ifc::mainBarColor;
	if(bartype==1)
		style->m_Styles.push_back(DB2Ifc::mainBarColor);
	else if(bartype==2)
		style->m_Styles.push_back(DB2Ifc::tiedBarColor);
	else if (bartype == 3) 
		style->m_Styles.push_back(DB2Ifc::shearBarColor);
	else if(bartype==4)
		style->m_Styles.push_back(DB2Ifc::waistBarColor);
	return 0;
}
int GenIfcMappedItem_callback(void* data, int argc, char** argv, char** azColName) {
	int id = stoi(argv[0]), pointid = stoi(argv[1]), type = stoi(argv[3]);
	std::string ids(argv[2]);
	std::vector<int> shapeids;
	std::stringstream ss(ids);
	std::string tmp;
	shared_ptr<IfcMappedItem> res;
	
	while (ss >> tmp) {
		shapeids.push_back(stoi(tmp));
	}
	switch (type)
	{
	case 1: {//bar
		for (auto i : shapeids) {//对应的是SweptDiskSolid 需要返回一个mappedItem
			std::vector<shared_ptr<IfcRepresentationItem>> items;
			items.push_back(DB2Ifc::SweptDIskSolids[i]);
			shared_ptr<IfcRepresentationMap> mapsource = GenIfc::GenIfcRepresentationMap(DB2Ifc::placements[1], GenIfc::GenIfcShapeRepresentation(nullptr, "Body", "SweptDiskSolid", items));
			res = GenIfc::GenIfcMappedItem(mapsource, GenIfc::GenIfcCartesianTransformationOperator3D(NULL , NULL, DB2Ifc::points[pointid], nullptr, NULL));
		}
	}
	default:
		break;
	}
	DB2Ifc::MappedItems[id] = res;
	//DB2Ifc::vec_new_entitys.push_back(DB2Ifc::MappedItems[id]);
	return 0;
}
int GenIfcReinforcingBar_callback(void* data, int argc, char** argv, char** azColName) {
	int id = stoi(argv[0]);
	int ownerid = stoi(argv[1]);
	const char* name(argv[2]);
	int placementid = stoi(argv[3]);
	string mappids(argv[4]);
	const char* stellgrade(argv[5]);
	int parentStoreyID = stoi(argv[6]);
	vector<int> mappedids;
	stringstream ss(mappids);
	string tmp;
	//DB2Ifc::BeamBarAssembly[id] = make_shared<IfcRelAggregates>();
	while (ss>>tmp)
	{
		mappedids.push_back(stoi(tmp));
	}
	std::vector<shared_ptr<IfcRepresentationItem>> items;
	for (auto i : mappedids) {
		items.push_back(DB2Ifc::MappedItems[i]);
	}
	shared_ptr<IfcRepresentation> barRepresentation = GenIfc::GenIfcShapeRepresentation(nullptr, "Body", "MappedRepresentation", items);
	std::vector<shared_ptr<IfcRepresentation>> vecrep;
	vecrep.push_back(barRepresentation);
	shared_ptr<IfcProductDefinitionShape> barShape = GenIfc::GenIfcProductDefinitionShape("", "", vecrep);
	DB2Ifc::ReinforcingBars[id] = GenIfc::GenIfcReinforcingBar(make_shared<IfcGloballyUniqueId>(createBase64Uuid_wstr().data()),nullptr,"AA", DB2Ifc::LocalPlacements[placementid],
		barShape,"C30", IfcReinforcingBarTypeEnum::ENUM_MAIN, IfcReinforcingBarSurfaceEnum::ENUM_PLAIN, parentStoreyID);
	//DB2Ifc::vec_new_entitys.push_back(DB2Ifc::ReinforcingBars[id]);
	DB2Ifc::BeamBarAssembly[parentStoreyID]->m_RelatedObjects.push_back(DB2Ifc::ReinforcingBars[id]);

	return 0;
}
int GenIfcExtrudedAreaSolid_callback(void* data, int argc, char** argv, char** azColName) {
	int id = stoi(argv[0]);
	int sectionType = stoi(argv[1]);
	string parameter(argv[2]);
	int directionID = stoi(argv[3]);
	int depth = stoi(argv[4]);
	//printf("%d", depth);
	DB2Ifc::ExtrudedAreaSolids[id] = GenIfc::GenIfcExtrudedAreaSolid(GenIfc::GenIfcProfileDef(sectionType, parameter), DB2Ifc::directions[directionID], depth);
	return 0;
}
int GenIfcBeam_callback(void* data, int argc, char** argv, char** azColName) {
	int id = stoi(argv[0]);
	int ownerid = stoi(argv[1]);
	int localplacementID = stoi(argv[3]);
	int representationId = stoi(argv[4]);//直接去sweptdisksolid里面找
	int storeyID = stoi(argv[5]);

	std::vector<shared_ptr<IfcRepresentationItem>> items;
	items.push_back(DB2Ifc::ExtrudedAreaSolids[representationId]);
	shared_ptr<IfcRepresentation> beamRepresentation = GenIfc::GenIfcShapeRepresentation(nullptr, "Body", "SweptSolid", items);
	std::vector<shared_ptr<IfcRepresentation>> vecrep;
	vecrep.push_back(beamRepresentation);
	shared_ptr<IfcProductDefinitionShape> beamShape = GenIfc::GenIfcProductDefinitionShape(nullptr, NULL, vecrep);
	DB2Ifc::beams[id] = GenIfc::GeIfcBeam(NULL, "bbb",DB2Ifc::LocalPlacements[localplacementID], beamShape, IfcBeamTypeEnum::ENUM_BEAM, storeyID);
	
	/*shared_ptr<IfcElementAssembly> elementAssembly = make_shared<IfcElementAssembly>();
	elementAssembly->m_ObjectPlacement = DB2Ifc::LocalPlacements[localplacementID];
	DB2Ifc::vec_new_entitys.push_back(elementAssembly);*/

	shared_ptr<IfcRelAggregates> relAgg = make_shared<IfcRelAggregates>();
	shared_ptr<IfcElementAssembly> tmpass = make_shared<IfcElementAssembly>();
	relAgg->m_RelatingObject = tmpass;
	DB2Ifc::BeamBarAssembly[id] = relAgg;
	DB2Ifc::vec_new_entitys.push_back(tmpass);
	DB2Ifc::vec_new_entitys.push_back(relAgg);

	DB2Ifc::storeyComponents[storeyID]->m_RelatedElements.push_back(tmpass);
	relAgg->m_RelatedObjects.push_back(DB2Ifc::beams[id]);

	return 0;
}
int GenIfcLocalPlacement_callback(void* data, int argc, char** argv, char** azColName) {
	int id = stoi(argv[0]), localid = stoi(argv[1]), placeid = stoi(argv[2]);
	if (localid==-1)
	{
		DB2Ifc::LocalPlacements[id] = GenIfc::GenIfcLocalPlacement(nullptr, DB2Ifc::placements[placeid]);
	}
	else {
		DB2Ifc::LocalPlacements[id] = GenIfc::GenIfcLocalPlacement(DB2Ifc::LocalPlacements[localid], DB2Ifc::placements[placeid]);
	}
	//DB2Ifc::vec_new_entitys.push_back(DB2Ifc::LocalPlacements[id]);
	return 0;
}
int GenIfcBuilding_callback(void* data, int argc, char** argv, char** azColName) {
	int id = stoi(argv[0]), localPlacementID = stoi(argv[5]);
	DB2Ifc::Buildings[id] = GenIfc::GenIfcBuilding(make_shared<IfcGloballyUniqueId>(createBase64Uuid_wstr().data()),NULL,nullptr,nullptr,nullptr,DB2Ifc::LocalPlacements[localPlacementID]);
	return 0;
}
int GenIfcBuildingStorey_callback(void* data, int argc, char** argv, char** azColName) {
	int id = stoi(argv[0]), localPlacementID = stoi(argv[5]), h = stoi(argv[6]);
	//string 
	//wchar_t tmp[10] = "ssss";
	DB2Ifc::BuildingStorey[id] = GenIfc::GenIfcBuildingStorey(make_shared<IfcGloballyUniqueId>(createBase64Uuid_wstr().data()), nullptr, nullptr, nullptr, nullptr,DB2Ifc::LocalPlacements[localPlacementID],h );
	DB2Ifc::storeyComponents[id] = make_shared<IfcRelContainedInSpatialStructure>();
	DB2Ifc::storeyComponents[id]->m_RelatingStructure = DB2Ifc::BuildingStorey[id];
	DB2Ifc::vec_new_entitys.push_back(DB2Ifc::storeyComponents[id]);

	/*shared_ptr<IfcElementAssembly> elementAssembly = make_shared<IfcElementAssembly>();
	elementAssembly->m_ObjectPlacement = DB2Ifc::LocalPlacements[localPlacementID];
	DB2Ifc::vec_new_entitys.push_back(elementAssembly);*/

	/*shared_ptr<IfcRelAggregates> relAgg = make_shared<IfcRelAggregates>();
	relAgg->m_RelatingObject = elementAssembly;
	DB2Ifc::BeamBarAssembly[id] = relAgg;
	DB2Ifc::vec_new_entitys.push_back(relAgg);
	
	DB2Ifc::storeyComponents[id]->m_RelatedElements.push_back(elementAssembly);*/


	return 0;
}
void DB2Ifc::GenPointsFromDB() {
	std::string command = "select * from IfcPoint;";
	printf("%s", "IfcPoint");
	SqliteExecution::Instance()->SelectDb(command, GenIfcPoint_callback, 0);
}
void DB2Ifc::GenDirectionsFromDB() {
	std::string command = "select * from IfcDirection;";
	printf("%s", "IfcDirection");
	SqliteExecution::Instance()->SelectDb(command, GenIfcDirection_callback, 0);
}
void DB2Ifc::GenPlacements3DFromDB() {
	std::string command = "select * from IfcPlacement3D;";
	printf("%s", "IfcPlacement3D");
	SqliteExecution::Instance()->SelectDb(command, GenIfcPlacement3D_callback, 0);
}
void DB2Ifc::GenLinesFromDB() {
	std::string command = "select * from IfcLine;";
	printf("%s", "IfcLine");
	SqliteExecution::Instance()->SelectDb(command, GenIfcLines_callback, 0);
}
void DB2Ifc::GenCirclesFromDB() {
	std::string command = "select * from IfcCircle;";
	printf("%s", "IfcCircle");
	SqliteExecution::Instance()->SelectDb(command, GenIfcCircles_callback, 0);
}
void DB2Ifc::GenTrimmedCurveFromDB() {
	std::string command = "select * from IfcTrimmedCurve;";
	printf("%s", "Ifctrimmedcurve");
	SqliteExecution::Instance()->SelectDb(command, GenIfcTrimmedCurve_callback, 0);
}
void DB2Ifc::GenCompositeCurveFromDB() {
	std::string command = "select * from IfcCompositeCurve;";
	printf("%s", "compositecurve");
	SqliteExecution::Instance()->SelectDb(command, GenIfcCompositeCurve_callback, 0);
}
void DB2Ifc::GenSweptDiskSoldFromDB() {
	std::string command = "select * from IfcSweptDiskSolid;";
	printf("%s", "sweptdisksolid");
	SqliteExecution::Instance()->SelectDb(command, GenIfcSweptDiskSolid_callback, 0);
}
void DB2Ifc::GenMappedItemFromDB() {
	std::string command = "select * from IfcMappedItem;";
	SqliteExecution::Instance()->SelectDb(command, GenIfcMappedItem_callback, 0);
}
void DB2Ifc::GenReinforcingBarFromDB() {
	string command = "select * from IfcReinforcingBar;";
	printf("%s", "reinforcingbar");
	SqliteExecution::Instance()->SelectDb(command, GenIfcReinforcingBar_callback, 0);
}

void DB2Ifc::GenLocalPlacementFromDB() {
	string command = "select * from IfcLocalPlacement;";
	printf("%s", "localplacement ");
	SqliteExecution::Instance()->SelectDb(command, GenIfcLocalPlacement_callback, 0);
}
void DB2Ifc::GenBuildingFromDB() {
	string command = "select * from IfcBuilding;";
	printf("%s", "ifcbuilding");
	SqliteExecution::Instance()->SelectDb(command, GenIfcBuilding_callback, 0);
}
void DB2Ifc::GenBuildingStoreyFromDB() {
	string command = "select * from IfcBuildingStory;";
	printf("%s", "buildingstorey");
	SqliteExecution::Instance()->SelectDb(command, GenIfcBuildingStorey_callback, 0);
}

void DB2Ifc::GenBeamFromDB() {
	string command = "select * from IfcBeam;";
	printf("%s ", "ifcbeam ");
	SqliteExecution::Instance()->SelectDb(command, GenIfcBeam_callback, 0);
}
void DB2Ifc::GenExtrudedAreaSolidFromDB() {
	string command = "select * from IfcExtrudedAreaSolid;";
	printf("areadisksolid ");
	SqliteExecution::Instance()->SelectDb(command, GenIfcExtrudedAreaSolid_callback, 0);
}
void DB2Ifc::GenAllFromDB() {
	GenPointsFromDB();
	GenDirectionsFromDB();
	GenPlacements3DFromDB();
	GenLocalPlacementFromDB();
	GenLinesFromDB();
	GenCirclesFromDB();
	GenBuildingFromDB();
	GenBuildingStoreyFromDB();
	GenExtrudedAreaSolidFromDB();
	GenBeamFromDB();
	GenTrimmedCurveFromDB();
	GenCompositeCurveFromDB();
	GenSweptDiskSoldFromDB();
	GenMappedItemFromDB();
	GenReinforcingBarFromDB();
}