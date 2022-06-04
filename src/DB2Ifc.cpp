#include"DB2Ifc.h"
#include"sqlBag.h"
#include"Genifc.h"
#include<sstream>
using namespace GenIfc;
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
std::vector<shared_ptr<BuildingEntity>> DB2Ifc::vec_new_entitys;

DB2Ifc* DB2Ifc::ins = nullptr;

int GenIfcPoint_callback(void* data, int argc, char** argv, char** azColName) {//ͨ��ifcpoint��������ȡ��������������ifcPoint
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
	DB2Ifc::lines[id] = GenIfcLine(DB2Ifc::points[pointid], DB2Ifc::directions[directionid]);
	//DB2Ifc::vec_new_entitys.push_back(DB2Ifc::lines[id]);
	return 0;
}
int GenIfcCircles_callback(void* data, int argc, char** argv, char** azColName) {
	int id, placeid;
	double radius;
	id = stoi(argv[0]);
	placeid = stoi(argv[1]);
	radius = stod(argv[2]);
	DB2Ifc::circles[id] = GenIfcCircle(radius, DB2Ifc::placements[placeid]);
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
	DB2Ifc::TrimmedCurves[id] = GenIfcTrimmedCurve(tmp, trim1, trim2, same, IfcTrimmingPreference::ENUM_PARAMETER);
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
		shared_ptr<IfcCompositeCurveSegment> tmp = GenIfcCompositeCurveSegment(make_shared<IfcTransitionCode>(IfcTransitionCode::ENUM_CONTINUOUS), true, DB2Ifc::TrimmedCurves[stoi(tmps)]);
		vec.push_back(tmp);
	}
	res = GenIfcCompositeCurve(vec, LogicalEnum::LOGICAL_FALSE);
	//DB2Ifc::vec_new_entitys.push_back(DB2Ifc::CompositeCurves[id]);
	DB2Ifc::CompositeCurves[id] = res;
	return 0;
}
int GenIfcSweptDiskSolid_callback(void* data, int argc, char** argv, char** azColName) {
	int id = stoi(argv[0]), directid = stoi(argv[1]);
	double radius = stod(argv[2]), innerradius = stod(argv[3]), begin = stod(argv[4]), end = stod(argv[5]);
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
	//shared_ptr<IfcCurve> tmp = DB2Ifc::CompositeCurves[directid];
	DB2Ifc::SweptDIskSolids[id] = GenIfcSweptDiskSolid(DB2Ifc::CompositeCurves[directid], radius, innerradius, begin, end);
	//DB2Ifc::vec_new_entitys.push_back(DB2Ifc::SweptDIskSolids[id]);
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
		for (auto i : shapeids) {//��Ӧ����SweptDiskSolid ��Ҫ����һ��mappedItem
			std::vector<shared_ptr<IfcRepresentationItem>> items;
			items.push_back(DB2Ifc::SweptDIskSolids[i]);
			shared_ptr<IfcRepresentationMap> mapsource = GenIfcRepresentationMap(DB2Ifc::placements[1], GenIfcShapeRepresentation(nullptr, "Body", "SweptDiskSolid", items));
			res = GenIfcMappedItem(mapsource, GenIfcCartesianTransformationOperator3D(NULL, NULL, DB2Ifc::points[pointid], nullptr,nullptr));
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
	const char *globalid(argv[1]);
	int ownerid = stoi(argv[2]);
	const char* name(argv[3]);
	const char* description(argv[4]);
	const char* objecttype(argv[5]);
	int placementid = stoi(argv[6]);
	string mappids(argv[7]);
	const char* tag(argv[8]);
	const char* stellgrade(argv[9]);
	
	vector<int> mappedids;
	stringstream ss(mappids);
	string tmp;
	while (ss>>tmp)
	{
		mappedids.push_back(stoi(tmp));
	}
	std::vector<shared_ptr<IfcRepresentationItem>> items;
	for (auto i : mappedids) {
		items.push_back(DB2Ifc::MappedItems[i]);
	}
	shared_ptr<IfcRepresentation> barRepresentation = GenIfcShapeRepresentation(nullptr, nullptr, nullptr, items);
	std::vector<shared_ptr<IfcRepresentation>> vecrep;
	vecrep.push_back(barRepresentation);
	shared_ptr<IfcProductDefinitionShape> barShape = GenIfcProductDefinitionShape(nullptr, NULL, vecrep);
	DB2Ifc::ReinforcingBars[id] = GenIfcReinforcingBar(globalid,nullptr,name,description,objecttype,DB2Ifc::LocalPlacements[placementid],barShape,tag,stellgrade
	,-1,-1,-1,IfcReinforcingBarTypeEnum::ENUM_MAIN,IfcReinforcingBarSurfaceEnum::ENUM_TEXTURED);
	//DB2Ifc::vec_new_entitys.push_back(DB2Ifc::ReinforcingBars[id]);
	return 0;
}
int GenIfcLocalPlacement_callback(void* data, int argc, char** argv, char** azColName) {
	int id = stoi(argv[0]), localid = stoi(argv[1]), placeid = stoi(argv[2]);
	if (localid==-1)
	{
		DB2Ifc::LocalPlacements[id] = GenIfcLocalPlacement(nullptr, DB2Ifc::placements[placeid]);
	}
	else {
		DB2Ifc::LocalPlacements[id] = GenIfcLocalPlacement(DB2Ifc::LocalPlacements[localid], DB2Ifc::placements[placeid]);
	}
	//DB2Ifc::vec_new_entitys.push_back(DB2Ifc::LocalPlacements[id]);
	return 0;
}

void DB2Ifc::GenPointsFromDB() {
	std::string command = "select * from IfcPoint;";
	SqliteExecution::Instance()->SelectDb(command, GenIfcPoint_callback, 0);
}
void DB2Ifc::GenDirectionsFromDB() {
	std::string command = "select * from IfcDirection;";
	SqliteExecution::Instance()->SelectDb(command, GenIfcDirection_callback, 0);
}
void DB2Ifc::GenPlacements3DFromDB() {
	std::string command = "select * from IfcPlacement3D;";
	SqliteExecution::Instance()->SelectDb(command, GenIfcPlacement3D_callback, 0);
}
void DB2Ifc::GenLinesFromDB() {
	std::string command = "select * from IfcLine;";
	SqliteExecution::Instance()->SelectDb(command, GenIfcLines_callback, 0);
}
void DB2Ifc::GenCirclesFromDB() {
	std::string command = "select * from IfcCircle;";
	SqliteExecution::Instance()->SelectDb(command, GenIfcCircles_callback, 0);
}
void DB2Ifc::GenTrimmedCurveFromDB() {
	std::string command = "select * from IfcTrimmedCurve;";
	SqliteExecution::Instance()->SelectDb(command, GenIfcTrimmedCurve_callback, 0);
}
void DB2Ifc::GenCompositeCurveFromDB() {
	std::string command = "select * from IfcCompositeCurve;";
	SqliteExecution::Instance()->SelectDb(command, GenIfcCompositeCurve_callback, 0);
}
void DB2Ifc::GenSweptDiskSoldFromDB() {
	std::string command = "select * from IfcSweptDiskSolid;";
	SqliteExecution::Instance()->SelectDb(command, GenIfcSweptDiskSolid_callback, 0);
}
void DB2Ifc::GenMappedItemFromDB() {
	std::string command = "select * from IfcMappedItem;";
	SqliteExecution::Instance()->SelectDb(command, GenIfcMappedItem_callback, 0);
}
void DB2Ifc::GenReinforcingBarFromDB() {
	string command = "select * from IfcReinforcingBar;";
	SqliteExecution::Instance()->SelectDb(command, GenIfcReinforcingBar_callback, 0);
}

void DB2Ifc::GenLocalPlacementFromDB() {
	string command = "select * from IfcLocalPlacement;";
	SqliteExecution::Instance()->SelectDb(command, GenIfcLocalPlacement_callback, 0);
}
void DB2Ifc::GenAllFromDB() {
	GenPointsFromDB();
	GenDirectionsFromDB();
	GenPlacements3DFromDB();
	GenLocalPlacementFromDB();
	GenLinesFromDB();
	GenCirclesFromDB();
	GenTrimmedCurveFromDB();
	GenCompositeCurveFromDB();
	GenSweptDiskSoldFromDB();
	GenMappedItemFromDB();
	GenReinforcingBarFromDB();
}