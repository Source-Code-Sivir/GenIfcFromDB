#pragma once
#ifndef GENIFC_H
#define GENIFC_H
#include<memory>
#include<vector>
#include<string>

#include<unordered_map>
#include"ifcpp\IFC4\include\IfcReinforcingBar.h"
#include"ifcpp\IFC4\include\IfcCompositeCurve.h"
#include "ifcpp\IFC4\include\IfcReinforcingBarType.h"
#include "ifcpp\IFC4\include\IfcReinforcingBarTypeEnum.h"
#include "ifcpp\IFC4\include\IfcTransitionCode.h"
#include "ifcpp\IFC4\include\IfcTrimmingSelect.h"
#include "ifcpp\IFC4\include\IfcTrimmingPreference.h"
#include "ifcpp\IFC4\include\IfcLine.h"
#include "ifcpp\IFC4\include\IfcVector.h"
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
#include"ifcpp/IFC4\include\IfcCompositeCurveSegment.h"
#include"ifcpp/IFC4\include\IfcBoolean.h"
#include"ifcpp\IFC4\include\IfcTrimmedCurve.h"
#include"ifcpp\IFC4\include\IfcParameterValue.h"
#include"ifcpp\IFC4\include\IfcCartesianPoint.h"
#include"ifcpp\IFC4\include\IfcLengthMeasure.h"
#include"ifcpp\IFC4\include\IfcVector.h"
#include"ifcpp\IFC4\include\IfcDirection.h"
#include"ifcpp\IFC4\include\IfcReal.h"
#include"ifcpp\IFC4\include\IfcCircle.h"
#include"ifcpp\IFC4\include\IfcPositiveLengthMeasure.h"
#include"ifcpp\IFC4\include\IfcAxis2Placement3D.h"
#include"ifcpp\IFC4\include\IfcAxis2Placement.h"
#include"ifcpp\IFC4\include\IfcDirection.h"
#include"ifcpp\IFC4\include\IfcRepresentationMap.h"
#include"ifcpp\IFC4\include\IfcRepresentation.h"
#include"ifcpp\IFC4\include\IfcSweptDiskSolid.h"
#include"ifcpp\IFC4\include\IfcShapeRepresentation.h"
#include"ifcpp\IFC4\include\IfcTrimmingPreference.h"
#include"ifcpp\IFC4\include\IfcGeometricRepresentationContext.h"
#include"ifcpp\IFC4\include\IfcMappedItem.h"
#include"ifcpp\IFC4\include\IfcCartesianTransformationOperator3D.h"
#include"ifcpp\IFC4\include\IfcProductDefinitionShape.h"
#include"ifcpp\IFC4\include\IfcLocalPlacement.h"
#include"ifcpp\IFC4\include\IfcLogical.h"
#include"ifcpp\IFC4\include\IfcReinforcingBarSurfaceEnum.h"
#include"ifcpp\IFC4\include\IfcLabel.h"
#include"ifcpp\IFC4\include\IfcIdentifier.h"
#include"ifcpp\IFC4\include\IfcVector.h"
#include"ifcpp\IFC4\include\IfcBuilding.h"
#include"ifcpp\IFC4\include\IfcBuildingStorey.h"
#include"ifcpp\IFC4\include\IfcSite.h"
#include"ifcpp\IFC4\include\IfcRelAggregates.h"
#include"ifcpp\IFC4\include\IfcRelContainedInSpatialStructure.h"
#include"ifcpp\IFC4\include\IfcBeam.h"
#include"ifcpp\IFC4\include\IfcBeamTypeEnum.h"
#include"ifcpp\IFC4\include\IfcExtrudedAreaSolid.h"

class GenIfc {
public:
	static std::unordered_map<int, shared_ptr<IfcBuildingStorey>> storeys;//存储楼层信息
	static std::shared_ptr<IfcCartesianPoint> GenIfcCartesianPoint(std::vector<double>& data);

	static std::shared_ptr<IfcDirection> GenIfcDirection(std::vector<double>& data);

	static std::shared_ptr<IfcAxis2Placement3D> GenIfcAxis2Placement3D(shared_ptr<IfcCartesianPoint>& point,
		shared_ptr<IfcDirection>& dx, shared_ptr<IfcDirection>& dz);

	static std::shared_ptr<IfcTrimmedCurve> GenIfcTrimmedCurve(shared_ptr<IfcCurve>& curve, double trim1, double trim2,
		bool direction, IfcTrimmingPreference::IfcTrimmingPreferenceEnum perf);
	//目前只支持用para初始化，如果想用point来初始化请自己写重载函数

	static std::shared_ptr<IfcLine> GenIfcLine(shared_ptr<IfcCartesianPoint>& point, shared_ptr<IfcDirection> dir);

	static std::shared_ptr<IfcCircle> GenIfcCircle(double radius, shared_ptr<IfcAxis2Placement3D>& placement);

	static std::shared_ptr<IfcCompositeCurveSegment> GenIfcCompositeCurveSegment(IfcTransitionCode::IfcTransitionCodeEnum e, bool same,
		shared_ptr<IfcCurve>& curve);

	static std::shared_ptr<IfcCompositeCurve> GenIfcCompositeCurve(std::vector <shared_ptr<IfcCompositeCurveSegment>>& curv, LogicalEnum a);

	static std::shared_ptr<IfcSweptDiskSolid> GenIfcSweptDiskSolid(shared_ptr<IfcCurve> curve, double radius,
		double innerradius, double start, double end);

	static std::shared_ptr<IfcShapeRepresentation> GenIfcShapeRepresentation(shared_ptr<IfcRepresentationContext> context,
		const char* m_RepresentationIdentifier, const char* m_RepresentationType,
		std::vector<shared_ptr<IfcRepresentationItem>>& m_Items);

	static std::shared_ptr<IfcRepresentationContext> GenIfcRepresentationContext();

	static std::shared_ptr<IfcGeometricRepresentationContext> GenIfcGeometricRepresentationContext(const char* m_ContextIdentifier,
		const char* m_ContextType, shared_ptr<IfcDimensionCount>m_CoordinateSpaceDimension, double precision,
		shared_ptr<IfcAxis2Placement> place, shared_ptr<IfcDirection> dir);

	static std::shared_ptr<IfcRepresentationMap> GenIfcRepresentationMap(shared_ptr<IfcAxis2Placement3D>& origin,
		shared_ptr<IfcRepresentation> pre);

	static std::shared_ptr<IfcMappedItem> GenIfcMappedItem(shared_ptr<IfcRepresentationMap> map,
		shared_ptr<IfcCartesianTransformationOperator> pre);

	static std::shared_ptr<IfcProductDefinitionShape> GenIfcProductDefinitionShape(const char* name, const char* desc,
		std::vector<shared_ptr<IfcRepresentation>> repres);

	static std::shared_ptr<IfcLocalPlacement> GenIfcLocalPlacement(shared_ptr<IfcObjectPlacement> localplace,
		shared_ptr<IfcAxis2Placement> place);

	static std::shared_ptr<IfcReinforcingBar> GenIfcReinforcingBar(shared_ptr<IfcGloballyUniqueId> globalID, shared_ptr<IfcOwnerHistory> owner,
		const char* name, shared_ptr<IfcObjectPlacement> objplace,
		shared_ptr<IfcProductRepresentation> repre, const char* steel,
		IfcReinforcingBarTypeEnum predefinedtype, IfcReinforcingBarSurfaceEnum surface, int parentStoreyID);

	static std::shared_ptr<IfcCartesianTransformationOperator> GenIfcCartesianTransformationOperator3D(shared_ptr<IfcDirection>axis1, shared_ptr<IfcDirection>axis2, shared_ptr<IfcCartesianPoint> point, shared_ptr<IfcReal> real,  shared_ptr<IfcDirection>axis3);

	static std::shared_ptr<IfcCompositeCurveSegment> GenIfcCompositeCurveSegment(shared_ptr<IfcTransitionCode>m_Transition, bool m_SameSense, shared_ptr<IfcCurve> m_ParentCurve);

	static std::shared_ptr<IfcBuilding> GenIfcBuilding(shared_ptr<IfcGloballyUniqueId> globalID, shared_ptr<IfcOwnerHistory> owner,
		const char* name, const char* desc, const char* objtype, shared_ptr<IfcObjectPlacement> objplace);

	static std::shared_ptr<IfcBuildingStorey> GenIfcBuildingStorey(shared_ptr<IfcGloballyUniqueId> globalID, shared_ptr<IfcOwnerHistory> owner,
		const char* name, const char* desc, const char* objtype, shared_ptr<IfcObjectPlacement> objplace, int elevation);
	
	static std::shared_ptr<IfcBeam> GenIfc::GeIfcBeam(shared_ptr<IfcOwnerHistory> owner,
		const char* name, shared_ptr<IfcObjectPlacement> objplace, shared_ptr<IfcProductRepresentation> representation, IfcBeamTypeEnum e, int parentFloorID);
		
	static std::shared_ptr<IfcExtrudedAreaSolid> GenIfcExtrudedAreaSolid(shared_ptr<IfcProfileDef> profile, shared_ptr<IfcDirection> direction, int depth);
	static std::shared_ptr<IfcProfileDef> GenIfcProfileDef(int type, std::string parameter);
};
#endif
