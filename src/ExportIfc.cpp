#include"ExportIfc.h"
#include"DB2Ifc.h"
#include"Genifc.h"
void convertPlacement(double local_x[3], double local_z[3], double location[3], shared_ptr<IfcAxis2Placement3D>& axis2placement3d, std::vector<shared_ptr<BuildingEntity> >& vec_new_entities)
{
	if (!axis2placement3d)
	{
		axis2placement3d = shared_ptr<IfcAxis2Placement3D>(new IfcAxis2Placement3D());
		vec_new_entities.push_back(axis2placement3d);
	}

	if (!axis2placement3d->m_Location)
	{
		axis2placement3d->m_Location = shared_ptr<IfcCartesianPoint>(new IfcCartesianPoint());
		vec_new_entities.push_back(axis2placement3d->m_Location);
	}
	axis2placement3d->m_Location->m_Coordinates.clear();
	axis2placement3d->m_Location->m_Coordinates.push_back(shared_ptr<IfcLengthMeasure>(new IfcLengthMeasure(location[0])));
	axis2placement3d->m_Location->m_Coordinates.push_back(shared_ptr<IfcLengthMeasure>(new IfcLengthMeasure(location[1])));
	axis2placement3d->m_Location->m_Coordinates.push_back(shared_ptr<IfcLengthMeasure>(new IfcLengthMeasure(location[2])));

	if (!axis2placement3d->m_Axis)
	{
		axis2placement3d->m_Axis = shared_ptr<IfcDirection>(new IfcDirection());
		vec_new_entities.push_back(axis2placement3d->m_Axis);
	}
	axis2placement3d->m_Axis->m_DirectionRatios.clear();
	axis2placement3d->m_Axis->m_DirectionRatios.push_back(shared_ptr<IfcReal>(new IfcReal(local_z[0])));
	axis2placement3d->m_Axis->m_DirectionRatios.push_back(shared_ptr<IfcReal>(new IfcReal(local_z[1])));
	axis2placement3d->m_Axis->m_DirectionRatios.push_back(shared_ptr<IfcReal>(new IfcReal(local_z[2])));

	if (!axis2placement3d->m_RefDirection)
	{
		axis2placement3d->m_RefDirection = shared_ptr<IfcDirection>(new IfcDirection());
		vec_new_entities.push_back(axis2placement3d->m_RefDirection);
	}

	axis2placement3d->m_RefDirection->m_DirectionRatios.clear();
	axis2placement3d->m_RefDirection->m_DirectionRatios.push_back(shared_ptr<IfcReal>(new IfcReal(local_x[0])));
	axis2placement3d->m_RefDirection->m_DirectionRatios.push_back(shared_ptr<IfcReal>(new IfcReal(local_x[1])));
	axis2placement3d->m_RefDirection->m_DirectionRatios.push_back(shared_ptr<IfcReal>(new IfcReal(local_x[2])));
}

void ExportIfc::initIfcModel(std::vector<shared_ptr<BuildingEntity>>& vec_new_entities)
{
	//std::vector<shared_ptr<BuildingEntity>> vec_new_entities;//存放所有的ifc实体


	shared_ptr<IfcProject> ifc_project = ifc_model->getIfcProject();
	if (!ifc_project)
	{
		ifc_project = shared_ptr<IfcProject>(new IfcProject());
		vec_new_entities.push_back(ifc_project);
		ifc_model->setIfcProject(ifc_project);
	}

	////shared_ptr<IfcSite> ifc_site(new IfcSite());
	////GenIfc::site = IfcSIUni
	//vec_new_entities.push_back(ifc_site);

	//shared_ptr<IfcBuilding> ifc_building(new IfcBuilding());
	//vec_new_entities.push_back(ifc_building);

	//shared_ptr<IfcBuildingStorey> ifc_building_storey(new IfcBuildingStorey());
	//vec_new_entities.push_back(ifc_building_storey);

	// relations object to connect site to project
	shared_ptr<IfcRelAggregates> rel_aggregates_project_site(new IfcRelAggregates());
	rel_aggregates_project_site->m_RelatingObject = ifc_project;
	rel_aggregates_project_site->m_RelatedObjects.push_back(DB2Ifc::site);
	vec_new_entities.push_back(rel_aggregates_project_site);

	// relations object to connect building to site
	//shared_ptr<IfcRelAggregates> rel_aggregates_site_building(new IfcRelAggregates());
	//rel_aggregates_site_building->m_RelatingObject = ifc_site;
	//rel_aggregates_site_building->m_RelatedObjects.push_back(ifc_building);
	//vec_new_entities.push_back(rel_aggregates_site_building);

	//// relations object to connect building storey to building
	//shared_ptr<IfcRelAggregates> rel_aggregates_building_buildingstorey(new IfcRelAggregates());
	//rel_aggregates_building_buildingstorey->m_RelatingObject = ifc_building;
	//rel_aggregates_building_buildingstorey->m_RelatedObjects.push_back(ifc_building_storey);
	//vec_new_entities.push_back(rel_aggregates_building_buildingstorey);

	//// relations object to connect wall to building storey
	//shared_ptr<IfcRelContainedInSpatialStructure> rel_contained_buildingstorey_wall(new IfcRelContainedInSpatialStructure());
	//rel_contained_buildingstorey_wall->m_RelatingStructure = ifc_building_storey;
	//rel_contained_buildingstorey_wall->m_RelatedElements.push_back(bar);
	//vec_new_entities.push_back(rel_contained_buildingstorey_wall);


	//// coordinate systems
	//double local_x[3] = { 1,0,0 };
	//double local_z[3] = { 0,0,1 };
	//double location[3] = { 0,0,0 };

	//// global placement
	//shared_ptr<IfcAxis2Placement3D> axis_placement_origin;
	//convertPlacement(local_x, local_z, location, axis_placement_origin, vec_new_entities);
	//shared_ptr<IfcLocalPlacement> global_placement(new IfcLocalPlacement());
	//vec_new_entities.push_back(global_placement);
	//global_placement->m_RelativePlacement = axis_placement_origin;

	//// local placement of building
	//location[0] = 2.7;
	//shared_ptr<IfcAxis2Placement3D> axis_placement_building;
	//convertPlacement(local_x, local_z, location, axis_placement_building, vec_new_entities);
	//shared_ptr<IfcLocalPlacement> building_placement(new IfcLocalPlacement());
	//vec_new_entities.push_back(building_placement);
	//building_placement->m_PlacementRelTo = global_placement;
	//building_placement->m_RelativePlacement = axis_placement_building;
	//ifc_building->m_ObjectPlacement = building_placement;

	//// local placement of wall
	//location[0] = 0.1;
	//location[1] = 3.0;
	//shared_ptr<IfcAxis2Placement3D> axis_placement_local;
	//convertPlacement(local_x, local_z, location, axis_placement_local, vec_new_entities);
	//shared_ptr<IfcLocalPlacement> wall_placement(new IfcLocalPlacement());
	//vec_new_entities.push_back(wall_placement);
	//wall_placement->m_PlacementRelTo = building_placement;
	//wall_placement->m_RelativePlacement = axis_placement_local;
	//bar->m_ObjectPlacement = wall_placement;


	// general objects
	shared_ptr<IfcPerson> person(new IfcPerson());
	person->m_Identification = shared_ptr<IfcIdentifier>(new IfcIdentifier(L"MyID"));
	person->m_FamilyName = shared_ptr<IfcLabel>(new IfcLabel(L"MyFamilyName"));
	person->m_GivenName = shared_ptr<IfcLabel>(new IfcLabel(L"MyGivenName"));
	vec_new_entities.push_back(person);

	shared_ptr<IfcOrganization> orga(new IfcOrganization());
	orga->m_Identification = shared_ptr<IfcIdentifier>(new IfcIdentifier(L"MyOrganization"));
	orga->m_Name = shared_ptr<IfcLabel>(new IfcLabel(L"My organizations name"));
	orga->m_Description = shared_ptr<IfcText>(new IfcText(L"My organizations description"));
	vec_new_entities.push_back(orga);

	shared_ptr<IfcPersonAndOrganization> person_and_organization(new IfcPersonAndOrganization());
	person_and_organization->m_ThePerson = person;
	person_and_organization->m_TheOrganization = orga;
	vec_new_entities.push_back(person_and_organization);

	shared_ptr<IfcOwnerHistory> owner_history(new IfcOwnerHistory());
	owner_history->m_OwningUser = person_and_organization;
	vec_new_entities.push_back(owner_history);

	// define units of the model
	shared_ptr<IfcSIUnit> unit1(new IfcSIUnit());
	unit1->m_UnitType = shared_ptr<IfcUnitEnum>(new IfcUnitEnum(IfcUnitEnum::ENUM_LENGTHUNIT));
	unit1->m_Prefix = make_shared<IfcSIPrefix>(IfcSIPrefix::ENUM_MILLI);
	unit1->m_Name = shared_ptr<IfcSIUnitName>(new IfcSIUnitName(IfcSIUnitName::ENUM_METRE));
	vec_new_entities.push_back(unit1);

	shared_ptr<IfcUnitAssignment> unit_assignment(new IfcUnitAssignment());
	unit_assignment->m_Units.push_back(unit1);
	vec_new_entities.push_back(unit_assignment);

	//radian 
	shared_ptr<IfcSIUnit> unit2(new IfcSIUnit());
	unit2->m_UnitType = shared_ptr<IfcUnitEnum>(new IfcUnitEnum(IfcUnitEnum::ENUM_RADIOACTIVITYUNIT));
	//unit2->m_Prefix = make_shared<IfcSIPrefix>(IfcSIPrefix::ENUM_MILLI);
	unit2->m_Name = shared_ptr<IfcSIUnitName>(new IfcSIUnitName(IfcSIUnitName::ENUM_RADIAN));
	vec_new_entities.push_back(unit2);

	shared_ptr<IfcUnitAssignment> unit_assignment2(new IfcUnitAssignment());
	unit_assignment2->m_Units.push_back(unit2);
	vec_new_entities.push_back(unit_assignment2);

	// define representation context
	shared_ptr<IfcGeometricRepresentationContext> geom_context(new IfcGeometricRepresentationContext());
	geom_context->m_ContextType = shared_ptr<IfcLabel>(new IfcLabel(L"Model"));
	geom_context->m_CoordinateSpaceDimension = shared_ptr<IfcDimensionCount>(new IfcDimensionCount(3));
	geom_context->m_Precision = shared_ptr<IfcReal>(new IfcReal(1.000E-5));
	geom_context->m_WorldCoordinateSystem = DB2Ifc::placements[1];
	vec_new_entities.push_back(geom_context);

	ifc_project->m_UnitsInContext = unit_assignment;
	ifc_project->m_RepresentationContexts.push_back(geom_context);

	std::map<BuildingEntity*, shared_ptr<BuildingEntity> > map_new_entities;
	shared_ptr<BuildingEntity> projectAsEntity = ifc_project;

	for (auto entity : vec_new_entities)
	{
		shared_ptr<IfcRoot> ifc_root_object = dynamic_pointer_cast<IfcRoot>(entity);
		if (ifc_root_object)
		{
			// each object that is derived from IfcRoot should have a GUID
			if (!ifc_root_object->m_GlobalId)
			{
				ifc_root_object->m_GlobalId = shared_ptr<IfcGloballyUniqueId>(new IfcGloballyUniqueId(createBase64Uuid_wstr().data()));
			}

			ifc_root_object->m_OwnerHistory = owner_history;
		}

		shared_ptr<IfcRepresentation> ifc_representation = dynamic_pointer_cast<IfcRepresentation>(entity);
		if (ifc_representation)
		{
			ifc_representation->m_ContextOfItems = geom_context;
		}

		ifc_model->insertEntity(entity);
	}

	ifc_model->unsetInverseAttributes();
	ifc_model->resolveInverseAttributes();
}
void loadModel(shared_ptr<BuildingModel>& ifc_model, std::vector<shared_ptr<BuildingEntity>> vec_new_entities) {
	if (ifc_model == nullptr) {
		ifc_model = shared_ptr<BuildingModel>(new BuildingModel());
	}
	shared_ptr<IfcGeometricRepresentationContext> geom_context(new IfcGeometricRepresentationContext());
	geom_context->m_ContextType = shared_ptr<IfcLabel>(new IfcLabel(L"Model"));
	geom_context->m_CoordinateSpaceDimension = shared_ptr<IfcDimensionCount>(new IfcDimensionCount(3));
	geom_context->m_Precision = shared_ptr<IfcReal>(new IfcReal(1.000E-5));
	geom_context->m_WorldCoordinateSystem = DB2Ifc::placements[1];
	vec_new_entities.push_back(geom_context);
	for (auto entity : vec_new_entities)
	{
		shared_ptr<IfcRoot> ifc_root_object = dynamic_pointer_cast<IfcRoot>(entity);
		if (ifc_root_object)
		{
			// each object that is derived from IfcRoot should have a GUID
			if (!ifc_root_object->m_GlobalId)
			{
				ifc_root_object->m_GlobalId = shared_ptr<IfcGloballyUniqueId>(new IfcGloballyUniqueId(createBase64Uuid_wstr().data()));
			}

			//ifc_root_object->m_OwnerHistory = owner_history;
		}

		shared_ptr<IfcRepresentation> ifc_representation = dynamic_pointer_cast<IfcRepresentation>(entity);
		if (ifc_representation)
		{
			ifc_representation->m_ContextOfItems = geom_context;
		}

		ifc_model->insertEntity(entity);
	}

	ifc_model->unsetInverseAttributes();
	ifc_model->resolveInverseAttributes();
}

void ExportIfc::exportifc() {
	std::wstring file_path = L"Example.ifc";
	ifc_model->initFileHeader(file_path);
	std::stringstream stream;

	shared_ptr<WriterSTEP> step_writer(new WriterSTEP());
	step_writer->writeModelToStream(stream, ifc_model);
	ifc_model->clearIfcModel();

	std::ofstream ofs(file_path, std::ofstream::out);
	ofs << stream.str().c_str();
	ofs.close();
}
