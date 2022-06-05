//#include"GenifcClass.h"
#include<vector>
#include<stdio.h>
#include<string>
#include"sqlBag.h"
#include"DB2Ifc.h"
#include"ExportIfc.h"

///*void pre(shared_ptr<BuildingModel>& ifc_model, std::vector<shared_ptr<BuildingEntity>>& vec_new_entities) {
//	shared_ptr<IfcProject> ifc_project = ifc_model->getIfcProject();
//	// building structure
//	//shared_ptr<IfcProject> ifc_project = ifc_model->getIfcProject();
//	if (!ifc_project)
//	{
//		ifc_project = shared_ptr<IfcProject>(new IfcProject());
//		vec_new_entities.push_back(ifc_project);
//		ifc_model->setIfcProject(ifc_project);
//	}
//
//	shared_ptr<IfcSite> ifc_site(new IfcSite());
//	vec_new_entities.push_back(ifc_site);
//
//	shared_ptr<IfcBuilding> ifc_building(new IfcBuilding());
//	vec_new_entities.push_back(ifc_building);
//
//	shared_ptr<IfcBuildingStorey> ifc_building_storey(new IfcBuildingStorey());
//	vec_new_entities.push_back(ifc_building_storey);
//
//	// relations object to connect site to project
//	shared_ptr<IfcRelAggregates> rel_aggregates_project_site(new IfcRelAggregates());
//	rel_aggregates_project_site->m_RelatingObject = ifc_project;
//	rel_aggregates_project_site->m_RelatedObjects.push_back(ifc_site);
//	vec_new_entities.push_back(rel_aggregates_project_site);
//
//	// relations object to connect building to site
//	shared_ptr<IfcRelAggregates> rel_aggregates_site_building(new IfcRelAggregates());
//	rel_aggregates_site_building->m_RelatingObject = ifc_site;
//	rel_aggregates_site_building->m_RelatedObjects.push_back(ifc_building);
//	vec_new_entities.push_back(rel_aggregates_site_building);
//
//	// relations object to connect building storey to building
//	shared_ptr<IfcRelAggregates> rel_aggregates_building_buildingstorey(new IfcRelAggregates());
//	rel_aggregates_building_buildingstorey->m_RelatingObject = ifc_building;
//	rel_aggregates_building_buildingstorey->m_RelatedObjects.push_back(ifc_building_storey);
//	vec_new_entities.push_back(rel_aggregates_building_buildingstorey);
//
//	// relations object to connect wall to building storey
//	/*shared_ptr<IfcRelContainedInSpatialStructure> rel_contained_buildingstorey_wall(new IfcRelContainedInSpatialStructure());
//	rel_contained_buildingstorey_wall->m_RelatingStructure = ifc_building_storey;
//	rel_contained_buildingstorey_wall->m_RelatedElements.push_back(wall);
//	vec_new_entities.push_back(rel_contained_buildingstorey_wall);*/
//
//
//	// coordinate systems
//	/*double local_x[3] = { 1,0,0 };
//	double local_z[3] = { 0,0,1 };
//	double location[3] = { 0,0,0 };
//
//	// global placement
//	shared_ptr<IfcAxis2Placement3D> axis_placement_origin;
//	//convertPlacement(local_x, local_z, location, axis_placement_origin, vec_new_entities);
//	shared_ptr<IfcLocalPlacement> global_placement(DB2Ifc::LocalPlacements[1]);
//	//vec_new_entities.push_back(global_placement);
//	global_placement->m_RelativePlacement = axis_placement_origin;
//
//	// local placement of building
//	//location[0] = 2.7;
//	shared_ptr<IfcAxis2Placement3D> axis_placement_building;
//	//convertPlacement(local_x, local_z, location, axis_placement_building, vec_new_entities);
//	shared_ptr<IfcLocalPlacement> building_placement(DB2Ifc::LocalPlacements[1]);
//	vec_new_entities.push_back(building_placement);
//	building_placement->m_PlacementRelTo = global_placement;
//	building_placement->m_RelativePlacement = axis_placement_building;
//	ifc_building->m_ObjectPlacement = building_placement;
//
//	// local placement of wall
//	//location[0] = 0.1;
//	//location[1] = 3.0;
//	//shared_ptr<IfcAxis2Placement3D> axis_placement_local;
//	////convertPlacement(local_x, local_z, location, axis_placement_local, vec_new_entities);
//	//shared_ptr<IfcLocalPlacement> wall_placement(DB2Ifc::LocalPlacements[1]);
//	//vec_new_entities.push_back(wall_placement);
//	//wall_placement->m_PlacementRelTo = building_placement;
//	//wall_placement->m_RelativePlacement = axis_placement_local;
//	//wall->m_ObjectPlacement = wall_placement;
//
//	// general objects
//	shared_ptr<IfcPerson> person(new IfcPerson());
//	person->m_Identification = shared_ptr<IfcIdentifier>(new IfcIdentifier(L"MyID"));
//	person->m_FamilyName = shared_ptr<IfcLabel>(new IfcLabel(L"MyFamilyName"));
//	person->m_GivenName = shared_ptr<IfcLabel>(new IfcLabel(L"MyGivenName"));
//	vec_new_entities.push_back(person);
//
//	shared_ptr<IfcOrganization> orga(new IfcOrganization());
//	orga->m_Identification = shared_ptr<IfcIdentifier>(new IfcIdentifier(L"MyOrganization"));
//	orga->m_Name = shared_ptr<IfcLabel>(new IfcLabel(L"My organizations name"));
//	orga->m_Description = shared_ptr<IfcText>(new IfcText(L"My organizations description"));
//	vec_new_entities.push_back(orga);
//
//	shared_ptr<IfcPersonAndOrganization> person_and_organization(new IfcPersonAndOrganization());
//	person_and_organization->m_ThePerson = person;
//	person_and_organization->m_TheOrganization = orga;
//	vec_new_entities.push_back(person_and_organization);
//
//	shared_ptr<IfcOwnerHistory> owner_history(new IfcOwnerHistory());
//	owner_history->m_OwningUser = person_and_organization;
//	vec_new_entities.push_back(owner_history);
//
//	// define units of the model
//	shared_ptr<IfcSIUnit> unit1(new IfcSIUnit());
//	unit1->m_UnitType = shared_ptr<IfcUnitEnum>(new IfcUnitEnum(IfcUnitEnum::ENUM_LENGTHUNIT));
//	unit1->m_Prefix = make_shared<IfcSIPrefix>(IfcSIPrefix::ENUM_MILLI);
//	unit1->m_Name = shared_ptr<IfcSIUnitName>(new IfcSIUnitName(IfcSIUnitName::ENUM_METRE));
//	vec_new_entities.push_back(unit1);
//	
//	//
//	shared_ptr<IfcSIUnit> unit2(new IfcSIUnit());
//	unit2->m_UnitType = shared_ptr<IfcUnitEnum>(new IfcUnitEnum(IfcUnitEnum::ENUM_PLANEANGLEUNIT));
//	unit2->m_Name = shared_ptr<IfcSIUnitName>(new IfcSIUnitName(IfcSIUnitName::ENUM_RADIAN));
//	vec_new_entities.push_back(unit2);
//
//	shared_ptr<IfcUnitAssignment> unit_assignment(new IfcUnitAssignment());
//	unit_assignment->m_Units.push_back(unit1);
//	vec_new_entities.push_back(unit_assignment);
//
//	shared_ptr<IfcUnitAssignment> unit_assignment2(new IfcUnitAssignment());
//	unit_assignment2->m_Units.push_back(unit2);
//	vec_new_entities.push_back(unit_assignment2);
//
//	// define representation context
//	shared_ptr<IfcGeometricRepresentationContext> geom_context(new IfcGeometricRepresentationContext());
//	geom_context->m_ContextType = shared_ptr<IfcLabel>(new IfcLabel(L"Model"));
//	geom_context->m_CoordinateSpaceDimension = shared_ptr<IfcDimensionCount>(new IfcDimensionCount(3));
//	geom_context->m_Precision = shared_ptr<IfcReal>(new IfcReal(1.000E-5));
//	geom_context->m_WorldCoordinateSystem = axis_placement_origin;
//	vec_new_entities.push_back(geom_context);
//
//	ifc_project->m_UnitsInContext = unit_assignment;
//	ifc_project->m_RepresentationContexts.push_back(geom_context);
//
//	//std::map<BuildingEntity*, shared_ptr<BuildingEntity> > map_new_entities;
//	//shared_ptr<BuildingEntity> projectAsEntity = ifc_project;
//	ExportIfc::loadModel(ifc_model, DB2Ifc::vec_new_entitys);
//}*/
int main() {
	std::vector<double> point(3);
	//GenIfc::GenIfcCartesianPoint(point);
	SqliteExecution::Instance()->Init("E:\\code\\Insert2DB\\Insert2DB\\IfcDB.db");
	DB2Ifc::GenAllFromDB();
	//shared_ptr<BuildingModel> model = make_shared<BuildingModel>();
	//std::vector<shared_ptr<BuildingEntity>> vv;
	//vv.push_back(DB2Ifc::points[1]);
	ExportIfc exportEn;
	exportEn.initIfcModel( DB2Ifc::vec_new_entitys);
	exportEn.exportifc();
	return 0;
}
