#include"Genifc.h"
//#pragma comment(lib,"IfcPlusPlus.dll")
#include"DB2Ifc.h"


	std::shared_ptr<IfcCompositeCurveSegment> GenIfc::GenIfcCompositeCurveSegment(shared_ptr<IfcTransitionCode>m_Transition, bool m_SameSense, shared_ptr<IfcCurve> m_ParentCurve) {
		shared_ptr<IfcCompositeCurveSegment> res = make_shared<IfcCompositeCurveSegment>();
		res->m_Transition = m_Transition;
		res->m_SameSense = make_shared<IfcBoolean>(m_SameSense);
		res->m_ParentCurve = m_ParentCurve;
		DB2Ifc::vec_new_entitys.push_back(res);
		return res;
	}
	std::shared_ptr<IfcCartesianPoint> GenIfc::GenIfcCartesianPoint(std::vector<double> &data) {
		shared_ptr<IfcCartesianPoint> point(new IfcCartesianPoint);
		for (auto i : data) {
			auto tmp = make_shared<IfcLengthMeasure>(i);
			point->m_Coordinates.push_back(tmp);
		}
		DB2Ifc::vec_new_entitys.push_back(point);
		return point;
	}

	std::shared_ptr<IfcDirection> GenIfc::GenIfcDirection(std::vector<double> &data) {
		shared_ptr<IfcDirection> dir = make_shared<IfcDirection>();
		//printf("\nsssss%d", dir->m_DirectionRatios.size());
		for (auto &i : dir->m_DirectionRatios) {
			printf("%.3f\n", i->m_value);
		}
		for (auto i : data) {
			dir->m_DirectionRatios.push_back(make_shared<IfcReal>(i));
		}
		DB2Ifc::vec_new_entitys.push_back(dir);
		return dir;
	}

	std::shared_ptr<IfcAxis2Placement3D> GenIfc::GenIfcAxis2Placement3D(shared_ptr<IfcCartesianPoint> &point, shared_ptr<IfcDirection>&dz, shared_ptr<IfcDirection>&dx) {
		shared_ptr<IfcAxis2Placement3D> rec = make_shared<IfcAxis2Placement3D>();
		rec->m_Location = point;
		rec->m_Axis = dz;
		rec->m_RefDirection = dx;
		DB2Ifc::vec_new_entitys.push_back(rec);
		return rec;
	}

	std::shared_ptr<IfcTrimmedCurve> GenIfc::GenIfcTrimmedCurve(shared_ptr<IfcCurve> &curve, double trim1, double trim2, bool direction, IfcTrimmingPreference::IfcTrimmingPreferenceEnum perf)
		//目前只支持用para初始化，如果想用point来初始化请自己写重载函数
	{
		shared_ptr<IfcTrimmedCurve> res = make_shared<IfcTrimmedCurve>();
		res->m_BasisCurve = curve;
		res->m_Trim1.push_back(make_shared<IfcParameterValue>(trim1));
		res->m_Trim2.push_back(make_shared<IfcParameterValue>(trim2));
		res->m_SenseAgreement = make_shared<IfcBoolean>(direction);
		res->m_MasterRepresentation = make_shared<IfcTrimmingPreference>(perf);
		DB2Ifc::vec_new_entitys.push_back(res);
		return res;
	}

	std::shared_ptr<IfcLine> GenIfc::GenIfcLine(shared_ptr<IfcCartesianPoint> &point, shared_ptr<IfcDirection>dir) {
		shared_ptr<IfcLine> res = make_shared<IfcLine>();
		shared_ptr<IfcVector> vec = make_shared<IfcVector>();
		vec->m_Magnitude = make_shared<IfcLengthMeasure>(1);
		vec->m_Orientation = dir;
		res->m_Dir = vec;
		res->m_Pnt = point;
		DB2Ifc::vec_new_entitys.push_back(vec);
		DB2Ifc::vec_new_entitys.push_back((res));
		return res;
	}

	std::shared_ptr<IfcCircle>GenIfc::GenIfcCircle(double radius, shared_ptr<IfcAxis2Placement3D> &placement) {
		shared_ptr<IfcCircle> res = make_shared<IfcCircle>();
		res->m_Position = placement;
		res->m_Radius = make_shared<IfcPositiveLengthMeasure>(radius);
		DB2Ifc::vec_new_entitys.push_back(res);
		return res;
	}

	std::shared_ptr<IfcCompositeCurveSegment>GenIfc::GenIfcCompositeCurveSegment(IfcTransitionCode::IfcTransitionCodeEnum e, bool same, shared_ptr<IfcCurve> &curve) {
		std::shared_ptr<IfcCompositeCurveSegment> res = make_shared<IfcCompositeCurveSegment>();
		res->m_Transition = make_shared<IfcTransitionCode>(e);
		res->m_SameSense = make_shared<IfcBoolean>(same);
		res->m_ParentCurve = curve;
		DB2Ifc::vec_new_entitys.push_back(res);
		return res;
	}
	std::shared_ptr<IfcCompositeCurve> GenIfc::GenIfcCompositeCurve(std::vector <shared_ptr<IfcCompositeCurveSegment>>& curv, LogicalEnum a) {
		shared_ptr<IfcCompositeCurve> res = make_shared<IfcCompositeCurve>();
		res->m_Segments = curv;
		res->m_SelfIntersect = make_shared<IfcLogical>(a);
		DB2Ifc::vec_new_entitys.push_back((res));
		return res;
	}

	std::shared_ptr<IfcSweptDiskSolid> GenIfc::GenIfcSweptDiskSolid(shared_ptr<IfcCurve> curve, double radius, double innerradius, double start, double end) {
		shared_ptr<IfcSweptDiskSolid> res = make_shared<IfcSweptDiskSolid>();
		res->m_Directrix = curve;
		res->m_Radius = make_shared<IfcPositiveLengthMeasure>(radius);
		//DB2Ifc::vec_new_entitys.push_back((res)
		if(innerradius>0)
			res->m_InnerRadius = make_shared<IfcPositiveLengthMeasure>(innerradius);
		if(start>=0)
			res->m_StartParam = make_shared<IfcParameterValue>(start);
		if(end>=0)
			res->m_EndParam = make_shared<IfcParameterValue>(end);
		DB2Ifc::vec_new_entitys.push_back(res);
		return res;
	}
	std::shared_ptr<IfcShapeRepresentation> GenIfc::GenIfcShapeRepresentation(shared_ptr<IfcRepresentationContext> context, const char *m_RepresentationIdentifier, const char *
		m_RepresentationType, std::vector<shared_ptr<IfcRepresentationItem>>&m_Items) {
		wchar_t tmp1[100],tmp2[100];
		swprintf(tmp1, 100, L"%ws", m_RepresentationIdentifier);
		swprintf(tmp2, 100, L"%ws", m_RepresentationType);

		shared_ptr<IfcShapeRepresentation> res = make_shared<IfcShapeRepresentation>();
		res->m_ContextOfItems = context;
		if(!m_RepresentationIdentifier)
			res->m_RepresentationType =make_shared<IfcLabel>( tmp1);
		if(!m_RepresentationType)
			res->m_RepresentationIdentifier =make_shared<IfcLabel>(tmp2);
		res->m_Items = m_Items;
		DB2Ifc::vec_new_entitys.push_back(res);
		return res;
	}
	std::shared_ptr<IfcRepresentationContext> GenIfc::GenIfcRepresentationContext() {
		shared_ptr<IfcRepresentationContext> res = make_shared<IfcRepresentationContext>();
		DB2Ifc::vec_new_entitys.push_back(res);
		return res;
	}
	std::shared_ptr<IfcGeometricRepresentationContext> GenIfc::GenIfcGeometricRepresentationContext(const char *m_ContextIdentifier, const char *m_ContextType, shared_ptr<IfcDimensionCount>m_CoordinateSpaceDimension, double precision, shared_ptr<IfcAxis2Placement> place, shared_ptr<IfcDirection> dir) {
		wchar_t tmp1[100], tmp2[100];
		swprintf(tmp1, 100, L"%ws", m_ContextIdentifier);
		swprintf(tmp2, 100, L"%ws", m_ContextType);

		shared_ptr<IfcGeometricRepresentationContext> res = make_shared<IfcGeometricRepresentationContext>();
		if(!m_ContextIdentifier)
			res->m_ContextIdentifier = make_shared<IfcLabel>(tmp1);
		if(!m_ContextType)
			res->m_ContextType =make_shared<IfcLabel>(tmp2);
		res->m_CoordinateSpaceDimension = m_CoordinateSpaceDimension;
		res->m_Precision = make_shared<IfcReal>(precision);
		res->m_WorldCoordinateSystem = place;
		res->m_TrueNorth = dir;
		DB2Ifc::vec_new_entitys.push_back(res);
		return res;
	}
	std::shared_ptr<IfcRepresentationMap> GenIfc::GenIfcRepresentationMap(shared_ptr<IfcAxis2Placement3D> &origin, shared_ptr<IfcRepresentation> pre) {
		shared_ptr<IfcRepresentationMap> res = make_shared<IfcRepresentationMap>();
		res->m_MappingOrigin = origin;
		res->m_MappedRepresentation = pre;
		DB2Ifc::vec_new_entitys.push_back(res);
		return res;
	}
	std::shared_ptr<IfcMappedItem> GenIfc::GenIfcMappedItem(shared_ptr<IfcRepresentationMap> map, shared_ptr<IfcCartesianTransformationOperator> pre) {
		shared_ptr<IfcMappedItem> res = make_shared<IfcMappedItem>();
		res->m_MappingSource = map;
		res->m_MappingTarget = pre;
		DB2Ifc::vec_new_entitys.push_back(res);
		return res;
	}
	std::shared_ptr<IfcCartesianTransformationOperator> GenIfc::GenIfcCartesianTransformationOperator3D(shared_ptr<IfcDirection>axis1, shared_ptr<IfcDirection>axis2, shared_ptr<IfcCartesianPoint> point, shared_ptr<IfcReal> real, shared_ptr<IfcDirection>axis3) {
		shared_ptr<IfcCartesianTransformationOperator3D>res = make_shared<IfcCartesianTransformationOperator3D>();
		res->m_Axis1 = axis1;
		res->m_Axis2 = axis2;
		res->m_LocalOrigin = point;
		res->m_Scale = real;
		res->m_Axis3 = axis3;
		DB2Ifc::vec_new_entitys.push_back(res);
		return res;
	}
	std::shared_ptr<IfcProductDefinitionShape> GenIfc::GenIfcProductDefinitionShape(const char *name, const char *desc, std::vector<shared_ptr<IfcRepresentation>> repres) {
		wchar_t tmp1[100], tmp2[100];
		swprintf(tmp1, 100, L"%ws", name);
		swprintf(tmp2, 100, L"%ws", desc);

		shared_ptr<IfcProductDefinitionShape> res = make_shared<IfcProductDefinitionShape>();
		if(!name)
			res->m_Name =make_shared<IfcLabel>(tmp1);
		if(!desc)
			res->m_Description =make_shared<IfcText>(tmp2);
		res->m_Representations = repres;
		DB2Ifc::vec_new_entitys.push_back(res);
		return res;
	}
	std::shared_ptr<IfcLocalPlacement> GenIfc::GenIfcLocalPlacement(shared_ptr<IfcObjectPlacement> localplace, shared_ptr<IfcAxis2Placement> place) {

		/*shared_ptr<IfcAxis2Placement3D> axis_placement_origin;
		convertPlacement(local_x, local_z, location, axis_placement_origin, vec_new_entities);
		shared_ptr<IfcLocalPlacement> global_placement(new IfcLocalPlacement());
		vec_new_entities.push_back(global_placement);
		global_placement->m_RelativePlacement = axis_placement_origin;*/

		shared_ptr<IfcLocalPlacement> res = make_shared<IfcLocalPlacement>();
		res->m_PlacementRelTo = localplace;
		res->m_RelativePlacement = place;
		DB2Ifc::vec_new_entitys.push_back(res);
		return res;
	}
	std::shared_ptr<IfcReinforcingBar> GenIfc::GenIfcReinforcingBar(shared_ptr<IfcGloballyUniqueId> globalID, shared_ptr<IfcOwnerHistory> owner,
		const char* name, const char* desc, const char* objtype, shared_ptr<IfcObjectPlacement> objplace,
		shared_ptr<IfcProductRepresentation> repre, const char* tag, const char* steel,
		double diameter, double area, double len,
		IfcReinforcingBarTypeEnum predefinedtype, IfcReinforcingBarSurfaceEnum surface,int parentStoreyID) {
		wchar_t tmp1[100], tmp2[100],tmp3[100],tmp4[100],tmp5[100],tmp6[100];
		//swprintf(tmp1, 100, L"%ws", id);
		swprintf(tmp2, 100, L"%ws", name);
		swprintf(tmp3, 100, L"%ws", desc);
		swprintf(tmp4, 100, L"%ws", objtype);
		swprintf(tmp5, 100, L"%ws", tag);
		swprintf(tmp6, 100, L"%ws", steel);

		shared_ptr<IfcReinforcingBar> res = make_shared<IfcReinforcingBar>();
		if(!globalID)
			res->m_GlobalId = globalID;
		res->m_OwnerHistory = owner;
		if (!name)
			res->m_Name = make_shared<IfcLabel>(tmp2);
		if(!desc)
			res->m_Description = make_shared<IfcText>(tmp3);
		if(!objtype)
			res->m_ObjectType =make_shared<IfcLabel>(tmp4);
		res->m_ObjectPlacement = objplace;
		res->m_Representation = repre;
		if(!tag)
			res->m_Tag = make_shared<IfcIdentifier>(tmp5);
		if(!steel)
			res->m_SteelGrade = make_shared<IfcLabel>(tmp6);
		res->m_NominalDiameter =make_shared<IfcPositiveLengthMeasure>(diameter);
		if(area>1)
			res->m_CrossSectionArea = make_shared<IfcAreaMeasure>(area);
		if(len>1)
		res->m_BarLength =make_shared<IfcPositiveLengthMeasure>(len);

		res->m_PredefinedType = make_shared<IfcReinforcingBarTypeEnum>(predefinedtype);
		res->m_BarSurface = make_shared<IfcReinforcingBarSurfaceEnum>(surface);
		DB2Ifc::vec_new_entitys.push_back(res);

		shared_ptr<IfcRelContainedInSpatialStructure> rel_contained_buildingstorey_wall(new IfcRelContainedInSpatialStructure());
		rel_contained_buildingstorey_wall->m_RelatingStructure = DB2Ifc::BuildingStorey[parentStoreyID];
		rel_contained_buildingstorey_wall->m_RelatedElements.push_back(res);
		DB2Ifc::vec_new_entitys.push_back(rel_contained_buildingstorey_wall);

		return res;
	}

	std::shared_ptr<IfcBuilding> GenIfc::GenIfcBuilding(shared_ptr<IfcGloballyUniqueId> globalID, shared_ptr<IfcOwnerHistory> owner,
		const char* name, const char* desc, const char* objtype, shared_ptr<IfcObjectPlacement> objplace) {
		if (DB2Ifc::site == nullptr) {
			DB2Ifc::site = make_shared<IfcSite>();
			DB2Ifc::vec_new_entitys.push_back(DB2Ifc::site);
		}

		shared_ptr<IfcBuilding> res = make_shared<IfcBuilding>();
		res->m_GlobalId = globalID;
		shared_ptr<IfcRelAggregates> rel_aggregates_site_building(new IfcRelAggregates());
		rel_aggregates_site_building->m_RelatingObject = DB2Ifc::site;
		rel_aggregates_site_building->m_RelatedObjects.push_back(res);
		DB2Ifc::vec_new_entitys.push_back(rel_aggregates_site_building);

		if (!globalID)
			//res->m_GlobalId = make_shared<IfcGloballyUniqueId>(tmp1);
		res->m_OwnerHistory = owner;
		if (!name)
			//res->m_Name = make_shared<IfcLabel>(tmp2);
		if (!desc)
			//res->m_Description = make_shared<IfcText>(tmp3);
		if (!objtype)
			//res->m_ObjectType = make_shared<IfcLabel>(tmp4);
		res->m_ObjectPlacement = objplace;
		
		DB2Ifc::vec_new_entitys.push_back(res);
		return res;
	}
	std::shared_ptr<IfcBuildingStorey> GenIfc::GenIfcBuildingStorey(shared_ptr<IfcGloballyUniqueId> globalID, shared_ptr<IfcOwnerHistory> owner,
		const char* name, const char* desc, const char* objtype, shared_ptr<IfcObjectPlacement> objplace, int elevation) {
		shared_ptr<IfcBuildingStorey> res = make_shared<IfcBuildingStorey>();
		res->m_GlobalId = globalID;
			//res->m_GlobalId = make_shared<IfcGloballyUniqueId>(tmp1);
		res->m_OwnerHistory = owner;
		if (!name)
			;
			//res->m_Name = make_shared<IfcLabel>(tmp2);
		if (!desc)
			;
			//res->m_Description = make_shared<IfcText>(tmp3);
		if (!objtype)
			;
			//res->m_ObjectType = make_shared<IfcLabel>(tmp4);
		res->m_ObjectPlacement = objplace;
		DB2Ifc::vec_new_entitys.push_back(res);

		shared_ptr<IfcRelAggregates> rel_aggregates_building_buildingstorey(new IfcRelAggregates());
		rel_aggregates_building_buildingstorey->m_RelatingObject = DB2Ifc::Buildings[1];
		rel_aggregates_building_buildingstorey->m_RelatedObjects.push_back(res);
		DB2Ifc::vec_new_entitys.push_back(rel_aggregates_building_buildingstorey);
		return res;
	}
